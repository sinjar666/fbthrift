/*
 * Copyright 2015 Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <thrift/lib/cpp2/server/BaseThriftServer.h>

#include <folly/Conv.h>
#include <folly/Memory.h>
#include <folly/Random.h>
#include <folly/Logging.h>
#include <folly/ScopeGuard.h>

#include <iostream>
#include <random>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include <signal.h>

namespace apache {
namespace thrift {

using namespace apache::thrift::protocol;
using namespace apache::thrift::server;
using namespace apache::thrift::transport;
using namespace apache::thrift::async;
using namespace std;
using std::shared_ptr;

const int BaseThriftServer::T_ASYNC_DEFAULT_WORKER_THREADS =
    sysconf(_SC_NPROCESSORS_ONLN);

const std::chrono::milliseconds BaseThriftServer::DEFAULT_TASK_EXPIRE_TIME =
    std::chrono::milliseconds(5000);

const std::chrono::milliseconds BaseThriftServer::DEFAULT_TIMEOUT =
    std::chrono::milliseconds(60000);

void BaseThriftServer::CumulativeFailureInjection::set(
    const FailureInjection& fi) {
  CHECK_GE(fi.errorFraction, 0);
  CHECK_GE(fi.dropFraction, 0);
  CHECK_GE(fi.disconnectFraction, 0);
  CHECK_LE(fi.errorFraction + fi.dropFraction + fi.disconnectFraction, 1);

  std::lock_guard<std::mutex> lock(mutex_);
  errorThreshold_ = fi.errorFraction;
  dropThreshold_ = errorThreshold_ + fi.dropFraction;
  disconnectThreshold_ = dropThreshold_ + fi.disconnectFraction;
  empty_.store((disconnectThreshold_ == 0), std::memory_order_relaxed);
}

BaseThriftServer::InjectedFailure
BaseThriftServer::CumulativeFailureInjection::test() const {
  if (empty_.load(std::memory_order_relaxed)) {
    return InjectedFailure::NONE;
  }

  static folly::ThreadLocalPtr<std::mt19937> rng;
  if (!rng) {
    rng.reset(new std::mt19937(folly::randomNumberSeed()));
  }

  std::uniform_real_distribution<float> dist(0, 1);
  float val = dist(*rng);

  std::lock_guard<std::mutex> lock(mutex_);
  if (val <= errorThreshold_) {
    return InjectedFailure::ERROR;
  } else if (val <= dropThreshold_) {
    return InjectedFailure::DROP;
  } else if (val <= disconnectThreshold_) {
    return InjectedFailure::DISCONNECT;
  }
  return InjectedFailure::NONE;
}

bool BaseThriftServer::getTaskExpireTimeForRequest(
    const apache::thrift::transport::THeader& requestHeader,
    std::chrono::milliseconds& softTimeout,
    std::chrono::milliseconds& hardTimeout) const {
  softTimeout = getTaskExpireTime();
  if (softTimeout == std::chrono::milliseconds(0)) {
    hardTimeout = softTimeout;
    return false;
  }
  if (getUseClientTimeout()) {
    // we add 10% to the client timeout so that the request is much more likely
    // to timeout on the client side than to read the timeout from the server
    // as a TApplicationException (which can be confusing)
    hardTimeout = std::chrono::milliseconds(
        (uint32_t)(requestHeader.getClientTimeout().count() * 1.1));
    if (hardTimeout > std::chrono::milliseconds(0)) {
      if (hardTimeout < softTimeout ||
          softTimeout == std::chrono::milliseconds(0)) {
        softTimeout = hardTimeout;
        return false;
      } else {
        return true;
      }
    }
  }
  hardTimeout = softTimeout;
  return false;
}

int64_t BaseThriftServer::getLoad(const std::string& counter,
                                  bool check_custom) {
  if (check_custom && getLoad_) {
    return getLoad_(counter);
  }

  auto reqload = getRequestLoad();
  auto connload = getConnectionLoad();
  auto queueload = getQueueLoad();

  if (VLOG_IS_ON(1)) {
    FB_LOG_EVERY_MS(INFO, 1000 * 10)
        << getLoadInfo(reqload, connload, queueload);
  }

  return std::max({reqload, connload, queueload});
}

int64_t BaseThriftServer::getQueueLoad() {
  auto tm = getThreadManager();
  if (tm) {
    auto codel = tm->getCodel();
    if (codel) {
      return codel->getLoad();
    }
  }

  return 0;
}

std::string BaseThriftServer::getLoadInfo(int64_t reqload,
                                           int64_t connload,
                                           int64_t queueload) {
  std::stringstream stream;
  stream << "Load is: " << reqload << "% requests, " << connload
         << "% connections, " << queueload << "% queue time";
  return stream.str();
}
}
} // apache::thrift

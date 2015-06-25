/*
 * Copyright 2014 Facebook, Inc.
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
#include <gtest/gtest.h>
#include <glog/logging.h>
#include <thrift/lib/cpp2/frozen/FrozenUtil.h>

#include <thrift/lib/cpp2/frozen/test/gen-cpp/Compatibility_layouts.h>
#include <thrift/lib/cpp2/frozen/test/gen-cpp/Compatibility_constants.h>

DEFINE_bool(write_test_cases, false, "Write files, too");

using namespace apache::thrift;
using namespace frozen;
using namespace util;

using namespace compatibility1;

class CompatibilityTest : public ::testing::TestWithParam<Case> {
 public:
  static std::string filePath(folly::StringPiece name) {
    return folly::to<std::string>("thrift/lib/cpp2/frozen/test/compatibility/",
                                  name);
  }
};

TEST_P(CompatibilityTest, Write) {
  if (!FLAGS_write_test_cases) {
    return;
  }
  auto test = GetParam();
  if (test.__isset.root) {
    freezeToFile(test.root,
                 folly::File(filePath(test.name).c_str(),
                             O_RDWR | O_TRUNC | O_CREAT | O_EXCL));
  }
}

TEST_P(CompatibilityTest, Read) {
  auto test = GetParam();
  auto path = folly::to<std::string>(
      "thrift/lib/cpp2/frozen/test/compatibility/", test.name);

  try {
    auto root = mapFrozen<Root>(folly::File(filePath(test.name).c_str()));
    EXPECT_FALSE(test.fails);
    EXPECT_EQ(test.root, root.thaw());
  }
  catch (const std::exception&) {
    EXPECT_TRUE(test.fails);
  }
}

INSTANTIATE_TEST_CASE_P(
    AllCases,
    CompatibilityTest,
    ::testing::ValuesIn(Compatibility_constants_codemod::kTestCases()));

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  testing::InitGoogleTest(&argc, argv);
  google::ParseCommandLineFlags(&argc, &argv, true);
  return RUN_ALL_TESTS();
}

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

#include <gtest/gtest.h>
#include <thrift/lib/cpp2/protocol/BinaryProtocol.h>
#include <thrift/lib/cpp2/protocol/CompactProtocol.h>
#include <thrift/lib/cpp2/protocol/DebugProtocol.h>
#include <thrift/lib/cpp2/protocol/SimpleJSONProtocol.h>
#include <thrift/lib/cpp2/protocol/VirtualProtocol.h>

using namespace std;
using namespace folly;
using namespace apache::thrift;

namespace {

constexpr auto strvalue = StringPiece("hello world");
using UniquePtrIOBuf = unique_ptr<IOBuf>;

template <typename R> struct maker {
  static R make();
};

template <> struct maker<StringPiece> {
  static StringPiece make() { return strvalue; }
};

template <> struct maker<ByteRange> {
  static ByteRange make() { return ByteRange(strvalue); }
};

template <> struct maker<IOBuf> {
  static IOBuf make() { return IOBuf(IOBuf::COPY_BUFFER, strvalue); }
};

template <> struct maker<UniquePtrIOBuf> {
  static UniquePtrIOBuf make() { return IOBuf::copyBuffer(strvalue); }
};

using Writers = testing::Types<
    BinaryProtocolWriter,
    CompactProtocolWriter,
    DebugProtocolWriter,
    SimpleJSONProtocolWriter,
    VirtualWriter<BinaryProtocolWriter>,
    VirtualWriter<CompactProtocolWriter>,
    //VirtualWriter<DebugProtocolWriter>,
    VirtualWriter<SimpleJSONProtocolWriter>>;

template <typename Writer>
class WriterInterfaceTest : public testing::Test {
 protected:
  IOBufQueue queue;
  Writer writer;
  void SetUp() override {
    writer.setOutput(&queue);
  }
};

}

TYPED_TEST_CASE_P(WriterInterfaceTest);

#define WRITER_INTERFACE_TYPED_TEST_P(method, argtype) \
  TYPED_TEST_P(WriterInterfaceTest, method ## _ ## argtype) { \
    this->writer.method(maker<argtype>::make()); \
  }

WRITER_INTERFACE_TYPED_TEST_P(writeString, StringPiece)
WRITER_INTERFACE_TYPED_TEST_P(writeBinary, StringPiece)
WRITER_INTERFACE_TYPED_TEST_P(writeBinary, ByteRange)
WRITER_INTERFACE_TYPED_TEST_P(writeBinary, UniquePtrIOBuf)
WRITER_INTERFACE_TYPED_TEST_P(writeBinary, IOBuf)

WRITER_INTERFACE_TYPED_TEST_P(serializedSizeString, StringPiece)
WRITER_INTERFACE_TYPED_TEST_P(serializedSizeBinary, StringPiece)
WRITER_INTERFACE_TYPED_TEST_P(serializedSizeBinary, ByteRange)
WRITER_INTERFACE_TYPED_TEST_P(serializedSizeBinary, UniquePtrIOBuf)
WRITER_INTERFACE_TYPED_TEST_P(serializedSizeBinary, IOBuf)

WRITER_INTERFACE_TYPED_TEST_P(serializedSizeZCBinary, StringPiece)
WRITER_INTERFACE_TYPED_TEST_P(serializedSizeZCBinary, ByteRange)
WRITER_INTERFACE_TYPED_TEST_P(serializedSizeZCBinary, UniquePtrIOBuf)
WRITER_INTERFACE_TYPED_TEST_P(serializedSizeZCBinary, IOBuf)

#undef WRITER_INTERFACE_TYPED_TEST_P

REGISTER_TYPED_TEST_CASE_P(
    WriterInterfaceTest,
    writeString_StringPiece,
    writeBinary_StringPiece,
    writeBinary_ByteRange,
    writeBinary_UniquePtrIOBuf,
    writeBinary_IOBuf,
    serializedSizeString_StringPiece,
    serializedSizeBinary_StringPiece,
    serializedSizeBinary_ByteRange,
    serializedSizeBinary_UniquePtrIOBuf,
    serializedSizeBinary_IOBuf,
    serializedSizeZCBinary_StringPiece,
    serializedSizeZCBinary_ByteRange,
    serializedSizeZCBinary_UniquePtrIOBuf,
    serializedSizeZCBinary_IOBuf);

INSTANTIATE_TYPED_TEST_CASE_P(Thrift, WriterInterfaceTest, Writers);

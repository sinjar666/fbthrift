/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include <thrift/lib/cpp/Thrift.h>
#include <thrift/lib/cpp/TApplicationException.h>
#include <thrift/lib/cpp/protocol/TProtocol.h>
#include <thrift/lib/cpp/transport/TTransport.h>

#include <folly/json.h>

#include <folly/Range.h>

#include <folly/Conv.h>

#include <math.h>

#include <thrift/lib/cpp/Thrift.h>

using namespace folly::json;
namespace apache { namespace thrift { namespace reflection {
class Schema;
}}}


namespace cpp1 {

class Included;

void swap(Included &a, Included &b);

class Included : public apache::thrift::TStructType<Included> {
 public:

  static const uint64_t _reflection_id = 16202005076139393548U;
  static void _reflection_register(::apache::thrift::reflection::Schema&);
  Included() : some_val(0) {
  }

  Included(const Included&) = default;
  Included& operator=(const Included& src)= default;
  Included(Included&&) = default;
  Included& operator=(Included&&) = default;

  void __clear();

  virtual ~Included() throw() {}

  int16_t some_val;

  struct __isset {
    __isset() { __clear(); } 
    void __clear() {
      some_val = false;
    }
    bool some_val;
  } __isset;

  bool operator == (const Included &) const;
  bool operator != (const Included& rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Included & ) const;

  void readFromJson(const char* jsonText, size_t len);
  void readFromJson(const char* jsonText);
  uint32_t read(apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(apache::thrift::protocol::TProtocol* oprot) const;

};

class Included;
void merge(const Included& from, Included& to);
void merge(Included&& from, Included& to);
} // namespace


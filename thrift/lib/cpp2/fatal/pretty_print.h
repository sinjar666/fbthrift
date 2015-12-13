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
#ifndef THRIFT_FATAL_PRETTY_PRINT_H_
#define THRIFT_FATAL_PRETTY_PRINT_H_ 1

#include <thrift/lib/cpp2/fatal/indenter.h>
#include <thrift/lib/cpp2/fatal/reflect_category.h>
#include <thrift/lib/cpp2/fatal/reflection.h>

#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

namespace apache { namespace thrift { namespace detail {
template <typename OutputStream, typename T>
OutputStream &pretty_print(OutputStream &&, T &&);
} // namespace detail {

/**
 * Pretty-prints an object to the given output stream using Thrift's reflection
 * support.
 *
 * All Thrift types are required to be generated using the 'fatal' cpp2 flag,
 * otherwise compile-time reflection metadata won't be available.
 *
 * @author: Marcelo Juchem <marcelo@fb.com>
 */
template <typename OutputStream, typename T>
void pretty_print(
  OutputStream &&out,
  T &&what,
  std::string indentation = "  "
) {
  detail::pretty_print(
    make_indenter(out, std::move(indentation)),
    std::forward<T>(what)
  );
}

/**
 * Pretty-prints an object to a string using Thrift's reflection support.
 *
 * All Thrift types are required to be generated using the 'fatal' cpp2 flag,
 * otherwise compile-time reflection metadata won't be available.
 *
 * @author: Marcelo Juchem <marcelo@fb.com>
 */
template <typename T>
std::string pretty_string(T &&what) {
  std::ostringstream out;
  pretty_print(out, std::forward<T>(what));
  return out.str();
}

}} // apache::thrift

#include <thrift/lib/cpp2/fatal/pretty_print-inl.h>

#endif // THRIFT_FATAL_PRETTY_PRINT_H_

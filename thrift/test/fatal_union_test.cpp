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

#include <thrift/test/gen-cpp2/reflection_fatal_union.h>

#include <thrift/lib/cpp2/fatal/reflection.h>
#include <thrift/test/expect_same.h>

#include <gtest/gtest.h>

#include <fatal/type/transform.h>

namespace test_cpp2 {
namespace cpp_reflection {

FATAL_STR(union1s, "union1");
FATAL_STR(uis, "ui");
FATAL_STR(uds, "ud");
FATAL_STR(uss, "us");
FATAL_STR(ues, "ue");

using uii = std::integral_constant<union1::Type, union1::Type::ui>;
using udi = std::integral_constant<union1::Type, union1::Type::ud>;
using usi = std::integral_constant<union1::Type, union1::Type::us>;
using uei = std::integral_constant<union1::Type, union1::Type::ue>;

TEST(fatal_union, variants) {
  using traits = fatal::variant_traits<union1>;

  EXPECT_SAME<union1, traits::type>();
  EXPECT_SAME<union1s, traits::name>();
  EXPECT_SAME<union1::Type, traits::id>();

  EXPECT_SAME<uii, traits::ids::ui>();
  EXPECT_SAME<udi, traits::ids::ud>();
  EXPECT_SAME<usi, traits::ids::us>();
  EXPECT_SAME<uei, traits::ids::ue>();

  EXPECT_SAME<
    fatal::type_list<uii, udi, usi, uei>,
    traits::descriptors::transform<fatal::get_member_type::id>
  >();

  EXPECT_SAME<
    fatal::type_list<std::int32_t, double, std::string, enum1>,
    traits::descriptors::transform<fatal::get_member_type::type>
  >();
}

TEST(fatal_union, by_id) {
  using vtraits = fatal::variant_traits<union1>;
  using traits = vtraits::by_id;

  EXPECT_SAME<fatal::type_list<uii, udi, usi, uei>, traits::tags>();

  EXPECT_SAME<uii, traits::id<uii>>();
  EXPECT_SAME<udi, traits::id<udi>>();
  EXPECT_SAME<usi, traits::id<usi>>();
  EXPECT_SAME<uei, traits::id<uei>>();

  EXPECT_SAME<std::int32_t, traits::type<uii>>();
  EXPECT_SAME<double, traits::type<udi>>();
  EXPECT_SAME<std::string, traits::type<usi>>();
  EXPECT_SAME<enum1, traits::type<uei>>();

  union1 u;
  union1 const &uc = u;
  union1 &ul = u;
  union1 &&ur = std::move(u);
  EXPECT_TRUE(vtraits::empty(u));
  EXPECT_TRUE(vtraits::empty(uc));
  EXPECT_TRUE(vtraits::empty(ul));
  EXPECT_TRUE(vtraits::empty(ur));

  traits::set<uii>(u, 10);
  EXPECT_FALSE(vtraits::empty(u));
  EXPECT_FALSE(vtraits::empty(uc));
  EXPECT_FALSE(vtraits::empty(ul));
  EXPECT_FALSE(vtraits::empty(ur));
  EXPECT_EQ(union1::Type::ui, u.getType());
  EXPECT_EQ(union1::Type::ui, vtraits::get_id(u));
  EXPECT_EQ(union1::Type::ui, vtraits::get_id(uc));
  EXPECT_EQ(union1::Type::ui, vtraits::get_id(ul));
  EXPECT_EQ(union1::Type::ui, vtraits::get_id(ur));
  EXPECT_EQ(10, u.get_ui());
  EXPECT_EQ(10, traits::get<uii>(ul));
  EXPECT_EQ(10, traits::get<uii>(uc));
  EXPECT_EQ(10, traits::get<uii>(ur));

  traits::set<udi>(u, 5.6);
  EXPECT_FALSE(vtraits::empty(u));
  EXPECT_FALSE(vtraits::empty(uc));
  EXPECT_FALSE(vtraits::empty(ul));
  EXPECT_FALSE(vtraits::empty(ur));
  EXPECT_EQ(union1::Type::ud, u.getType());
  EXPECT_EQ(union1::Type::ud, vtraits::get_id(u));
  EXPECT_EQ(union1::Type::ud, vtraits::get_id(uc));
  EXPECT_EQ(union1::Type::ud, vtraits::get_id(ul));
  EXPECT_EQ(union1::Type::ud, vtraits::get_id(ur));
  EXPECT_EQ(5.6, u.get_ud());
  EXPECT_EQ(5.6, traits::get<udi>(ul));
  EXPECT_EQ(5.6, traits::get<udi>(uc));
  EXPECT_EQ(5.6, traits::get<udi>(ur));

  traits::set<usi>(u, "hello");
  EXPECT_FALSE(vtraits::empty(u));
  EXPECT_FALSE(vtraits::empty(uc));
  EXPECT_FALSE(vtraits::empty(ul));
  EXPECT_FALSE(vtraits::empty(ur));
  EXPECT_EQ(union1::Type::us, u.getType());
  EXPECT_EQ(union1::Type::us, vtraits::get_id(u));
  EXPECT_EQ(union1::Type::us, vtraits::get_id(uc));
  EXPECT_EQ(union1::Type::us, vtraits::get_id(ul));
  EXPECT_EQ(union1::Type::us, vtraits::get_id(ur));
  EXPECT_EQ("hello", u.get_us());
  EXPECT_EQ("hello", traits::get<usi>(ul));
  EXPECT_EQ("hello", traits::get<usi>(uc));
  EXPECT_EQ("hello", traits::get<usi>(ur));

  traits::set<uei>(u, enum1::field1);
  EXPECT_FALSE(vtraits::empty(u));
  EXPECT_FALSE(vtraits::empty(uc));
  EXPECT_FALSE(vtraits::empty(ul));
  EXPECT_FALSE(vtraits::empty(ur));
  EXPECT_EQ(union1::Type::ue, u.getType());
  EXPECT_EQ(union1::Type::ue, vtraits::get_id(u));
  EXPECT_EQ(union1::Type::ue, vtraits::get_id(uc));
  EXPECT_EQ(union1::Type::ue, vtraits::get_id(ul));
  EXPECT_EQ(union1::Type::ue, vtraits::get_id(ur));
  EXPECT_EQ(enum1::field1, u.get_ue());
  EXPECT_EQ(enum1::field1, traits::get<uei>(ul));
  EXPECT_EQ(enum1::field1, traits::get<uei>(uc));
  EXPECT_EQ(enum1::field1, traits::get<uei>(ur));
}

TEST(fatal_union, by_type) {
  using vtraits = fatal::variant_traits<union1>;
  using traits = vtraits::by_type;

  EXPECT_SAME<
    fatal::type_list<std::int32_t, double, std::string, enum1>,
    traits::tags
  >();

  EXPECT_SAME<uii, traits::id<std::int32_t>>();
  EXPECT_SAME<udi, traits::id<double>>();
  EXPECT_SAME<usi, traits::id<std::string>>();
  EXPECT_SAME<uei, traits::id<enum1>>();

  EXPECT_SAME<std::int32_t, traits::type<std::int32_t>>();
  EXPECT_SAME<double, traits::type<double>>();
  EXPECT_SAME<std::string, traits::type<std::string>>();
  EXPECT_SAME<enum1, traits::type<enum1>>();

  union1 u;
  union1 const &uc = u;
  union1 &ul = u;
  union1 &&ur = std::move(u);
  EXPECT_TRUE(vtraits::empty(u));
  EXPECT_TRUE(vtraits::empty(uc));
  EXPECT_TRUE(vtraits::empty(ul));
  EXPECT_TRUE(vtraits::empty(ur));

  traits::set<std::int32_t>(u, 10);
  EXPECT_FALSE(vtraits::empty(u));
  EXPECT_FALSE(vtraits::empty(uc));
  EXPECT_FALSE(vtraits::empty(ul));
  EXPECT_FALSE(vtraits::empty(ur));
  EXPECT_EQ(union1::Type::ui, u.getType());
  EXPECT_EQ(union1::Type::ui, vtraits::get_id(u));
  EXPECT_EQ(union1::Type::ui, vtraits::get_id(uc));
  EXPECT_EQ(union1::Type::ui, vtraits::get_id(ul));
  EXPECT_EQ(union1::Type::ui, vtraits::get_id(ur));
  EXPECT_EQ(10, u.get_ui());
  EXPECT_EQ(10, traits::get<std::int32_t>(ul));
  EXPECT_EQ(10, traits::get<std::int32_t>(uc));
  EXPECT_EQ(10, traits::get<std::int32_t>(ur));

  traits::set<double>(u, 5.6);
  EXPECT_FALSE(vtraits::empty(u));
  EXPECT_FALSE(vtraits::empty(uc));
  EXPECT_FALSE(vtraits::empty(ul));
  EXPECT_FALSE(vtraits::empty(ur));
  EXPECT_EQ(union1::Type::ud, u.getType());
  EXPECT_EQ(union1::Type::ud, vtraits::get_id(u));
  EXPECT_EQ(union1::Type::ud, vtraits::get_id(uc));
  EXPECT_EQ(union1::Type::ud, vtraits::get_id(ul));
  EXPECT_EQ(union1::Type::ud, vtraits::get_id(ur));
  EXPECT_EQ(5.6, u.get_ud());
  EXPECT_EQ(5.6, traits::get<double>(ul));
  EXPECT_EQ(5.6, traits::get<double>(uc));
  EXPECT_EQ(5.6, traits::get<double>(ur));

  traits::set<std::string>(u, "hello");
  EXPECT_FALSE(vtraits::empty(u));
  EXPECT_FALSE(vtraits::empty(uc));
  EXPECT_FALSE(vtraits::empty(ul));
  EXPECT_FALSE(vtraits::empty(ur));
  EXPECT_EQ(union1::Type::us, u.getType());
  EXPECT_EQ(union1::Type::us, vtraits::get_id(u));
  EXPECT_EQ(union1::Type::us, vtraits::get_id(uc));
  EXPECT_EQ(union1::Type::us, vtraits::get_id(ul));
  EXPECT_EQ(union1::Type::us, vtraits::get_id(ur));
  EXPECT_EQ("hello", u.get_us());
  EXPECT_EQ("hello", traits::get<std::string>(ul));
  EXPECT_EQ("hello", traits::get<std::string>(uc));
  EXPECT_EQ("hello", traits::get<std::string>(ur));

  traits::set<enum1>(u, enum1::field1);
  EXPECT_FALSE(vtraits::empty(u));
  EXPECT_FALSE(vtraits::empty(uc));
  EXPECT_FALSE(vtraits::empty(ul));
  EXPECT_FALSE(vtraits::empty(ur));
  EXPECT_EQ(union1::Type::ue, u.getType());
  EXPECT_EQ(union1::Type::ue, vtraits::get_id(u));
  EXPECT_EQ(union1::Type::ue, vtraits::get_id(uc));
  EXPECT_EQ(union1::Type::ue, vtraits::get_id(ul));
  EXPECT_EQ(union1::Type::ue, vtraits::get_id(ur));
  EXPECT_EQ(enum1::field1, u.get_ue());
  EXPECT_EQ(enum1::field1, traits::get<enum1>(ul));
  EXPECT_EQ(enum1::field1, traits::get<enum1>(uc));
  EXPECT_EQ(enum1::field1, traits::get<enum1>(ur));
}

FATAL_STR(unionA_annotation1k, "another.annotation");
FATAL_STR(unionA_annotation1v, "some more text");
FATAL_STR(unionA_annotation2k, "sample.annotation");
FATAL_STR(unionA_annotation2v, "some text here");

TEST(fatal_struct, annotations) {
  EXPECT_SAME<
    fatal::type_map<>,
    apache::thrift::reflect_union<union1>::annotations
  >();

  EXPECT_SAME<
    fatal::type_map<>,
    apache::thrift::reflect_union<union2>::annotations
  >();

  EXPECT_SAME<
    fatal::type_map<>,
    apache::thrift::reflect_union<union3>::annotations
  >();

  EXPECT_SAME<
    fatal::build_type_map<
      unionA_annotation1k, unionA_annotation1v,
      unionA_annotation2k, unionA_annotation2v
    >,
    apache::thrift::reflect_union<unionA>::annotations
  >();
}

} // namespace cpp_reflection {
} // namespace test_cpp2 {

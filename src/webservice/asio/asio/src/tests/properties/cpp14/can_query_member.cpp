//
// cpp14/can_query_member.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2025 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "asio/query.hpp"
#include <cassert>

struct prop
{
  template <typename> static constexpr bool is_applicable_property_v = true;
};

struct object
{
  constexpr int query(prop) const { return 123; }
};

int main()
{
  static_assert(asio::can_query_v<object, prop>, "");
  static_assert(asio::can_query_v<const object, prop>, "");
}

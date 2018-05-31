#pragma once

#include <cstdint>
#include <climits>

using int_type = std::int32_t;
using long_type = std::int64_t;
using float_type = float;
using double_type = double;
using char_type = std::int8_t;
using bool_type = std::int8_t;
using command_type = int_type;

constexpr auto int_size = sizeof(int_type);
constexpr auto long_size = sizeof(long_type);
constexpr auto float_size = sizeof(float_type);
constexpr auto double_size = sizeof(double_type);
constexpr auto char_size = sizeof(char_type);
constexpr auto bool_size = sizeof(bool_type);

union TypeConverter {
  int_type i;
  long_type l;
  float_type f;
  double_type d;
  char_type c;
  bool_type b;
  int_type raw[2];
};

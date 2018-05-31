#include "types.hpp"

static_assert(CHAR_BIT == 8, "Wrong byte size!");
static_assert(sizeof(command_type) == sizeof(int_type), "Word and command should have the same size!");
static_assert(sizeof(int_type) == 4, "Wrong integer size!");
static_assert(sizeof(long_type) == 8, "Wrong long size!");
static_assert(sizeof(float_type) == 4, "Wrong float size!");
static_assert(sizeof(double_type) == 8, "Wrong double size!");
static_assert(sizeof(char_type) == 1, "Wrong double size!");
static_assert(sizeof(bool_type) == 1, "Wrong double size!");

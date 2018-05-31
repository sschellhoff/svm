#pragma once

#include "types.hpp"

enum Commands : command_type {
  HALT = 0,
  LOADC,
  ADD,
  SUB,
  MULT,
  DIV,
  MOD,
  AND,
  OR,
  EQ,
  NEQ,
  LE,
  LT,
  GE,
  GT
};

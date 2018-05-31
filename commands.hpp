#pragma once

#include "types.hpp"

enum Commands : command_type {
  HALT = 0,
  PUSH,
  POP,
  LOADC,
  ADD,
  SUB,
  MULT,
  DIV,
  MOD,
  AND_B,
  OR_B,
  XOR_B,
  NOT_B,
  EQ,
  NEQ,
  LE,
  LT,
  GE,
  GT,
  NEG,
  NOT
};

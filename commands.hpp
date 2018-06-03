#pragma once

#include "types.hpp"

enum Command : command_type {
  HALT = 0,
  PUSH,
  POP,
  LOADC,
  LOADRC,
  LOAD,
  LOADN,
  STORE,
  STOREN,
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
  NOT,
  JMP,
  JMPZ,
  JMPI,
  DUP,
  ALLOC,
  FREE,
  REALLOC
};

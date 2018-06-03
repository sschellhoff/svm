#pragma once

#include "types.hpp"

class Stack;

class SystemCalls {
private:
  Stack& memory;
public:
  SystemCalls(Stack& memory);
  void execute(command_type function);
};

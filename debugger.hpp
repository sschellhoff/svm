#pragma once

#include "vm.hpp"
#include "types.hpp"
#include <vector>

class Debugger {
private:
  VM vm;
public:
  void setProgram(std::vector<command_type> program);
  void run();
};

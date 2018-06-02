#pragma once

#include "vm.hpp"
#include "types.hpp"
#include <vector>

class Debugger {
private:
  VM vm;

  void debugStep();
  void printCommand(command_type* command_pos);
public:
  void setProgram(std::vector<command_type> program);
  void run();
};

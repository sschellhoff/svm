#pragma once

#include "vm.hpp"
#include "types.hpp"
#include <vector>

class Debugger {
private:
  VM vm;

  std::vector<command_type*> breakpoints;

  void debugStep();
  void runUntilBreakpoint();
  void restartProgram();
  void quitProgram();
  void printCommand(command_type* command_pos);
  void printCurrentCommand();
  void registerBreakpoint();
public:
  void setProgram(std::vector<command_type> program);
  void run();
};

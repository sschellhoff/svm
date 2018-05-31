#pragma once

#include "types.hpp"
#include "stack.hpp"
#include <vector>

class VM {
private:
  std::vector<command_type> program;
  command_type* IP;
  std::size_t IR;

  Stack memory;

  bool is_running;

  void fetchCommand();
  void executeCommand();

  void printStack() const;
public:
  VM();

  void setProgram(std::vector<command_type> program);
  void resetVM();
  void restartProgram();

  void executeStep();

  void runProgram();

  void debugProgram();

  bool isRunning() const;
};

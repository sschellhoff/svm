#pragma once

#include "types.hpp"
#include "stack.hpp"
#include <vector>
#include "system_calls.hpp"

class VM {
private:
  friend class Debugger;
  std::vector<command_type> program;
  command_type* IP;
  std::size_t IR;
  std::size_t BP;

  Stack memory;

  bool is_running;

  SystemCalls sysCalls;

  void fetchCommand();
  void executeCommand();

  void printStack() const;
  void printHeap() const;
  void printHeapEntries() const;
  void printRegisters() const;
public:
  VM();

  void setProgram(std::vector<command_type> program);
  void resetVM();
  void restartProgram();

  void executeStep();

  void run();

  bool isRunning() const;
};

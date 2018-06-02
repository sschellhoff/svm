#include "debugger.hpp"
#include "command_line_interface.hpp"
#include "command_info.hpp"
#include <iostream>
#include <string>

void Debugger::setProgram(std::vector<command_type> program) {
  vm.setProgram(program);
}

void Debugger::run() {
  CommandLineInterface cli;
  //cli.registerCommand("continue", [this]() { this->toNextBreakpoint(); });
  //cli.registerCommand("c", [this]() { this->toNextBreakpoint(); });
  //cli.registerCommand("quit", [this]() { this->quitProgram(); });
  //cli.registerCommand("restart", [this]() { this->restartProgram(); });
  //cli.registerCommand("r", [this]() { this->restartProgram(); });
  cli.registerCommand("step", [this]() { this->debugStep(); });
  cli.registerCommand("s", [this]() { this->debugStep(); });
  cli.registerCommand("printStack", [this]() { this->vm.printStack(); });
  cli.registerCommand("ps", [this]() { this->vm.printStack(); });
  cli.registerCommand("printRegisters", [this]() { this->vm.printRegisters(); });
  cli.registerCommand("pr", [this]() { this->vm.printRegisters(); });
  cli.registerCommand("printAll", [this]() { this->vm.printRegisters(); this->vm.printStack(); });
  cli.registerCommand("pa", [this]() { this->vm.printRegisters(); this->vm.printStack(); });
  cli.registerCommand("", []() { });
  while(vm.is_running) {
    cli.nextCommand();
  }
  std::cout << "Program done" << std::endl;
  cli.nextCommand();
}

void Debugger::debugStep() {
  printCommand(vm.IP);
  vm.fetchCommand();
  vm.executeCommand();
}

void Debugger::printCommand(command_type* command_pos) {
  auto command = *command_pos;
  Command com = static_cast<Command>(command);
  if(doesCommandExist(com)) {
    std::cout << translateCommand(com) << " " << (hasParameter(com) ? std::to_string(*(command_pos + 1)) : "") << std::endl;
  } else {
    std::cout << "Unknown command: " << command << std::endl;
  }
}

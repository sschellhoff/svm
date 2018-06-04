#include "debugger.hpp"
#include "command_line_interface.hpp"
#include "command_info.hpp"
#include <iostream>
#include <string>
#include <algorithm>

void Debugger::setProgram(std::vector<command_type> program) {
  vm.setProgram(program);
}

void Debugger::run() {
  CommandLineInterface cli;
  cli.registerCommand("help", [&]() { cli.printHelp(); });
  cli.registerCommand("h", [&]() { cli.printHelp(); });
  cli.registerCommand("continue", [this]() { this->runUntilBreakpoint(); });
  cli.registerCommand("c", [this]() { this->runUntilBreakpoint(); });
  cli.registerCommand("step", [this]() { this->debugStep(); });
  cli.registerCommand("s", [this]() { this->debugStep(); });
  cli.registerCommand("break", [this]() { this->registerBreakpoint(); });
  cli.registerCommand("b", [this]() { this->registerBreakpoint(); });
  cli.registerCommand("quit", [this]() { this->quitProgram(); });
  cli.registerCommand("restart", [this]() { this->restartProgram(); });
  cli.registerCommand("inspect", [this]() { this->printCurrentCommand(); });
  cli.registerCommand("stack", [this]() { this->vm.printStack(); });
  cli.registerCommand("heap", [this]() { this->vm.printHeap(); });
  cli.registerCommand("allocated", [this]() { this->vm.printHeapEntries(); });
  cli.registerCommand("registers", [this]() { this->vm.printRegisters(); });
  cli.registerCommand("show", [this]() { this->vm.printRegisters(); this->vm.printStack(); this->vm.printHeap(); this->printCurrentCommand(); });
  cli.registerCommand("", []() { });
  while(vm.is_running) {
    cli.nextCommand();
  }
  std::cout << "Program done" << std::endl;
  cli.nextCommand();
}

void Debugger::debugStep() {
  if(!vm.is_running) return;
  printCurrentCommand();
  vm.fetchCommand();
  vm.executeCommand();
}

void Debugger::runUntilBreakpoint() {
  while(vm.is_running) {
    vm.executeStep();
    auto address = vm.IP;
    if(std::find(breakpoints.begin(), breakpoints.end(), address) != breakpoints.end()) {
      return;
    }
  }
}

void Debugger::restartProgram() {
  vm.restartProgram();
}

void Debugger::quitProgram() {
  vm.is_running = false;
}

void Debugger::printCommand(command_type* command_pos) {
  auto command = *command_pos;
  Command com = static_cast<Command>(command);
  if(doesCommandExist(com)) {
    std::cout << "[" << std::to_string(command_pos - &vm.program[0]) << "] " << translateCommand(com) << " " << (hasParameter(com) ? std::to_string(*(command_pos + 1)) : "") << std::endl;
  } else {
    std::cout << "Unknown command: " << command << std::endl;
  }
}

void Debugger::printCurrentCommand() {
  printCommand(vm.IP);
}

void Debugger::registerBreakpoint() {
  std::cout << "Address: ";
  command_type breakpoint;
  if(std::cin >> breakpoint) {
    breakpoints.push_back(&vm.program[0] + breakpoint);
      std::cout << "registered breakpoint at " << breakpoint << std::endl;
  } else {
    std::cout << "Value is no breakpoint!" << std::endl;
  }
  std::cin.clear();
  std::cin.ignore(INT_MAX, '\n');
}

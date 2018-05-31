#include "command_line_interface.hpp"
#include <iostream>

void CommandLineInterface::registerCommand(const std::string &command, std::function<void()> function) {
  callbacks[command] = function;
}

void CommandLineInterface::nextCommand() {
  if(callbacks.empty()) {
    return;
  }

  std::string command;
  std::cout << "> ";
  std::getline(std::cin, command);
  while(callbacks.find(command) == callbacks.end()) {
    std::cout << "Unknown command!" << std::endl;
    std::cout << "> ";
    std::getline(std::cin, command);
  }
  callbacks[command]();
}

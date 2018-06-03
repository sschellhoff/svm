#include "system_calls.hpp"
#include "stack.hpp"
#include <iostream>
#include <string>

SystemCalls::SystemCalls(Stack& memory) : memory(memory) {
}

SystemCalls::~SystemCalls() {
}

void SystemCalls::execute(command_type function) {
  switch(function) {
    case 0: {
      auto address = memory.pop();
      std::cout << static_cast<char>(memory.data[address]);
    }
    break;
    case 1: {
      std::string value;
      std::getline(std::cin, value);
      for(const auto c : value) {
        memory.push(c);
      }
      memory.push(0);
    }
    break;
    default:
      std::cerr << "Unknown systemcall: " << function << std::endl;
  }
}

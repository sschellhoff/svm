#include "vm.hpp"
#include "commands.hpp"
#include <iostream>

VM::VM() : is_running(false) {
  memory.push(0);
}

void VM::fetchCommand() {
  IR = *IP;
  IP++;
}

void VM::executeCommand() {
  switch(IR) {
    case Commands::HALT:
      is_running = false;
    break;
    case Commands::LOADC: {
      fetchCommand(); // fetch constants address
      auto constant = IR; // get constant
      memory.push(constant); // push constant on stack
    }
    break;
    case Commands::ADD: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a+b);
    }
    break;
    /*case Commands::SUB: {
    }
    break;
    case Commands::MULT: {
    }
    break;
    case Commands::DIV: {
    }
    break;
    case Commands::MOD: {
    }
    break;
    case Commands::AND: {
    }
    break;
    case Commands::OR: {
    }
    break;
    case Commands::EQ: {
    }
    break;
    case Commands::NEQ: {
    }
    break;
    case Commands::LE: {
    }
    break;
    case Commands::LT: {
    }
    break;
    case Commands::GE: {
    }
    break;
    case Commands::GT: {
    }
    break;*/
    default:
    // RUNTIME ERROR
    std::cerr << "unknown command: " << IR << std::endl;
    break;
  }
}

void VM::setProgram(std::vector<command_type> program) {
  this->program = program;
  restartProgram();
}

void VM::resetVM() {
  memory.reset();
  restartProgram();
}

void VM::restartProgram() {
  IP = &program[0];
  is_running = true;
}

void VM::executeStep() {
  fetchCommand();
  executeCommand();
}

void VM::runProgram() {
  while(is_running) {
    executeStep();
  }
}

void VM::debugProgram() {
  while(is_running) {
    printStack();
    executeStep();
  }
  printStack();
}

bool VM::isRunning() const {
  return is_running;
}

void VM::printStack() const {
  std::cout << "[ ";
  for(auto i = memory.data; i < memory.SP; i++) {
    std::cout << *i << " ";
  }
  std::cout << "]" << std::endl;
}

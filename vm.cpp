#include "vm.hpp"
#include "commands.hpp"
#include <iostream>
#include "command_line_interface.hpp"

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
    case Commands::PUSH: {
      fetchCommand(); // fetch value
      auto size = IR; // get value
      memory.reserveStackSpace(size);
    }
    break;
    case Commands::POP: {
      fetchCommand(); // fetch value
      auto size = IR; // get value
      memory.removeStackSpace(size);
    }
    break;
    case Commands::LOADC: {
      fetchCommand(); // fetch constant
      auto constant = IR; // get constant
      memory.push(constant);
    }
    break;
    case Commands::LOAD: {
      auto var_addr = memory.pop();
      auto value = memory.load(var_addr);
      memory.push(value);
    }
    break;
    case Commands::STORE: {
      auto var_addr = memory.pop();
      auto value = memory.pop();
      memory.store(var_addr, value);
    }
    break;
    case Commands::ADD: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a+b);
    }
    break;
    case Commands::SUB: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a-b);
    }
    break;
    case Commands::MULT: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a*b);
    }
    break;
    case Commands::DIV: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a/b);
    }
    break;
    case Commands::MOD: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a%b);
    }
    break;
    case Commands::AND_B: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a&b);
    }
    break;
    case Commands::OR_B: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a|b);
    }
    break;;
    case Commands::XOR_B: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a^b);
    }
    break;
    case Commands::NOT_B: {
      const auto a = memory.pop();
      memory.push(~a);
    }
    break;
    case Commands::EQ: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push((a==b) ? TRUE_CONSTANT : FALSE_CONSTANT);
    }
    break;
    case Commands::NEQ: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push((a!=b) ? TRUE_CONSTANT : FALSE_CONSTANT);
    }
    break;
    case Commands::LE: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push((a<=b) ? TRUE_CONSTANT : FALSE_CONSTANT);
    }
    break;
    case Commands::LT: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push((a<b) ? TRUE_CONSTANT : FALSE_CONSTANT);
    }
    break;
    case Commands::GE: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push((a>=b) ? TRUE_CONSTANT : FALSE_CONSTANT);
    }
    break;
    case Commands::GT: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push((a>b) ? TRUE_CONSTANT : FALSE_CONSTANT);
    }
    break;
    case Commands::NEG: {
      const auto a = memory.pop();
      memory.push(-a);
    }
    break;
    case Commands::NOT: {
      const auto a = memory.pop();
      memory.push((a == FALSE_CONSTANT) ? TRUE_CONSTANT : FALSE_CONSTANT);
    }
    break;
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
  CommandLineInterface cli;
  cli.registerCommand("stack", [this]() { this->printStack(); });
  cli.registerCommand("", []() { });
  while(is_running) {
    cli.nextCommand();
    executeStep();
  }
  std::cout << "Program done" << std::endl;
  cli.nextCommand();
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

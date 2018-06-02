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
    case Command::HALT:
      is_running = false;
    break;
    case Command::PUSH: {
      fetchCommand(); // fetch value
      auto size = IR; // get value
      memory.reserveStackSpace(size);
    }
    break;
    case Command::POP: {
      fetchCommand(); // fetch value
      auto size = IR; // get value
      memory.removeStackSpace(size);
    }
    break;
    case Command::LOADC: {
      fetchCommand(); // fetch constant
      auto constant = IR; // get constant
      memory.push(constant);
    }
    break;
    case Command::LOAD: {
      auto var_addr = memory.pop();
      auto value = memory.load(var_addr);
      memory.push(value);
    }
    break;
    case Command::LOADN: {
      fetchCommand(); // fetch n
      auto n = IR; // get n
      auto var_addr = memory.pop();
      for(auto i = 0; i < n; i++) {
        auto value = memory.load(var_addr + i);
        memory.push(value);
      }
    }
    break;
    case Command::STORE: {
      auto var_addr = memory.pop();
      auto value = memory.pop();
      memory.store(var_addr, value);
    }
    break;
    case Command::STOREN: {
      fetchCommand(); // fetch n
      auto n = IR; // get n
      auto var_addr = memory.pop();
      for(int i = n - 1; i >= 0; i--) {
        auto value = memory.pop();
        memory.store(var_addr + i, value);
      }
    }
    break;
    case Command::ADD: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a+b);
    }
    break;
    case Command::SUB: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a-b);
    }
    break;
    case Command::MULT: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a*b);
    }
    break;
    case Command::DIV: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a/b);
    }
    break;
    case Command::MOD: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a%b);
    }
    break;
    case Command::AND_B: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a&b);
    }
    break;
    case Command::OR_B: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a|b);
    }
    break;;
    case Command::XOR_B: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push(a^b);
    }
    break;
    case Command::NOT_B: {
      const auto a = memory.pop();
      memory.push(~a);
    }
    break;
    case Command::EQ: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push((a==b) ? TRUE_CONSTANT : FALSE_CONSTANT);
    }
    break;
    case Command::NEQ: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push((a!=b) ? TRUE_CONSTANT : FALSE_CONSTANT);
    }
    break;
    case Command::LE: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push((a<=b) ? TRUE_CONSTANT : FALSE_CONSTANT);
    }
    break;
    case Command::LT: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push((a<b) ? TRUE_CONSTANT : FALSE_CONSTANT);
    }
    break;
    case Command::GE: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push((a>=b) ? TRUE_CONSTANT : FALSE_CONSTANT);
    }
    break;
    case Command::GT: {
      const auto b = memory.pop();
      const auto a = memory.pop();
      memory.push((a>b) ? TRUE_CONSTANT : FALSE_CONSTANT);
    }
    break;
    case Command::NEG: {
      const auto a = memory.pop();
      memory.push(-a);
    }
    break;
    case Command::NOT: {
      const auto a = memory.pop();
      memory.push((a == FALSE_CONSTANT) ? TRUE_CONSTANT : FALSE_CONSTANT);
    }
    break;
    case Command::JMP: {
      fetchCommand();
      auto target = IR;
      IP = &program[0] + target;
    }
    break;
    case Command::JMPZ: {
      fetchCommand();
      auto target = IR;
      auto condition = memory.pop();
      if(condition == FALSE_CONSTANT) {
        IP = &program[0] + target;
      }
    }
    break;
    case Command::JMPI: {
      fetchCommand();
      auto targetBase = IR;
      auto relative = memory.pop();
      IP = &program[0] + targetBase + relative;
    }
    break;
    case Command::DUP:
    memory.dup();
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

void VM::run() {
  while(is_running) {
    executeStep();
  }
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

void VM::printHeap() const {
  std::cout << "[ ";
  if(memory.heapEntries.size() > 0) {
    auto start = memory.heapEntries[0].address;
    for(auto i = memory.data + start; i <= memory.data + memory.MAX_ADDRESS; i++) {
      std::cout << *i << " ";
    }
  }
  std::cout << "]" << std::endl;
}

void VM::printRegisters() const {
  std::cout << "IP: " << (IP - &program[0]) << std::endl
  << "IR: " << IR << std::endl
  << "SP: " << (memory.SP - memory.data)
  << "HP: " << (memory.HP - memory.data) << std::endl;
}

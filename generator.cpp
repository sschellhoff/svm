#include "generator.hpp"


std::vector<command_type> makeProgram(std::vector<command_type> code) {
  code.push_back(Command::HALT);
  return code;
}

std::vector<command_type> loadConstant(command_type value) {
  return { Command::LOADC, value };
}

std::vector<command_type> addition(command_type op1, command_type op2) {
  return {
    Command::LOADC, op1,
    Command::LOADC, op2,
    Command::ADD
  };
}

std::vector<command_type> addition(std::vector<command_type> op1, std::vector<command_type> op2) {
  op1.insert(op1.end(), op2.begin(), op2.end());
  op1.push_back(Command::ADD);
  return op1;
}

std::vector<command_type> equals(std::vector<command_type> op1, std::vector<command_type> op2) {
  op1.insert(op1.end(), op2.begin(), op2.end());
  op1.push_back(Command::EQ);
  return op1;
}

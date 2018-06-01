#include "generator.hpp"

#define APPEND(fst, snd) fst.insert(fst.end(), snd.begin(), snd.end())

std::vector<command_type> makeProgram(std::vector<command_type> code) {
  code.push_back(Command::HALT);
  return code;
}

std::vector<command_type> environment(command_type size, std::vector<command_type> code) {
  std::vector<command_type> result = {Command::PUSH, size};
  APPEND(result, code);
  result.push_back(Command::POP);
  result.push_back(size);
  return result;
}

std::vector<command_type> concat(std::vector<command_type> fst, std::vector<command_type> snd) {
  APPEND(fst, snd);
  return fst;
}

std::vector<command_type> loadConstant(command_type value) {
  return { Command::LOADC, value };
}

std::vector<command_type> loadVariable() {
  return {
    Command::LOAD
  };
}

std::vector<command_type> loadVariable(command_type addr) {
  return {
    Command::LOADC, addr,
    Command::LOAD
  };
}

std::vector<command_type> storeVariable() {
  return {
    Command::STORE
  };
}

std::vector<command_type> storeVariable(command_type addr) {
  return {
    Command::LOADC, addr,
    Command::STORE
  };
}

std::vector<command_type> assign(command_type addr, std::vector<command_type> value) {
  return concat(value, storeVariable(addr));
}

std::vector<command_type> if_expr(command_type end_label, std::vector<command_type> condition, std::vector<command_type> then_part) {
  // condition
  // jmpz END
  // then_part
  // END:
  auto result = concat(condition, {Command::JMPZ, end_label});
  APPEND(result, then_part);
  return result;
}

std::vector<command_type> if_expr(command_type else_label, command_type end_label, std::vector<command_type> condition, std::vector<command_type> then_part, std::vector<command_type> else_part) {
  // condition
  // jmpz ELSE
  // then_part
  // jmp END
  // ELSE:
  // else_part
  // END
  auto result = if_expr(else_label, condition, concat(then_part, {Command::JMP, end_label}));
  return concat(result, else_part);
}

std::vector<command_type> addition(command_type op1, command_type op2) {
  return {
    Command::LOADC, op1,
    Command::LOADC, op2,
    Command::ADD
  };
}

std::vector<command_type> addition(std::vector<command_type> op1, std::vector<command_type> op2) {
  APPEND(op1, op2);
  op1.push_back(Command::ADD);
  return op1;
}

std::vector<command_type> equals(std::vector<command_type> op1, std::vector<command_type> op2) {
  APPEND(op1, op2);
  op1.push_back(Command::EQ);
  return op1;
}

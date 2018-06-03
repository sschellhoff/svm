#include "command_info.hpp"
#include <map>
#include <vector>
#include <algorithm>

#define MAKE_TO_STRING_PAIR(name) {Command::name, ""#name}
#define MAKE_TO_NAME_PAIR(name) {""#name, Command::name}

const static std::map<std::string, Command> name_command = {
  MAKE_TO_NAME_PAIR(HALT),
  MAKE_TO_NAME_PAIR(PUSH),
  MAKE_TO_NAME_PAIR(POP),
  MAKE_TO_NAME_PAIR(LOADC),
  MAKE_TO_NAME_PAIR(LOADRC),
  MAKE_TO_NAME_PAIR(LOAD),
  MAKE_TO_NAME_PAIR(LOADN),
  MAKE_TO_NAME_PAIR(STORE),
  MAKE_TO_NAME_PAIR(STOREN),
  MAKE_TO_NAME_PAIR(ADD),
  MAKE_TO_NAME_PAIR(SUB),
  MAKE_TO_NAME_PAIR(MULT),
  MAKE_TO_NAME_PAIR(DIV),
  MAKE_TO_NAME_PAIR(MOD),
  MAKE_TO_NAME_PAIR(AND_B),
  MAKE_TO_NAME_PAIR(OR_B),
  MAKE_TO_NAME_PAIR(XOR_B),
  MAKE_TO_NAME_PAIR(NOT_B),
  MAKE_TO_NAME_PAIR(EQ),
  MAKE_TO_NAME_PAIR(NEQ),
  MAKE_TO_NAME_PAIR(LE),
  MAKE_TO_NAME_PAIR(LT),
  MAKE_TO_NAME_PAIR(GE),
  MAKE_TO_NAME_PAIR(GT),
  MAKE_TO_NAME_PAIR(NEG),
  MAKE_TO_NAME_PAIR(NOT),
  MAKE_TO_NAME_PAIR(JMP),
  MAKE_TO_NAME_PAIR(JMPZ),
  MAKE_TO_NAME_PAIR(JMPI),
  MAKE_TO_NAME_PAIR(DUP),
  MAKE_TO_NAME_PAIR(ALLOC),
  MAKE_TO_NAME_PAIR(FREE),
  MAKE_TO_NAME_PAIR(REALLOC),
  MAKE_TO_NAME_PAIR(CALL),
  MAKE_TO_NAME_PAIR(RET)
};

const static std::map<Command, std::string> command_name = {
  MAKE_TO_STRING_PAIR(HALT),
  MAKE_TO_STRING_PAIR(PUSH),
  MAKE_TO_STRING_PAIR(POP),
  MAKE_TO_STRING_PAIR(LOADC),
  MAKE_TO_STRING_PAIR(LOADRC),
  MAKE_TO_STRING_PAIR(LOAD),
  MAKE_TO_STRING_PAIR(LOADN),
  MAKE_TO_STRING_PAIR(STORE),
  MAKE_TO_STRING_PAIR(STOREN),
  MAKE_TO_STRING_PAIR(ADD),
  MAKE_TO_STRING_PAIR(SUB),
  MAKE_TO_STRING_PAIR(MULT),
  MAKE_TO_STRING_PAIR(DIV),
  MAKE_TO_STRING_PAIR(MOD),
  MAKE_TO_STRING_PAIR(AND_B),
  MAKE_TO_STRING_PAIR(OR_B),
  MAKE_TO_STRING_PAIR(XOR_B),
  MAKE_TO_STRING_PAIR(NOT_B),
  MAKE_TO_STRING_PAIR(EQ),
  MAKE_TO_STRING_PAIR(NEQ),
  MAKE_TO_STRING_PAIR(LE),
  MAKE_TO_STRING_PAIR(LT),
  MAKE_TO_STRING_PAIR(GE),
  MAKE_TO_STRING_PAIR(GT),
  MAKE_TO_STRING_PAIR(NEG),
  MAKE_TO_STRING_PAIR(NOT),
  MAKE_TO_STRING_PAIR(JMP),
  MAKE_TO_STRING_PAIR(JMPZ),
  MAKE_TO_STRING_PAIR(JMPI),
  MAKE_TO_STRING_PAIR(DUP),
  MAKE_TO_STRING_PAIR(ALLOC),
  MAKE_TO_STRING_PAIR(FREE),
  MAKE_TO_STRING_PAIR(REALLOC),
  MAKE_TO_STRING_PAIR(CALL),
  MAKE_TO_STRING_PAIR(RET)
};

const static std::vector<Command> has_parameter = {
  Command::PUSH, Command::POP, Command::LOADC, Command::LOADRC, LOADN, STOREN, Command::JMP, Command::JMPZ, Command::JMPI, Command::CALL
};

bool doesCommandExist(const std::string &command) {
  return name_command.find(command) != name_command.end();
}

bool doesCommandExist(Command command) {
  return command_name.find(command) != command_name.end();
}

bool hasParameter(Command command) {
  return std::find(has_parameter.begin(), has_parameter.end(), command) != has_parameter.end();
}

std::string translateCommand(Command command) {
  return command_name.find(command)->second;
}

Command translateCommand(const std::string &command) {
  return name_command.find(command)->second;
}

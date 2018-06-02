#include "assembler.hpp"
#include <map>
#include <cctype>
#include "command_info.hpp"
#include <iostream>

enum TokenType {
  WHITESPACE,
  SOURCE,
  TARGET,
  COMMAND,
  NUMBER
};

struct TokenValue {
  std::string str;
  int_type no;
  command_type cmd;
};

struct Token {
  TokenType type;
  TokenValue value;

  Token() {}
  Token(TokenType type) : type(type) {}
};

std::vector<command_type> error_program() {
  return {Command::HALT};
}

std::vector<command_type> assemble(const std::string & program) {
  std::map<std::string, std::vector<std::size_t>> unknown_label_positions;
  std::map<std::string, std::size_t> label_positions;

  std::vector<command_type> result;

  std::size_t pos = 0;
  std::vector<Token> tokens;

  while(pos < program.length()) {
    auto start_pos = pos;
    auto current = program[pos];

    if(std::isspace(current)) {
      for(;pos < program.length() && std::isspace(current); current = program[++pos]) {
      }
      Token ws(TokenType::WHITESPACE);
      tokens.push_back(ws);
      continue;
    }

    if(std::isalpha(current)) {
      for(;pos < program.length() && std::isalpha(current); current = program[++pos]) {
      }
      auto value = program.substr(start_pos, pos-start_pos);
      if(pos < program.length() && current == ':') {
        pos++;
        Token target(TokenType::TARGET);
        target.value.str = value;
        tokens.push_back(target);
      } else {
        if(doesCommandExist(value)) {
          Token cmd(TokenType::COMMAND);
          cmd.value.cmd = translateCommand(value);
          tokens.push_back(cmd);
        } else {
          Token src(TokenType::SOURCE);
          src.value.str = value;
          tokens.push_back(src);
        }
      }
      continue;
    }

    if(std::isdigit(current)) {
      for(;pos < program.length() && std::isdigit(current); current = program[++pos]) {
      }
      auto value = std::stoi(program.substr(start_pos, pos-start_pos));
      Token no(TokenType::NUMBER);
      no.value.no = value;
      tokens.push_back(no);
      continue;
    }

    // error
    std::cerr << "Unknown token" << std::endl;
    return error_program();
  }

  pos = 0;
  while(pos < tokens.size()) {
    switch(tokens[pos].type) {
      case TokenType::WHITESPACE:
      break;
      case TokenType::TARGET: {
        auto target = tokens[pos].value.str;
        if(label_positions.find(target) != label_positions.end()) {
          std::cerr << "Target is already defined: " << target << std::endl;
          return error_program();
        }
        if(unknown_label_positions.find(target) != unknown_label_positions.end()) {
          for(auto label : unknown_label_positions.find(target)->second) {
            result[label] = result.size();
          }
          unknown_label_positions.erase(unknown_label_positions.find(target));
        }
        label_positions[target] = result.size();
      }
      break;
      case TokenType::SOURCE: {
        auto source = tokens[pos].value.str;
        std::cout << "SOURCE: " << source << std::endl;
        if(label_positions.find(source) != label_positions.end()) {
          result.push_back(label_positions.find(source)->second);
        } else {
          unknown_label_positions[source].push_back(result.size());
          result.push_back(-1);
        }
      }
      break;
      case TokenType::NUMBER:
        result.push_back(tokens[pos].value.no);
      break;
      case TokenType::COMMAND:
        result.push_back(tokens[pos].value.cmd);
        break;
      default: {
        std::cerr << "Unknown tokentype" << std::endl;
        return error_program();
      }

    }
    pos++;
  }
  if(unknown_label_positions.size() > 0) {
    std::cerr << "There are are missing targets" << std::endl;
  }

  return result;
}

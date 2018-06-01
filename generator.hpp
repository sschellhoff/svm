#pragma once

#include <vector>
#include "commands.hpp"

std::vector<command_type> makeProgram(std::vector<command_type> code);

std::vector<command_type> environment(command_type size, std::vector<command_type> code);

std::vector<command_type> concat(std::vector<command_type> fst, std::vector<command_type> snd);

std::vector<command_type> loadConstant(command_type value);

std::vector<command_type> loadVariable();

std::vector<command_type> loadVariable(command_type addr);

std::vector<command_type> storeVariable();

std::vector<command_type> storeVariable(command_type addr);

std::vector<command_type> assign(command_type addr, std::vector<command_type> value);

std::vector<command_type> if_expr(command_type end_label, std::vector<command_type> condition, std::vector<command_type> then_part);

std::vector<command_type> if_expr(command_type else_label, command_type end_label, std::vector<command_type> condition, std::vector<command_type> then_part, std::vector<command_type> else_part);

std::vector<command_type> addition(command_type op1, command_type op2);

std::vector<command_type> addition(std::vector<command_type> op1, std::vector<command_type> op2);

std::vector<command_type> equals(std::vector<command_type> op1, std::vector<command_type> op2);

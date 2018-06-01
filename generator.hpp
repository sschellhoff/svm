#pragma once

#include <vector>
#include "commands.hpp"

std::vector<command_type> makeProgram(std::vector<command_type> code);

std::vector<command_type> loadConstant(command_type value);

std::vector<command_type> addition(command_type op1, command_type op2);

std::vector<command_type> addition(std::vector<command_type> op1, std::vector<command_type> op2);

std::vector<command_type> equals(std::vector<command_type> op1, std::vector<command_type> op2);

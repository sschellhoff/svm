#pragma once

#include <string>
#include "commands.hpp"

bool doesCommandExist(const std::string &command);
bool doesCommandExist(Command command);

std::string translateCommand(Command command);
Command translateCommand(const std::string &command);

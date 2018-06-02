#pragma once

#include <string>
#include <functional>
#include <map>

class CommandLineInterface {
private:
  std::map<std::string, std::function<void()>> callbacks;
public:
  void registerCommand(const std::string &command, std::function<void()> function);
  void nextCommand();
  void printHelp();
};

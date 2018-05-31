#include <iostream>
#include "vm.hpp"
#include "commands.hpp"

int main(int argc, char* argv[]) {
  VM vm;
  vm.setProgram({Commands::LOADC, 13, Commands::LOADC, 37, Commands::ADD, Commands::LOADC, 8, Commands::SUB, LOADC, 42, Commands::EQ, Commands::HALT});

  vm.debugProgram();

  return 0;
}

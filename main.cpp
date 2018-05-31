#include <iostream>
#include "vm.hpp"
#include "commands.hpp"

int main(int argc, char* argv[]) {
  VM vm;
  vm.setProgram({Commands::PUSH, 2, Commands::POP, 2, Commands::HALT});

  vm.debugProgram();

  return 0;
}

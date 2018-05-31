#include <iostream>
#include "vm.hpp"
#include "commands.hpp"

int main(int argc, char* argv[]) {
  VM vm;
  vm.setProgram({
    Commands::LOADC, 13,
    Commands::DUP,
    Commands::HALT
  });

  vm.debugProgram();

  return 0;
}

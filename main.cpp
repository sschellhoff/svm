#include <iostream>
#include "vm.hpp"
#include "commands.hpp"

int main(int argc, char* argv[]) {
  VM vm;
  vm.setProgram({
    Commands::PUSH, 2,
    Commands::LOADC, 13,
    Commands::LOADC, 1,
    Commands::STORE,
    Commands::LOADC, 37,
    Commands::LOADC, 2,
    Commands::STORE,
    Commands::LOADC, 1,
    Commands::LOAD,
    Commands::LOADC, 2,
    Commands::LOAD,
    Commands::ADD,
    Commands::POP, 3,
    Commands::HALT
  });

  vm.debugProgram();

  return 0;
}

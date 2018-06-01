#include <iostream>
#include "vm.hpp"
#include "commands.hpp"

int main(int argc, char* argv[]) {
  VM vm;
  vm.setProgram({
    Command::LOADC, 13,
    Command::DUP,
    Command::HALT
  });

  vm.debugProgram();

  return 0;
}

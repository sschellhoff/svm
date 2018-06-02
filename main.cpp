#include "debugger.hpp"
#include "generator.hpp"
#include "assembler.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

int main(int argc, char* argv[]) {
  Debugger vm;
  // a = b + b * c
  // with addr(a) = 1, addr(b) = 2, addr(c) = 3
  // with value(a) = undefined, value(b) = 3, value(c) = 7
  // makeProgram(environment(3, concat(assign(2, loadConstant(3)), concat(assign(3, loadConstant(7)), assign(1, addition(loadVariable(2), loadVariable(3)))))))

  // if 1 = 1 { PUSH(3); }
  // makeProgram(if_expr(9, equals(loadConstant(1), loadConstant(2)), loadConstant(3)))

  std::string code = "LOADC 10 "
                     "LOADC 12 "
                     "ADD TEST:"
                     "HALT";

  if(argc == 2) {
    std::ifstream t(argv[1]);
    std::string str((std::istreambuf_iterator<char>(t)),
                   std::istreambuf_iterator<char>());
    code = str;
  }

  auto program = assemble(code);
  vm.setProgram(program);

  vm.run();

  return 0;
}

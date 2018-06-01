#include "vm.hpp"
#include "generator.hpp"

int main(int argc, char* argv[]) {
  VM vm;
  // a = b + b * c
  // with addr(a) = 1, addr(b) = 2, addr(c) = 3
  // with value(a) = undefined, value(b) = 3, value(c) = 7
  // makeProgram(environment(3, concat(assign(2, loadConstant(3)), concat(assign(3, loadConstant(7)), assign(1, addition(loadVariable(2), loadVariable(3)))))))

  // if 1 = 1 { PUSH(3); }
  // makeProgram(if_expr(9, equals(loadConstant(1), loadConstant(2)), loadConstant(3)))
  vm.setProgram(makeProgram({}));

  vm.debugProgram();

  return 0;
}

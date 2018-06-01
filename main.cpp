#include "vm.hpp"
#include "generator.hpp"

int main(int argc, char* argv[]) {
  VM vm;
  vm.setProgram(
    makeProgram(
      equals(
        addition(
          addition(
            loadConstant(13),
            loadConstant(37)
          ),
          loadConstant(-42)
        ),
        loadConstant(8)
      )
    )
  );

  vm.debugProgram();

  return 0;
}

#include "stack.hpp"

Stack::Stack() : SP(data) {
}

void Stack::push(int_type value) {
  *SP = value;
  SP++;
}

int_type Stack::pop() {
  SP--;
  return *SP;
}

bool Stack::isEmpty() const {
  return SP == data;
}

void Stack::reset() {
  SP = data;
}

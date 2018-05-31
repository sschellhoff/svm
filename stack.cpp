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

int_type Stack::load(int_type address) {
  return *(data+address);
}

void Stack::store(int_type address, int_type value) {
  *(data+address) = value;
}

void Stack::dup() {
  this->push(*(SP-1));
}

void Stack::reserveStackSpace(int_type size) {
  SP += size;
}

void Stack::removeStackSpace(int_type size) {
  SP -= size;
}

bool Stack::isEmpty() const {
  return SP == data;
}

void Stack::reset() {
  SP = data;
}

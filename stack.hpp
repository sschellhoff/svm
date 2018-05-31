#pragma once

#include "types.hpp"

struct Stack {
  static constexpr std::size_t MAX_ADDRESS = 1048576; // 4mb, (word-size: 4 byte)
  int_type data[MAX_ADDRESS + 1];
  int_type* SP;

  Stack();
  void push(int_type value);
  int_type pop();

  int_type load(int_type address);
  void store(int_type address, int_type value);

  void reserveStackSpace(int_type size);
  void removeStackSpace(int_type size);

  bool isEmpty() const;
  void reset();
};

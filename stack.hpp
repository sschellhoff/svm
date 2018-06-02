#pragma once

#include "types.hpp"
#include <cstddef>
#include <vector>

struct Stack {
  static constexpr std::size_t MAX_ADDRESS = 1048576; // 4mb, (word-size: 4 byte)
  int_type data[MAX_ADDRESS + 1];
  int_type* SP;
  int_type* HP;
  struct HeapData {
    int_type address;
    int_type size;
  };

  std::vector<HeapData> heapEntries;

  Stack();
  void push(int_type value);
  int_type pop();

  int_type load(int_type address);
  void store(int_type address, int_type value);

  void dup();

  void reserveStackSpace(int_type size);
  void removeStackSpace(int_type size);

  int_type reserveHeapSpace(int_type size);
  void removeHeapSpace(int_type address);
  int_type resizeHeapSpace(int_type address, int_type new_size);

  bool isEmpty() const;
  void reset();
};

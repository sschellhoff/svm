#include "stack.hpp"
#include <functional>
#include <cstring>

Stack::Stack() : SP(data), HP(SP + MAX_ADDRESS / 2) {
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

int_type Stack::reserveHeapSpace(int_type size) {
  auto last = MAX_ADDRESS + 1; // top

  for(const auto &entry : heapEntries) {
    if(last - (entry.address + entry.size) >= size) {
      HeapData newEntry;
      newEntry.address = entry.address + entry.size;
      newEntry.size = size;
      heapEntries.push_back(newEntry);
      std::sort(heapEntries.begin(), heapEntries.end(), [](HeapData a, HeapData b) { return a.address > b.address; });
      return newEntry.address;
    }
  }

  return 0;
}

void Stack::removeHeapSpace(int_type address) {
  for(auto it = heapEntries.begin(); it != heapEntries.end(); it++) {
    if(it->address == address) {
      heapEntries.erase(it);
      return;
    }
  }
}

int_type Stack::resizeHeapSpace(int_type address, int_type new_size) {
  auto it = std::find_if(heapEntries.begin(), heapEntries.end(), [address](HeapData data) { return data.address == address; });
  if(it == heapEntries.end()) {
    return reserveHeapSpace(new_size);
  }
  auto size = it->size;
  auto next = it + 1;
  if(next != heapEntries.end()) {
    if(next->address - it->address >= new_size) {
      it->size = new_size;
      return address;
    }
  }
  removeHeapSpace(address);
  auto new_address = reserveHeapSpace(new_size);
  if(new_address == 0) {
    return 0;
  }
  std::memcpy(&data[new_address], &data[address], size);
  return new_address;
}

bool Stack::isEmpty() const {
  return SP == data;
}

void Stack::reset() {
  SP = data;
}

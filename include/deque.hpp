#pragma once

#include <iostream>
#include <stdexcept>

template <typename T> class Deque {
private:
  T *elems;        // The circular buffer representing the deque
  size_t cap;      // Total capacity of the buffer
  size_t frontIdx; // Index of the front element in the deque
  size_t backIdx;  // Index of the rear element in the deque
  size_t sz;       // Number of elements in the deque

  // Resizes the buffer when it reaches capacity
  void resize() {
    size_t newCap = (cap == 0) ? 1 : cap * 2; // New capacity
    T *newElems = new T[newCap];              // New buffer

    for (size_t i = 0; i < sz; ++i) {
      newElems[i] = elems[(frontIdx + i) % cap]; // Copy elements
    }

    delete[] elems; // Free old buffer
    elems = newElems;
    cap = newCap;
    frontIdx = 0;
    backIdx = sz;
  }

public:
  Deque() : elems(nullptr), cap(0), frontIdx(0), backIdx(0), sz(0) {}

  ~Deque() { delete[] elems; }

  void push_front(const T &val) {
    if (sz == cap) {
      resize();
    }

    frontIdx = (frontIdx - 1 + cap) % cap;
    elems[frontIdx] = val;
    ++sz;
  }

  void push_back(const T &val) {
    if (sz == cap) {
      resize();
    }

    elems[backIdx] = val;
    backIdx = (backIdx + 1) % cap;
    ++sz;
  }

  void pop_front() {
    if (sz == 0) {
      throw std::out_of_range("Deque is empty");
    }

    frontIdx = (frontIdx + 1) % cap;
    --sz;
  }

  void pop_back() {
    if (sz == 0) {
      throw std::out_of_range("Deque is empty");
    }

    backIdx = (backIdx - 1 + cap) % cap;
    --sz;
  }

  T &operator[](int idx) {
    if (idx < 0 || idx >= static_cast<int>(sz)) {
      throw std::out_of_range("Index out of range");
    }
    return elems[(frontIdx + idx) % cap];
  }

  // Returns the number of elements in the deque
  size_t size() const { return sz; }

  // Removes all elements from the deque
  void clear() {
    sz = 0;
    frontIdx = backIdx = 0;
  }
};
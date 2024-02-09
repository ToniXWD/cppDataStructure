#pragma once

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T> class Vector {
private:
  T *elems;   // Pointer to the dynamic array
  size_t cap; // Capacity of the array
  size_t sz;  // Number of elements in the array

public:
  // Constructor
  Vector() : elems(nullptr), cap(0), sz(0) {}

  Vector(size_t capacity) : elems(nullptr), cap(capacity), sz(0) {
    elems = new T[capacity];
  }

  // Destructor
  ~Vector() {
    for (size_t i = 0; i < sz; ++i) {
      elems[i].~T(); // Call the destructor for each element
    }
    delete[] elems; // Release the allocated memory
  }

  // Copy constructor
  Vector(const Vector &other) : cap(other.cap), sz(other.sz) {
    elems = new T[cap];
    std::copy(other.elems, other.elems + sz, elems);
  }

  // Copy assignment operator
  Vector &operator=(const Vector &other) {
    if (this != &other) { // Protect against self-assignment
      // Allocate new memory and copy the elements
      T *newElems = new T[other.cap];
      std::copy(other.elems, other.elems + other.sz, newElems);

      this->clear();
      // Delete the old array
      delete[] elems;

      // Assign the new array and update the size and capacity
      elems = newElems;
      cap = other.cap;
      sz = other.sz;
    }
    return *this; // Return a self-reference
  }

  Vector &operator=(Vector &&other) {
    if (this != &other) {
      this->clear();
      delete[] elems; // Release the current array

      elems = other.elems; // Steal the data
      sz = other.sz;
      cap = other.cap;

      other.elems = nullptr; // Reset the other vector
      other.sz = 0;
      other.cap = 0;
    }
    return *this;
  }

  // Add an element to the end of the array
  void push_back(const T &val) {
    if (sz == cap) {
      reserve(cap == 0 ? 1 : 2 * cap); // Expand capacity if array is full
    }
    elems[sz++] = val;
  }

  // Get the number of elements in the array
  size_t getSize() const { return sz; }

  // Get the array capacity
  size_t getCapacity() const { return cap; }

  // Access an element in the array
  T &operator[](size_t idx) {
    if (idx >= sz) {
      throw std::out_of_range("Index out of range");
    }
    return elems[idx];
  }

  // Access an element in the array (const version)
  const T &operator[](size_t idx) const {
    if (idx >= sz) {
      throw std::out_of_range("Index out of range");
    }
    return elems[idx];
  }

  // Insert an element at a specified position
  void insert(size_t idx, const T &val) {
    if (idx > sz) {
      throw std::out_of_range("Index out of range");
    }
    if (sz == cap) {
      reserve(cap == 0 ? 1 : cap * 2);
    }
    for (size_t i = sz; i > idx; --i) {
      elems[i] = elems[i - 1];
    }
    elems[idx] = val;
    ++sz;
  }

  bool remove(const T &val) {
    size_t idx = 0;
    for (; idx < sz; ++idx) {
      if (elems[idx] == val) {
        break;
      }
    }
    if (idx == sz) { // 如果没找到，直接返回
      return false;
    }
    // 如果找到了元素，而且它不是最后一个元素，就移动后面的元素
    if (idx < sz - 1) {
      std::move(elems + idx + 1, elems + sz, elems + idx);
    }
    // 显式调用析构函数
    elems[sz - 1].~T();
    // 更新size
    sz--;
    return true;
  }

  // Remove the last element from the array
  void pop_back() {
    if (sz > 0) {
      --sz;
    }
  }

  // Clear the array
  void clear() {
    for (size_t i = 0; i < sz; ++i) {
      elems[i].~T(); // Call the destructor for each element
    }
    sz = 0;
  }

  // Begin iterator
  T *begin() { return elems; }

  // End iterator
  T *end() { return elems + sz; }

  // Begin iterator (const version)
  const T *begin() const { return elems; }

  // End iterator (const version)
  const T *end() const { return elems + sz; }

  // Print elements in the array
  void print() const {
    std::cout << "Elements:";
    for (size_t i = 0; i < sz; ++i) {
      std::cout << " " << elems[i];
    }
    std::cout << std::endl;
  }

private:
  // Expand array capacity
  void reserve(size_t newCap) {
    if (newCap > cap) {
      T *newElems = new T[newCap];
      std::copy(elems, elems + sz, newElems);
      delete[] elems;
      elems = newElems;
      cap = newCap;
    }
  }
};
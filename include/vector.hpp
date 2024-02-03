#include <algorithm>
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

  // Destructor
  ~Vector() { delete[] elems; }

  // Copy constructor
  Vector(const Vector &other) : cap(other.cap), sz(other.sz) {
    elems = new T[cap];
    std::copy(other.elems, other.elems + sz, elems);
  }

  // Copy assignment operator
  Vector &operator=(const Vector &other) {
    if (this != &other) {
      delete[] elems;
      cap = other.cap;
      sz = other.sz;
      elems = new T[cap];
      std::copy(other.elems, other.elems + sz, elems);
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

  // Remove the last element from the array
  void pop_back() {
    if (sz > 0) {
      --sz;
    }
  }

  // Clear the array
  void clear() { sz = 0; }

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
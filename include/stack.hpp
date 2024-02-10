#include "deque.hpp"

template <typename T> class Stack {
private:
  Deque<T> deque;

public:
  void push(const T &val) { deque.push_back(val); }

  void pop() {
    if (isEmpty()) {
      throw std::out_of_range("Stack is empty");
    }
    deque.pop_back();
  }

  T &top() {
    if (isEmpty()) {
      throw std::out_of_range("Stack is empty");
    }
    return deque[deque.size() - 1];
  }

  bool isEmpty() const { return deque.size() == 0; }

  size_t size() const { return deque.size(); }
};
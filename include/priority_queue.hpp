#pragma once

#include "heap.hpp"

template <typename T, typename Compare = std::less<T>> class PriorityQueue {
private:
  Heap<T, Compare> heap;

public:
  PriorityQueue() : heap() {}

  // Add an element to the priority queue.
  void push(const T &value) { heap.insert(value); }

  // Remove the top element from the priority queue.
  void pop() {
    if (empty()) {
      throw std::out_of_range("PriorityQueue is empty, cannot pop");
    }
    heap.removeRoot();
  }

  // Get the top element of the priority queue.
  T top() const {
    if (empty()) {
      throw std::out_of_range("PriorityQueue is empty, cannot get top");
    }
    // Assuming that arr[1] is the top element since the Heap is a 1-indexed
    // array.
    return heap.getRoot();
  }

  // Check if the priority queue is empty.
  bool empty() const { return heap.size() == 0; }

  // Get the number of elements in the priority queue.
  size_t size() const { return heap.size(); }
};
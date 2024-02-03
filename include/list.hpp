#include "node.hpp"
#include <iostream>
#include <stdexcept>

// Templated doubly linked list class
template <typename T> class List {
private:
  Node<T> *head; // Pointer to the first node of the list
  Node<T> *tail; // Pointer to the last node of the list
  size_t sz;     // Number of nodes in the list

  // Helper function to retrieve the node at a specific index
  Node<T> *getNodeAt(size_t idx) const {
    Node<T> *curr = head;
    for (size_t i = 0; i < idx; ++i) {
      if (curr == nullptr)
        throw std::out_of_range("Index out of range");
      curr = curr->next;
    }
    return curr;
  }

public:
  // Constructor initializes an empty list
  List() : head(nullptr), tail(nullptr), sz(0) {}

  // Destructor deallocates all nodes
  ~List() { clear(); }

  // Adds a new element to the end of the list
  void push_back(const T &val) {
    Node<T> *newN = new Node<T>(val, nullptr, tail);
    if (tail != nullptr) {
      tail->next = newN;
    } else {
      head = newN;
    }
    tail = newN;
    ++sz;
  }

  // Adds a new element to the front of the list
  void push_front(const T &val) {
    Node<T> *newN = new Node<T>(val, head, nullptr);
    if (head != nullptr) {
      head->prev = newN;
    } else {
      tail = newN;
    }
    head = newN;
    ++sz;
  }

  // Returns the number of elements in the list
  size_t size() const { return sz; }

  // Overloads the subscript operator for accessing elements by index
  T &operator[](size_t idx) { return getNodeAt(idx)->data; }

  // Overloads the subscript operator for accessing elements by index (const
  // version)
  const T &operator[](size_t idx) const { return getNodeAt(idx)->data; }

  // Removes the last element from the list
  void pop_back() {
    if (tail != nullptr) {
      Node<T> *newT = tail->prev;
      delete tail;
      tail = newT;
      if (tail != nullptr) {
        tail->next = nullptr;
      } else {
        head = nullptr;
      }
      --sz;
    }
  }

  // Removes the first element from the list
  void pop_front() {
    if (head != nullptr) {
      Node<T> *newH = head->next;
      delete head;
      head = newH;
      if (head != nullptr) {
        head->prev = nullptr;
      } else {
        tail = nullptr;
      }
      --sz;
    }
  }

  // Removes all elements from the list and deallocates the nodes
  void clear() {
    Node<T> *curr;
    while ((curr = head) != nullptr) {
      head = head->next;
      delete curr;
    }
    tail = nullptr;
    sz = 0;
  }

  // Returns an iterator to the beginning of the list
  Node<T> *begin() { return head; }
  // Returns a const iterator to the beginning of the list
  const Node<T> *begin() const { return head; }
  // Returns an iterator to the end of the list (nullptr in this case)
  Node<T> *end() { return nullptr; }
  // Returns a const iterator to the end of the list (nullptr in this case)
  const Node<T> *end() const { return nullptr; }
};
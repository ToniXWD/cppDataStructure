#pragma once

#include "iterator.hpp"
#include "node.hpp"
#include <iostream>
#include <stdexcept>

template <typename T> class ListIterator;

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

  List(List &&other) : head(other.head), tail(other.tail), sz(other.sz) {
    other.head = nullptr;
    other.tail = nullptr;
    other.sz = 0;
  }

  List(const List<T> &other) : head(nullptr), tail(nullptr), sz(0) {
    Node<T> *current = other.head;
    while (current != nullptr) {
      this->push_back(current->val);
      current = current->next;
    }
  }

  // Destructor deallocates all nodes
  ~List() { clear(); }

  List &operator=(List &&other) noexcept {
    if (this != &other) { // 自赋值检查
      this->clear();      // 删除旧资源

      this->head = other.head;
      this->tail = other.tail;
      this->sz = other.sz;

      // 将other置为一个确保安全销毁的状态
      other.head = nullptr;
      other.tail = nullptr;
      other.sz = 0;
    }
    return *this; // 返回当前对象的引用
  }

  List<T> &operator=(const List<T> &other) {
    if (this != &other) {        // 自赋值检查
      List<T> tmp(other);        // 使用拷贝构造函数创建临时实例
      std::swap(head, tmp.head); // 交换头指针
      std::swap(tail, tmp.tail); // 交换尾指针
      std::swap(sz, tmp.sz);     // 交换大小
    }
    return *this;
  }

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
  T &operator[](size_t idx) { return getNodeAt(idx)->val; }

  // Overloads the subscript operator for accessing elements by index (const
  // version)
  const T &operator[](size_t idx) const { return getNodeAt(idx)->val; }

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

  Node<T> *getNode(const T &val) {
    Node<T> *node = head;
    while (node != nullptr && node->val != val) {
      node = node->next;
    }

    return node;
  }

  T *find(const T &val) {
    Node<T> *node = getNode(val);
    if (node == nullptr) {
      return nullptr;
    }
    return &node->val;
  }

  bool remove(const T &val) {
    Node<T> *node = head;
    while (node != nullptr && node->val != val) {
      node = node->next;
    }

    if (node == nullptr) {
      // 没有找到
      return false;
    }
    if (node != head && node != tail) {
      // 既不是头结点也不是尾结点
      node->prev->next = node->next;
      node->next->prev = node->prev;
    } else if (node == head && node == tail) {
      // 既是头结点也是尾结点
      head = nullptr;
      node = nullptr;
    } else if (node == head) {
      // 是头结点
      head = node->next;
      head->prev = nullptr;
    } else {
      // 是尾结点
      tail = node->prev;
      tail->next = nullptr;
    }

    delete node;
    node = nullptr;
    return true;
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
    head = nullptr;
    sz = 0;
  }

  // Returns an iterator to the beginning of the list
  ListIterator<T> begin() { return ListIterator<T>(head); }
  // Returns a const iterator to the beginning of the list
  const ListIterator<T> begin() const { return ListIterator<T>(head); }
  // Returns an iterator to the end of the list (nullptr in this case)
  ListIterator<T> end() { return ListIterator<T>(nullptr); }
  // Returns a const iterator to the end of the list (nullptr in this case)
  const ListIterator<T> end() const { return ListIterator<T>(nullptr); }
};

template <typename T> class ListIterator : public BaseIterator<T> {
public:
  ListIterator(Node<T> *node = nullptr) : node(node) {}

  ListIterator &operator++() {
    node = node->next;
    return *this;
  }

  T &operator*() { return node->val; }

  bool operator==(const ListIterator &other) const {
    return node == other.node;
  }

  bool operator!=(const ListIterator &other) const {
    return node != other.node;
  }

private:
  Node<T> *node;
};
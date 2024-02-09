#pragma once

#include "node.hpp"

template <typename T> class BaseIterator {
public:
  BaseIterator &operator++();
  T &operator*();
  T *operator->();
  bool operator==(const BaseIterator &other) const;
  bool operator!=(const BaseIterator &other) const;
};

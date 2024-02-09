#pragma once

#include "node.hpp"
#include "rbTree.hpp"
#include "vector.hpp"
#include <cstddef>
#include <fstream>
#include <stdexcept>

template <typename Key, typename Val> class MultiMap {
  rbTree<Key, Vector<Val>> tree;
  size_t sz;

public:
  // Constructors
  MultiMap() : sz(0), tree(){};

  // Capacity
  bool empty() const noexcept { return sz == 0; }
  size_t size() const noexcept { return sz; }

  // Modifiers
  void clear() noexcept {
    tree.clear();
    sz = 0;
  }
  void insert(const Key &key, const Val &val) {
    RBNode<Key, Vector<Val>> *keyVec = tree.getNode(key);
    if (keyVec != nullptr) {
      keyVec->val.push_back(val);
      sz++;
      return;
    }
    Vector<Val> newVec;
    newVec.push_back(val);
    tree.insertKV(key, newVec);
    sz++;
  }

  void erase(const Key &key) {
    RBNode<Key, Vector<Val>> *keyVec = tree.getNode(key);
    if (keyVec != nullptr) {
      sz -= keyVec->val.getSize();
      tree.remove(key);
    }
  }

  // Lookup
  size_t count(const Key &key) {
    RBNode<Key, Vector<Val>> *keyVec = tree.getNode(key);
    if (keyVec != nullptr) {
      return keyVec->val.getSize();
    }
    return 0;
  }

  Vector<Val> find(const Key &key) {
    RBNode<Key, Vector<Val>> *keyVec = tree.getNode(key);
    if (keyVec != nullptr) {
      return keyVec->val;
    }
    return Vector<Val>();
  }
};
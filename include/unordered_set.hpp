#pragma once

#include "hashTable.hpp"
#include "node.hpp"
#include "vector.hpp"
#include <cstddef>
#include <utility>

// template <typename Key, typename Val> class Unordered_map_Iterator;

template <typename Key, typename Val> class Unordered_set {
private:
  HashTable<Key, Val> hashtable;

public:
  Unordered_set() : hashtable(){};

  ~Unordered_set() {}

  bool empty() const noexcept { return hashtable.size() == 0; }

  size_t size() const noexcept { return hashtable.size(); }

  void clear() noexcept { hashtable.clear(); }

  void insert(const Key &key) { hashtable.insert(key); }

  void erase(const Key &key) { hashtable.erase(key); }

  Key *find(const Key &key) {
    KVNode<Key, Val> *ans = hashtable.find(key);
    if (ans != nullptr) {
      return &ans->key;
    }
    return nullptr;
  }
};
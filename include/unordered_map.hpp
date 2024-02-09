#pragma once

#include "hashTable.hpp"
#include "node.hpp"
#include "vector.hpp"
#include <cstddef>
#include <utility>

// template <typename Key, typename Val> class Unordered_map_Iterator;

template <typename Key, typename Val> class Unordered_map {
private:
  HashTable<Key, Val> hashtable;

public:
  Unordered_map() : hashtable(){};

  ~Unordered_map() {}

  bool empty() const noexcept { return hashtable.size() == 0; }

  size_t size() const noexcept { return hashtable.size(); }

  void clear() noexcept { hashtable.clear(); }

  void insert(const Key &key, const Val &value) {
    hashtable.insert(key, value);
  }

  void erase(const Key &key) { hashtable.erase(key); }

  std::pair<Key, Val> *find(const Key &key) {
    KVNode<Key, Val> *ans = hashtable.find(key);
    if (ans != nullptr) {
      return new std::pair<Key, Val>(ans->key, ans->val);
    }
    return nullptr;
  }

  Val &operator[](const Key &key) {
    KVNode<Key, Val> *ans = hashtable.find(key);
    if (ans != nullptr) {
      return ans->val;
    }
    hashtable.insert(key);
    ans = hashtable.find(key);
    return ans->val;
  }
};
#pragma once

#include "algorithm.hpp"
#include "list.hpp"
#include "node.hpp"
#include "vector.hpp"
#include <cstddef>
#include <iostream>

template <typename Key, typename Val> class Hash_Iterator;

template <typename Key, typename Val, typename Hash = std::hash<Key>>
class HashTable {
  using Bucket = List<KVNode<Key, Val>>;

private:
  Vector<Bucket> buckets;
  Hash hashFunction;
  size_t tableSize;
  size_t numElements;

  float maxLoadFactor = 0.75; // 默认的最大负载因子

  size_t hash(const Key &key) const { return hashFunction(key) % tableSize; }

  void rehash(size_t newSize) {
    Vector<Bucket> newBuckets;
    for (size_t i = 0; i < newSize; i++) {
      newBuckets.push_back(Bucket());
    }
    for (Bucket &bucket : this->buckets) {
      for (auto &kv : bucket) {
        size_t newIndex = hashFunction(kv.key) % newSize;
        newBuckets[newIndex].push_back(kv);
      }
    }
    this->buckets = newBuckets;
    this->tableSize = newSize;
  }

public:
  HashTable(size_t size = 128, const Hash &hashFunc = Hash())
      : buckets(size), hashFunction(hashFunc), tableSize(size), numElements(0) {
    for (size_t i = 0; i < size; i++) {
      buckets.push_back(Bucket());
    }
  }

  void insert(const Key &key, const Val &val) { insertKV(key, val); }
  void insert(const Key &key) { insertKV(key, Val{}); }

  void insertKV(const Key &key, const Val &val) {
    KVNode<Key, Val> insertKV(key, val);
    if ((numElements + 1) > maxLoadFactor * tableSize) {
      rehash(tableSize * 2);
    }
    size_t index = hash(key);
    auto &bucket = buckets[index];
    if (!bucket.find(insertKV)) {
      bucket.push_back(insertKV);
      ++numElements;
    }
  }

  void erase(const Key &key) {
    size_t index = hash(key);
    auto &bucket = buckets[index];
    for (auto &nodeKey : bucket) {
      if (nodeKey == key) {
        bucket.remove(nodeKey);
        numElements--;
        break;
      }
    }
  }

  KVNode<Key, Val> *find(const Key &key) const {
    size_t index = hash(key);
    const auto &bucket = buckets[index];
    auto ans = iterFind(bucket.begin(), bucket.end(), key);

    if (ans != bucket.end()) {
      return &(*ans);
    }

    return nullptr;
  }

  size_t size() const { return numElements; }

  void print() const {
    std::cout << "\nUnordered Set elements:" << std::endl;
    for (size_t i = 0; i < tableSize; ++i) {
      std::cout << "Bucket " << i << ": ";
      for (const auto &element : buckets[i]) {
        std::cout << element << " ";
      }
      std::cout << std::endl;
    }
  }

  void clear() {
    this->buckets.clear();
    numElements = 0;
  }

  Hash_Iterator<Key, Val> begin() {
    Node<KVNode<Key, Val>> *node = buckets[0].head;
    int bucket_idx = 0;
    while (node == nullptr) {
      bucket_idx++;
      if (bucket_idx == buckets.getSize()) {
        break;
      }
      node = buckets[bucket_idx].head;
    }
    return Hash_Iterator<Key, Val>(this->buckets, node);
  }

  Hash_Iterator<Key, Val> end() {
    return Hash_Iterator<Key, Val>(this->buckets, tableSize, nullptr);
  }
};

template <typename Key, typename Val>
class Hash_Iterator : public BaseIterator<std::pair<Key, Val>> {
  using Bucket = List<KVNode<Key, Val>>;

public:
  Hash_Iterator(Vector<Bucket> &hashMapBuckects,
                Node<KVNode<Key, Val>> *node = nullptr)
      : node(node), bucket_idx(0), buckets(hashMapBuckects) {}

  Hash_Iterator(Vector<Bucket> &hashMapBuckects, size_t bucket_idx_,
                Node<KVNode<Key, Val>> *node = nullptr)
      : node(node), buckets(hashMapBuckects), bucket_idx(bucket_idx_) {}

  Hash_Iterator &operator++() {
    node = node->next;
    while (node == nullptr) {
      bucket_idx++;
      if (bucket_idx == buckets.getSize()) {
        return *this;
      }
      node = buckets[bucket_idx].head;
    }

    return *this;
  }

  std::pair<Key, Val> &operator*() {
    kv.first = node->val.key;
    kv.second = node->val.val;
    return kv;
  }

  std::pair<Key, Val> *operator->() {
    kv.first = node->val.key;
    kv.second = node->val.val;
    return &kv;
  }

  bool operator==(const Hash_Iterator &other) const {
    return &buckets == &other.buckets && bucket_idx == other.bucket_idx &&
           node == other.node;
  }

  bool operator!=(const Hash_Iterator &other) const {
    return !(&buckets == &other.buckets && bucket_idx == other.bucket_idx &&
             node == other.node);
  }

private:
  Vector<Bucket> &buckets;
  size_t bucket_idx;
  Node<KVNode<Key, Val>> *node;
  std::pair<Key, Val> kv;
};
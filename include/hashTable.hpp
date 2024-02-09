#include "algorithm.hpp"
#include "list.hpp"
#include "node.hpp"
#include "vector.hpp"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>

template <typename Key, typename Val, typename Hash = std::hash<Key>>
class HashTable {
private:
  using Bucket = List<KVNode<Key, Val>>;
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
  HashTable(size_t size = 10, const Hash &hashFunc = Hash())
      : buckets(size), hashFunction(hashFunc), tableSize(size), numElements(0) {
    for (size_t i = 0; i < size; i++) {
      buckets.push_back(Bucket());
    }
  }

  void insert(const Key &key) {
    KVNode<Key, Val> insertKV(key);
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

  bool find(const Key &key) const {
    size_t index = hash(key);
    const auto &bucket = buckets[index];
    return iterFind(bucket.begin(), bucket.end(), key) != bucket.end();
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
};
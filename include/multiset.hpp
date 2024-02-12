#pragma once

#include "node.hpp"
#include "rbTree.hpp"
#include <cstddef>
#include <stdexcept>

template <typename Key> class MultiSet {
  rbTree<Key, size_t> rbTree;
  size_t sz;

public:
  MultiSet() : sz(0) {} // 构造函数
  ~MultiSet() {}        // 析构函数

  // 插入元素
  void insert(const Key &key) {
    auto ans = rbTree.getNode(key);
    if (ans != nullptr) {
      ans->val++;
    }
    rbTree.insertKV(key, 1);
    sz++;
  }

  // 删除键为key的元素
  void erase(const Key &key) {
    auto ans = rbTree.getNode(key);
    if (ans != nullptr) {
      sz -= ans->val;
      rbTree.remove(key);
    }
  }

  // 返回容器中元素的数量
  size_t size() const { return sz; }

  // 判断容器是否为空
  bool empty() const { return sz == 0; }

  // 返回在 multiset 中等于给定值的元素的数量
  size_t count(const Key &key) {
    auto ans = rbTree.getNode(key);
    if (ans != nullptr) {
      return ans->val;
    }

    return 0;
  }

  void clear() {
    sz = 0;
    rbTree.clear();
  }
};
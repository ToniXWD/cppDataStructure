#pragma once

#include "node.hpp"
#include "rbTree.hpp"
#include <stdexcept>

template <typename Key, typename Val> class Map {
  rbTree<Key, Val> rbTree;

public:
  Map() {}  // 构造函数
  ~Map() {} // 析构函数

  // 插入元素
  void insert(const Key &key, const Val &val) {
    auto ans = rbTree.getNode(key);
    if (ans != nullptr) {
      return;
    }
    rbTree.insertKV(key, val);
  }

  // 删除键为key的元素
  void erase(const Key &key) { rbTree.remove(key); }

  // 访问键为key的元素的值
  Val &at(const Key &key) {
    auto ans = rbTree.getNode(key);
    if (ans == nullptr) {
      throw std::out_of_range("key not exist!");
    }
    return ans->val;
  }

  // 访问键为key的元素的值（const版本）
  const Val &at(const Key &key) const {
    auto ans = rbTree.getNode(key);
    if (ans == nullptr) {
      throw std::out_of_range("key not exist!");
    }
    return ans->val;
  }

  // 返回容器中元素的数量
  size_t size() const { return rbTree.size; }

  // 判断容器是否为空
  bool empty() const { return rbTree.empty(); }

  // 通过键访问值
  Val &operator[](const Key &key) {
    auto ans = rbTree.getNode(key);
    if (ans != nullptr) {
      return ans->val;
    }
    rbTree.insert(key);
    ans = rbTree.getNode(key);
    return ans->val;
  }
};
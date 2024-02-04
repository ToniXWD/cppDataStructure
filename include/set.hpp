#pragma once

#include "node.hpp"
#include "rbTree.hpp"
#include <stdexcept>

template <typename Key> class Set {
  rbTree<Key, Key> rbTree;

public:
  Set() {}  // 构造函数
  ~Set(){}; // 析构函数

  // 插入元素
  void insert(const Key &key) {
    auto ans = rbTree.getNode(key);
    if (ans != nullptr) {
      return;
    }
    rbTree.insert(key);
  }

  // 删除指定元素
  void erase(const Key &key) { rbTree.remove(key); }

  // 计算某个键的元素数量（0或1，因为set不允许重复）
  size_t count(const Key &key) {
    auto ans = rbTree.getNode(key);
    if (ans != nullptr) {
      return 1;
    }
    return 0;
  }
  // 返回容器中元素的数量
  size_t size() const { return rbTree.size; }

  // 判断容器是否为空
  bool empty() const { return rbTree.empty(); }

  // 迭代器相关的接口
  //   iterator begin(); // 返回指向第一个元素的迭代器
  //   iterator end();   // 返回指向容器结尾的迭代器
  //   const_iterator begin() const;
  //   const_iterator end() const;
};
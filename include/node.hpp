#pragma once

#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T> class Node {
public:
  T val;
  Node *next;
  Node *prev;
  Node(const T &value, Node *nextNode = nullptr, Node *prevNode = nullptr)
      : val(value), next(nextNode), prev(prevNode) {}
  T &operator*() { return val; }
  bool &operator<(const Node<T> &other) { return val < other.val; }
};

template <typename Key, typename Val> class KVNode {
public:
  Key key;
  Val val;

  // 从Key构造节点，Value使用默认构造
  explicit KVNode(const Key &key) : key(key), val() {}

  // 从Key和Value构造节点
  KVNode(const Key &key, const Val &value) : key(key), val(value) {}

  // 比较算符重载，只按照key进行比较
  bool operator==(const KVNode &other) const { return key == other.key; }

  bool operator!=(const KVNode &other) const { return key != other.key; }

  bool operator<(const KVNode &other) const { return key < other.key; }

  bool operator>(const KVNode &other) const { return key > other.key; }

  bool operator==(const Key &key_) const { return key == key_; }

  void print() const { std::cout << "key: " << key << " value: " << val<<" "; }
};

template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const KVNode<Key, Val> &kvNode) {
  os << "key: " << kvNode.key << " value: " << kvNode.val << " ";
  return os;
}

enum class Color { RED, BLACK };

template <typename Key, typename Val> class RBNode {
public:
  Key key;
  Val val;
  Color color;
  RBNode<Key, Val> *left;
  RBNode<Key, Val> *right;
  RBNode<Key, Val> *parent;

  // 构造函数
  RBNode(const Key &k, Color c, RBNode<Key, Val> *p = nullptr)
      : key(k), color(c), left(nullptr), right(nullptr), parent(p) {}
  RBNode(const Key &k, const Val &v, Color c, RBNode<Key, Val> *p = nullptr)
      : key(k), val(v), color(c), left(nullptr), right(nullptr), parent(p) {}
  RBNode()
      : color(Color::BLACK), left(nullptr), right(nullptr), parent(nullptr) {}

  int getLen() {
    // 获取某个子树的节点数量
    if (left == nullptr && right == nullptr) {
      return 1;
    }
    int l_len = 0;
    int r_len = 0;
    if (left != nullptr) {
      l_len = left->getLen();
    }
    if (right != nullptr) {
      r_len = right->getLen();
    }
    return 1 + l_len + r_len;
  }

  int getBlackHeight() {
    // 返回挡墙节点的黑色节点高度, 如果高度不合法, 返回-1
    if (left == nullptr && right == nullptr) {
      return color == Color::BLACK ? 1 : 0;
    }
    int hei_l = 0;
    int hei_r = 0;
    if (left != nullptr) {
      hei_l = left->getBlackHeight();
    }
    if (right != nullptr) {
      hei_r = right->getBlackHeight();
    }

    if (hei_l == -1 || hei_r == -1 || hei_l != hei_r) {
      return -1;
    }

    return color == Color::BLACK ? 1 + hei_l : hei_l;
  }

  bool isNoDoubleRed() {
    bool left_legal = true;
    bool right_legal = true;
    if (left != nullptr) {
      left_legal = left->isNoDoubleRed();
    }
    if (right != nullptr) {
      right_legal = right->isNoDoubleRed();
    }
    if (left_legal == false || right_legal == false) {
      return false;
    }
    if (color == Color::BLACK) {
      return true;
    }
    if (left != nullptr && left->color == Color::RED) {
      return false;
    }
    if (right != nullptr && right->color == Color::RED) {
      return false;
    }
    if (parent != nullptr && parent->color == Color::RED) {
      return false;
    }
    return true;
  }
};

template <typename Key, typename Val>
void printTreeHelper(RBNode<Key, Val> *root, std::string indent = "",
                     bool last = true) {
  // 当前节点为null，直接返回
  if (root == nullptr) {
    return;
  }

  // 打印缩进
  std::cout << indent;
  if (last) {
    std::cout << "R----";
    // 更新缩进标记为垂直线
    indent += "   ";
  } else {
    std::cout << "L----";
    // 更新缩进标记
    indent += "|  ";
  }

  // 打印当前节点的颜色和键值
  std::string color = root->color == Color::RED ? "RED" : "BLACK";
  std::cout << root->key << "(" << color << ")" << std::endl;

  // 递归打印左子树
  printTreeHelper(root->left, indent, false);
  // 递归打印右子树
  printTreeHelper(root->right, indent, true);
}

template <typename Key, typename Val> void printTree(RBNode<Key, Val> *root) {
  if (root == nullptr) {
    std::cout << "<empty tree>" << std::endl;
    return;
  }
  // 调用递归辅助函数
  printTreeHelper(root);
}
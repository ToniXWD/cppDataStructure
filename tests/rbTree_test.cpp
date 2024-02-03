#include "../include/rbTree.hpp"
#include <algorithm>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

// Demonstrate some basic assertions.
TEST(RbTreeTest, InsertTEST) {
  // 创建 RedBlackTree 对象
  RedBlackTree<int, int> tree;

  EXPECT_TRUE(tree.empty());

  // 插入元素
  tree.insert(42);
  tree.insert(21);
  tree.insert(63);
  tree.insert(10);
  tree.insert(4);
  tree.insert(30);
  tree.insert(36);
  tree.insert(92);
  tree.insert(75);
  tree.insert(87);
  tree.insert(58);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 11);

  tree.insert(58);
  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 11);
}

TEST(RbTreeTest, RemoveTest1) {
  // 创建 RedBlackTree 对象
  RedBlackTree<int, int> tree;

  EXPECT_TRUE(tree.empty());

  // 插入元素
  tree.insert(42);
  tree.insert(21);
  tree.insert(63);
  tree.insert(10);
  tree.insert(4);
  tree.insert(30);
  tree.insert(36);
  tree.insert(92);
  tree.insert(75);
  tree.insert(87);
  tree.insert(58);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 11);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(30);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 10);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(63);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 9);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(63);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 9);
  EXPECT_TRUE(tree.isRootBlack());

  // 删除根节点
  tree.remove(42);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 8);
  EXPECT_TRUE(tree.isRootBlack());

  // 删除根节点
  tree.remove(58);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 7);
  EXPECT_TRUE(tree.isRootBlack());
}

TEST(RbTreeTest, RemoveTest2) {
  // 创建 RedBlackTree 对象
  RedBlackTree<int, int> tree;

  EXPECT_TRUE(tree.empty());

  // 插入元素
  tree.insert(5);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 1);
  EXPECT_TRUE(tree.isRootBlack());

  tree.insert(3);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 2);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(5);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 1);
  EXPECT_TRUE(tree.isRootBlack());
}

TEST(RbTreeTest, RemoveRoot) {
  // 创建 RedBlackTree 对象
  RedBlackTree<int, int> tree;

  EXPECT_TRUE(tree.empty());

  // 插入元素
  tree.insert(5);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 1);
  EXPECT_TRUE(tree.isRootBlack());

  // 插入元素
  tree.insert(10);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 2);
  EXPECT_TRUE(tree.isRootBlack());

  // 删除根节点
  tree.remove(5);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 1);
  EXPECT_TRUE(tree.isRootBlack());

  // 删除根节点
  tree.remove(10);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 0);
  EXPECT_TRUE(tree.isRootBlack());
  EXPECT_TRUE(tree.empty());
}

TEST(RbTreeTest, DoubleBlackTest) {
  // 创建 RedBlackTree 对象
  RedBlackTree<int, int> tree;

  EXPECT_TRUE(tree.empty());

  // 插入元素
  tree.insert(10);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 1);
  EXPECT_TRUE(tree.isRootBlack());

  tree.insert(5);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 2);
  EXPECT_TRUE(tree.isRootBlack());

  tree.insert(50);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 3);
  EXPECT_TRUE(tree.isRootBlack());

  tree.insert(30);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 4);
  EXPECT_TRUE(tree.isRootBlack());

  tree.insert(36);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 5);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(5);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 4);
  EXPECT_TRUE(tree.isRootBlack());
}

TEST(RbTreeTest, RemoveWithSiblingHasTwoBlackChildren) {
  // 手动构造一个红黑树
  // 根节点
  RBNode<int, int> *root6 = new RBNode<int, int>(6, Color::BLACK, nullptr);

  // 第二层
  RBNode<int, int> *n_4_left_of_root_b =
      new RBNode<int, int>(4, Color::BLACK, root6);
  RBNode<int, int> *n_20_right_of_root_r =
      new RBNode<int, int>(20, Color::RED, root6);
  root6->left = n_4_left_of_root_b;
  root6->right = n_20_right_of_root_r;

  // 第三层
  RBNode<int, int> *n_3_left_of_4_b =
      new RBNode<int, int>(3, Color::BLACK, n_4_left_of_root_b);
  RBNode<int, int> *n_5_right_of_4_b =
      new RBNode<int, int>(5, Color::BLACK, n_4_left_of_root_b);
  n_4_left_of_root_b->left = n_3_left_of_4_b;
  n_4_left_of_root_b->right = n_5_right_of_4_b;

  RBNode<int, int> *n_13_left_of_20_b =
      new RBNode<int, int>(13, Color::BLACK, n_20_right_of_root_r);
  RBNode<int, int> *n_23_right_of_20_b =
      new RBNode<int, int>(23, Color::BLACK, n_20_right_of_root_r);
  n_20_right_of_root_r->left = n_13_left_of_20_b;
  n_20_right_of_root_r->right = n_23_right_of_20_b;

  // 第四层
  RBNode<int, int> *n_10_left_of_13_b =
      new RBNode<int, int>(10, Color::BLACK, n_13_left_of_20_b);
  RBNode<int, int> *n_15_right_of_13_b =
      new RBNode<int, int>(15, Color::BLACK, n_13_left_of_20_b);
  n_13_left_of_20_b->left = n_10_left_of_13_b;
  n_13_left_of_20_b->right = n_15_right_of_13_b;

  RBNode<int, int> *n_21_left_of_23_b =
      new RBNode<int, int>(21, Color::BLACK, n_23_right_of_20_b);
  RBNode<int, int> *n_28_right_of_23_b =
      new RBNode<int, int>(28, Color::BLACK, n_23_right_of_20_b);
  n_23_right_of_20_b->left = n_21_left_of_23_b;
  n_23_right_of_20_b->right = n_28_right_of_23_b;

  // 创建 RedBlackTree 对象
  RedBlackTree<int, int> tree(root6, 11);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 11);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(13);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 10);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(28);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 9);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(5);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 8);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(5);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 8);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(4);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 7);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(10);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 6);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(23);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 5);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(6);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 4);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(21);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 3);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(3);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 2);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(15);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 1);
  EXPECT_TRUE(tree.isRootBlack());

  tree.remove(20);

  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 0);
  EXPECT_TRUE(tree.isRootBlack());
  EXPECT_TRUE(tree.empty());

  tree.insert(27);
  EXPECT_TRUE(tree.len() == tree.getSizeByTranverse());
  EXPECT_TRUE(tree.isBlackLenLegal());
  EXPECT_TRUE(tree.isNoDoubleRed());
  EXPECT_EQ(tree.len(), 1);
  EXPECT_TRUE(tree.isRootBlack());
  EXPECT_FALSE(tree.empty());
}

TEST(RbTreeTest, RandomOperation) {
  // 创建 RedBlackTree 对象
  RedBlackTree<int, int> tree;

  // 初始化随机数引擎，使用随机设备来获取种子
  std::random_device rd;

  std::mt19937 gen(rd()); // 使用 Mersenne Twister 生成器

  // 定义随机数分布，这里以生成[0, 99]范围内的随机整数为例
  std::uniform_int_distribution<> dis(0, 2000000);

  std::unordered_set<int> collect;

  // 先插入一部分元素
  for (int i = 0; i < 1000; i++) {
    int random_number = dis(gen);
    tree.insert(random_number);
    collect.insert(random_number);
  }

  int first_resize = collect.size() / 2;

  // 再删除一半的元素
  while (collect.size() > first_resize) {
    int del_target = *(collect.begin());
    collect.erase(collect.begin());

    tree.remove(del_target);
    ASSERT_TRUE(tree.len() == tree.getSizeByTranverse());
    ASSERT_TRUE(tree.isBlackLenLegal());
    ASSERT_TRUE(tree.isNoDoubleRed());
    EXPECT_EQ(tree.len(), collect.size());
    ASSERT_TRUE(tree.isRootBlack());
  }

  // 再插入一部分元素
  for (int i = 0; i < 1000; i++) {
    int random_number = dis(gen);
    tree.insert(random_number);
    collect.insert(random_number);
  }

  // 再删除所有元素
  while (!collect.empty()) {
    int del_target = *(collect.begin());
    collect.erase(collect.begin());

    tree.remove(del_target);
    ASSERT_TRUE(tree.len() == tree.getSizeByTranverse());
    ASSERT_TRUE(tree.isBlackLenLegal());
    ASSERT_TRUE(tree.isNoDoubleRed());
    EXPECT_EQ(tree.len(), collect.size());
    ASSERT_TRUE(tree.isRootBlack());
  }
}
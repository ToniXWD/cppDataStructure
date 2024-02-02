#include "../include/rbTree.hpp"
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(RbTreeTest, InsertTEST) {
  // 创建 RedBlackTree 对象
  RedBlackTree<int> mySet;

  EXPECT_TRUE(mySet.empty());

  // 插入元素
  mySet.insert(42);
  mySet.insert(21);
  mySet.insert(63);
  mySet.insert(10);
  mySet.insert(4);
  mySet.insert(30);
  mySet.insert(36);
  mySet.insert(92);
  mySet.insert(75);
  mySet.insert(87);
  mySet.insert(58);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 11);

  mySet.insert(58);
  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 11);
}

TEST(RbTreeTest, RemoveTest1) {
  // 创建 RedBlackTree 对象
  RedBlackTree<int> mySet;

  EXPECT_TRUE(mySet.empty());

  // 插入元素
  mySet.insert(42);
  mySet.insert(21);
  mySet.insert(63);
  mySet.insert(10);
  mySet.insert(4);
  mySet.insert(30);
  mySet.insert(36);
  mySet.insert(92);
  mySet.insert(75);
  mySet.insert(87);
  mySet.insert(58);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 11);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(30);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 10);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(63);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 9);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(63);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 9);
  EXPECT_TRUE(mySet.isRootBlack());

  // 删除根节点
  mySet.remove(42);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 8);
  EXPECT_TRUE(mySet.isRootBlack());

  // 删除根节点
  mySet.remove(58);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 7);
  EXPECT_TRUE(mySet.isRootBlack());
}

TEST(RbTreeTest, RemoveTest2) {
  // 创建 RedBlackTree 对象
  RedBlackTree<int> mySet;

  EXPECT_TRUE(mySet.empty());

  // 插入元素
  mySet.insert(5);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 1);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.insert(3);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 2);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(5);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 1);
  EXPECT_TRUE(mySet.isRootBlack());
}

TEST(RbTreeTest, RemoveRoot) {
  // 创建 RedBlackTree 对象
  RedBlackTree<int> mySet;

  EXPECT_TRUE(mySet.empty());

  // 插入元素
  mySet.insert(5);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 1);
  EXPECT_TRUE(mySet.isRootBlack());

  // 插入元素
  mySet.insert(10);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 2);
  EXPECT_TRUE(mySet.isRootBlack());

  // 删除根节点
  mySet.remove(5);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 1);
  EXPECT_TRUE(mySet.isRootBlack());

  // 删除根节点
  mySet.remove(10);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 0);
  EXPECT_TRUE(mySet.isRootBlack());
  EXPECT_TRUE(mySet.empty());
}

TEST(RbTreeTest, DoubleBlackTest) {
  // 创建 RedBlackTree 对象
  RedBlackTree<int> mySet;

  EXPECT_TRUE(mySet.empty());

  // 插入元素
  mySet.insert(10);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 1);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.insert(5);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 2);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.insert(50);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 3);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.insert(30);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 4);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.insert(36);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 5);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(5);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 4);
  EXPECT_TRUE(mySet.isRootBlack());
}

TEST(RbTreeTest, RemoveWithSiblingHasTwoBlackChildren) {
  // 手动构造一个红黑树
  // 根节点
  Node<int> *root6 = new Node<int>(6, Color::BLACK, nullptr);

  // 第二层
  Node<int> *n_4_left_of_root_b = new Node<int>(4, Color::BLACK, root6);
  Node<int> *n_20_right_of_root_r = new Node<int>(20, Color::RED, root6);
  root6->left = n_4_left_of_root_b;
  root6->right = n_20_right_of_root_r;

  // 第三层
  Node<int> *n_3_left_of_4_b =
      new Node<int>(3, Color::BLACK, n_4_left_of_root_b);
  Node<int> *n_5_right_of_4_b =
      new Node<int>(5, Color::BLACK, n_4_left_of_root_b);
  n_4_left_of_root_b->left = n_3_left_of_4_b;
  n_4_left_of_root_b->right = n_5_right_of_4_b;

  Node<int> *n_13_left_of_20_b =
      new Node<int>(13, Color::BLACK, n_20_right_of_root_r);
  Node<int> *n_23_right_of_20_b =
      new Node<int>(23, Color::BLACK, n_20_right_of_root_r);
  n_20_right_of_root_r->left = n_13_left_of_20_b;
  n_20_right_of_root_r->right = n_23_right_of_20_b;

  // 第四层
  Node<int> *n_10_left_of_13_b =
      new Node<int>(10, Color::BLACK, n_13_left_of_20_b);
  Node<int> *n_15_right_of_13_b =
      new Node<int>(15, Color::BLACK, n_13_left_of_20_b);
  n_13_left_of_20_b->left = n_10_left_of_13_b;
  n_13_left_of_20_b->right = n_15_right_of_13_b;

  Node<int> *n_21_left_of_23_b =
      new Node<int>(21, Color::BLACK, n_23_right_of_20_b);
  Node<int> *n_28_right_of_23_b =
      new Node<int>(28, Color::BLACK, n_23_right_of_20_b);
  n_23_right_of_20_b->left = n_21_left_of_23_b;
  n_23_right_of_20_b->right = n_28_right_of_23_b;

  // 创建 RedBlackTree 对象
  RedBlackTree<int> mySet(root6, 11);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 11);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(13);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 10);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(28);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 9);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(5);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 8);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(5);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 8);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(4);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 7);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(10);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 6);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(23);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 5);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(6);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 4);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(21);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 3);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(3);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 2);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(15);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 1);
  EXPECT_TRUE(mySet.isRootBlack());

  mySet.remove(20);

  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 0);
  EXPECT_TRUE(mySet.isRootBlack());
  EXPECT_TRUE(mySet.empty());

  mySet.insert(27);
  EXPECT_TRUE(mySet.len() == mySet.getSizeByTranverse());
  EXPECT_TRUE(mySet.isBlackLenLegal());
  EXPECT_EQ(mySet.len(), 1);
  EXPECT_TRUE(mySet.isRootBlack());
  EXPECT_FALSE(mySet.empty());
}
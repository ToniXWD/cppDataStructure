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
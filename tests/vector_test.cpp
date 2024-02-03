#include "../include/vector.hpp" // 更新为你的vector实现的实际路径
#include <gtest/gtest.h>

// 测试vector的构造函数
TEST(VectorTest, Construct) {
  Vector<int> v;
  EXPECT_EQ(v.getSize(), 0); // 新建的vector应该是空的
}

// 测试添加元素到vector
TEST(VectorTest, PushBack) {
  Vector<int> v;
  v.push_back(1);
  EXPECT_EQ(v.getSize(), 1); // 添加一个元素后，大小应该是1
  EXPECT_EQ(v[0], 1);     // 这个元素的值应该是1
}

// 测试从vector删除元素
TEST(VectorTest, PopBack) {
  Vector<int> v;
  v.push_back(1);
  v.pop_back();
  EXPECT_EQ(v.getSize(), 0); // 删除后，vector应该是空的
}

// 测试访问vector中的元素
TEST(VectorTest, AccessElements) {
  Vector<int> v;
  v.push_back(1);
  v.push_back(2);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
}

// 测试vector的容量变化
TEST(VectorTest, Capacity) {
  Vector<int> v;
  EXPECT_TRUE(v.getCapacity() >= 0); // 初始容量应该大于等于0
  size_t old_capacity = v.getCapacity();
  for (int i = 0; i < 100; ++i) {
    v.push_back(i);
  }
  EXPECT_TRUE(v.getCapacity() > old_capacity); // 添加元素后，容量应该增加
  EXPECT_EQ(v.getSize(), 100);                 // 现在的大小应该是100
}

// 测试vector的复制构造函数
TEST(VectorTest, CopyConstructor) {
  Vector<int> v1;
  v1.push_back(1);
  v1.push_back(2);

  // 使用复制构造函数创建一个新的vector
  Vector<int> v2(v1);
  EXPECT_EQ(v2.getSize(), v1.getSize());
  for (size_t i = 0; i < v1.getSize(); ++i) {
    EXPECT_EQ(v2[i], v1[i]); // v2应该是v1的一个副本
  }
}

// 测试vector的赋值运算符
TEST(VectorTest, AssignmentOperator) {
  Vector<int> v1;
  v1.push_back(1);
  v1.push_back(2);

  // 使用赋值运算符
  Vector<int> v2;
  v2 = v1;
  EXPECT_EQ(v2.getSize(), v1.getSize());
  for (size_t i = 0; i < v1.getSize(); ++i) {
    EXPECT_EQ(v2[i], v1[i]); // v2应该是v1的一个副本
  }
}
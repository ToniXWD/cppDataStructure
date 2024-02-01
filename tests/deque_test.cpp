#include "../include/deque.hpp"
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(DequeTest, Basic1) {
// 创建一个 Deque 对象
Deque<int> myDeque;

// 在前端和后端插入元素
myDeque.push_front(1);
myDeque.push_back(2);
myDeque.push_front(0);
myDeque.push_back(3);
myDeque.push_back(4);
myDeque.push_back(5);
myDeque.push_back(6);
myDeque.push_front(-1);

EXPECT_EQ(myDeque[0], -1);
EXPECT_EQ(myDeque[1], 0);
EXPECT_EQ(myDeque[2], 1);
EXPECT_EQ(myDeque[3], 2);
EXPECT_EQ(myDeque[4], 3);
EXPECT_EQ(myDeque[5], 4);
EXPECT_EQ(myDeque[6], 5);
EXPECT_EQ(myDeque[7], 6);
EXPECT_EQ(myDeque.getSize(), 8);

myDeque.pop_front();
EXPECT_EQ(myDeque.getSize(), 7);
EXPECT_EQ(myDeque[0], 0);
EXPECT_EQ(myDeque[6], 6);

myDeque.pop_back();
EXPECT_EQ(myDeque.getSize(), 6);
EXPECT_EQ(myDeque[0], 0);
EXPECT_EQ(myDeque[5], 5);
}
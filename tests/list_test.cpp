#include "../include/list.hpp"
#include <gtest/gtest.h>
#include <iostream>

// Demonstrate some basic assertions.
TEST(ListTest, Basic1) {
    // 创建一个 List 对象
    List<int> myList;

    // 在链表末尾添加元素
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);

    EXPECT_EQ(myList[0], 1);
    EXPECT_EQ(myList[1], 2);
    EXPECT_EQ(myList[2], 3);
}
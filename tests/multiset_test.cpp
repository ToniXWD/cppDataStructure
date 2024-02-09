#include "../include/multiset.hpp"
#include <cstdlib>
#include <ctime>
#include <gtest/gtest.h>
#include <set>

// 测试 MultiSet 的插入功能
TEST(MultiSetTest, Insertion) {
  MultiSet<int> myMultiSet;
  std::multiset<int> stdMultiSet;

  srand((unsigned)time(NULL));
  for (int i = 0; i < 100; ++i) {
    int value = rand() % 100; // 随机生成 0 到 99 之间的数
    myMultiSet.insert(value);
    stdMultiSet.insert(value);
  }

  // 检查自定义 MultiSet 与 std::multiset 的大小是否一致
  ASSERT_EQ(myMultiSet.size(), stdMultiSet.size());

  // 检查自定义 MultiSet 中的每个元素出现次数是否与 std::multiset 中的一致
  for (const auto &val : stdMultiSet) {
    EXPECT_EQ(myMultiSet.count(val), stdMultiSet.count(val));
  }
}

// 测试 MultiSet 的删除功能
TEST(MultiSetTest, Deletion) {
  MultiSet<int> myMultiSet;
  std::multiset<int> stdMultiSet;

  srand((unsigned)time(NULL));
  for (int i = 0; i < 100; ++i) {
    int value = rand() % 100;
    myMultiSet.insert(value);
    stdMultiSet.insert(value);
  }

  for (int i = 0; i < 50; ++i) {
    int value = rand() % 100;
    myMultiSet.erase(value);
    stdMultiSet.erase(value);
  }

  // 再次检查大小
  ASSERT_EQ(myMultiSet.size(), stdMultiSet.size());

  // 再次检查元素计数
  for (const auto &val : stdMultiSet) {
    EXPECT_EQ(myMultiSet.count(val), stdMultiSet.count(val));
  }
}

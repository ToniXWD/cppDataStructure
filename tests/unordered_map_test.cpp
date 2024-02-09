#include "../include/unordered_map.hpp"
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <unordered_map>

// 测试构造函数
TEST(UnorderedMapTest, Constructor) {
  Unordered_map<int, int> map;
  EXPECT_TRUE(map.empty());
}

// 测试 empty 方法
TEST(UnorderedMapTest, Empty) {
  Unordered_map<int, int> map;
  EXPECT_TRUE(map.empty());
  map.insert(1, 100);
  EXPECT_FALSE(map.empty());
}

// 测试 size 方法
TEST(UnorderedMapTest, Size) {
  Unordered_map<int, int> map;
  EXPECT_EQ(0, map.size());
  map.insert(1, 100);
  EXPECT_EQ(1, map.size());
}

// 测试 clear 方法
TEST(UnorderedMapTest, Clear) {
  Unordered_map<int, int> map;
  map.insert(1, 100);
  map.clear();
  EXPECT_TRUE(map.empty());
}

// 测试 insert 方法
TEST(UnorderedMapTest, Insert) {
  Unordered_map<int, int> map;
  map.insert(1, 100);
  EXPECT_EQ(100, map[1]);
}

// 测试 erase 方法
TEST(UnorderedMapTest, Erase) {
  Unordered_map<int, int> map;
  map.insert(1, 100);
  map.erase(1);
  EXPECT_FALSE(map.find(1));
}

// 测试 find 方法
TEST(UnorderedMapTest, Find) {
  Unordered_map<int, int> map;
  map.insert(1, 100);
  EXPECT_TRUE(map.find(1) != nullptr);
  EXPECT_EQ(map.find(1)->second, 100);
  EXPECT_FALSE(map.find(2) != nullptr);
}

// 测试 operator[] 方法
TEST(UnorderedMapTest, SubscriptOperator) {
  Unordered_map<int, int> map;
  map[1] = 100;
  EXPECT_EQ(100, map[1]);
  map[1] = 200;
  EXPECT_EQ(200, map[1]);
  EXPECT_EQ(0, map[2]); // 默认构造值
}

TEST(UnorderedMapTest, RandomOperation) {
  std::mt19937 rng; // 默认随机数生成器
  //   rng.seed(std::random_device()()); // 使用随机设备来提供种子
  rng.seed(1); // 自定义随机种子

  std::uniform_int_distribution<int> dist(1, 100); // 定义一个分布范围

  Unordered_map<int, int> testMap;
  std::unordered_map<int, int> referenceMap;

  // 随机插入和删除操作的次数
  const int operations = 50;

  for (int i = 0; i < operations; ++i) {
    int key = dist(rng);   // 生成一个随机键
    int value = dist(rng); // 生成一个随机值

    // 随机决定是插入还是删除
    if (dist(rng) % 2 == 0) {
      // 插入操作
      testMap[key] = value;
      referenceMap[key] = value;
    } else {
      // 删除操作
      testMap.erase(key);
      referenceMap.erase(key);
    }
  }

  // 验证 UnorderedMap 和 std::unordered_map 的状态是否一致
  for (const auto &kvp : referenceMap) {
    // 这里假设 UnorderedMap 有一个 find 方法
    auto it = testMap.find(kvp.first);
    EXPECT_EQ(it->first, kvp.first);
    EXPECT_EQ(it->second, kvp.second);
  }
}
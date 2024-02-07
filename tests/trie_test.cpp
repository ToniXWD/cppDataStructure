#include "../include/trie.hpp" // Trie类的头文件
#include <gtest/gtest.h>

// 测试GetValue方法
TEST(TrieTest, GetValue) {
  Trie trie;
  bool success;

  trie.Insert("key1", 10);
  int value = trie.GetValue<int>("key1", &success);
  EXPECT_TRUE(success);
  EXPECT_EQ(value, 10);

  trie.GetValue<int>("nonexistent", &success);
  EXPECT_FALSE(success);
}

// 测试Insert方法
TEST(TrieTest, Insert) {
  Trie trie;
  bool inserted = trie.Insert("key1", 20);
  EXPECT_TRUE(inserted);

  int value;
  bool success;

  value = trie.GetValue<int>("key1", &success);
  EXPECT_TRUE(success);
  EXPECT_EQ(value, 20);

  // 插入新的值会被拒绝
  inserted = trie.Insert("key1", 30);
  EXPECT_FALSE(inserted);

  value = trie.GetValue<int>("key1", &success);
  EXPECT_TRUE(success);
  EXPECT_EQ(value, 20);

  inserted = trie.Insert("key11", 33);
  EXPECT_TRUE(inserted);

  value = trie.GetValue<int>("key11", &success);
  EXPECT_TRUE(success);
  EXPECT_EQ(value, 33);
}

// 测试Remove方法
TEST(TrieTest, Remove) {
  Trie trie;
  trie.Insert("key1", 10);

  bool success;
  trie.GetValue<int>("key1", &success);
  EXPECT_TRUE(success);

  bool removed = trie.Remove("key1");
  EXPECT_TRUE(removed);

  trie.GetValue<int>("key1", &success);
  EXPECT_FALSE(success);
}

// 测试Trie构造函数
TEST(TrieTest, Constructor) {
  Trie trie;
  bool success;
  trie.GetValue<int>("key1", &success);
  EXPECT_FALSE(success);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
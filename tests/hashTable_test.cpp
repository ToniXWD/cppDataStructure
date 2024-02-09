#include "../include/hashTable.hpp"
#include <cstddef>
#include <gtest/gtest.h>
#include <iostream>

// 测试构造函数
TEST(HashTableTest, ConstructTest) {
  HashTable<int, int> hashTable(5);
  EXPECT_EQ(0, hashTable.size());
}

// 测试插入功能
TEST(HashTableTest, InsertTEst) {
  HashTable<int, int> hashTable;
  hashTable.insert(1);
  hashTable.insert(2);
  hashTable.insert(3);

  EXPECT_TRUE(hashTable.find(1));
  EXPECT_TRUE(hashTable.find(2));
  EXPECT_TRUE(hashTable.find(3));
  EXPECT_EQ(3, hashTable.size());
}

// 测试查找功能
TEST(HashTableTest, FindTest) {
  HashTable<int, int> hashTable;
  hashTable.insert(10);
  hashTable.insert(20);
  EXPECT_TRUE(hashTable.find(10));
  EXPECT_FALSE(hashTable.find(30));
}

// 测试删除功能
TEST(HashTableTest, EraseTest) {
  HashTable<int, int> hashTable;
  hashTable.insert(10);
  hashTable.insert(20);
  hashTable.erase(10);
  EXPECT_FALSE(hashTable.find(10));
  EXPECT_TRUE(hashTable.find(20));
  EXPECT_EQ(1, hashTable.size());
}

// 测试重哈希功能
TEST(HashTableTest, RehashTest) {
  HashTable<int, int> hashTable(2);

  for (size_t i = 0; i < 20; i++) {
    hashTable.insert(i + 1);
    // hashTable.print();
  }

  for (size_t i = 0; i < 20; i++) {
    EXPECT_TRUE(hashTable.find(i + 1));
  }

  hashTable.erase(5);
  EXPECT_FALSE(hashTable.find(5));
}

// 测试迭代器功能
TEST(HashTableTest, IteratorTest) {
  HashTable<int, int> hashTable(2);

  for (size_t i = 0; i < 20; i++) {
    hashTable.insert(i + 1);
    // hashTable.print();
  }

  for (auto &kv : hashTable) {
    std::cout << "key: " << kv.first << ", val: " << kv.second << '\n';
  }
}
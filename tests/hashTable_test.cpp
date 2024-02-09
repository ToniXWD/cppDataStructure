#include "../include/hashTable.hpp"
#include <gtest/gtest.h>

// 测试构造函数
TEST(HashTableTest, Construct) {
  HashTable<int, int> hashTable(5);
  EXPECT_EQ(0, hashTable.size());
}

// 测试插入功能
TEST(HashTableTest, Insert) {
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
TEST(HashTableTest, Find) {
  HashTable<int, int> hashTable;
  hashTable.insert(10);
  hashTable.insert(20);
  EXPECT_TRUE(hashTable.find(10));
  EXPECT_FALSE(hashTable.find(30));
}

// 测试删除功能
TEST(HashTableTest, Erase) {
  HashTable<int, int> hashTable;
  hashTable.insert(10);
  hashTable.insert(20);
  hashTable.erase(10);
  EXPECT_FALSE(hashTable.find(10));
  EXPECT_TRUE(hashTable.find(20));
  EXPECT_EQ(1, hashTable.size());
}

// 测试重哈希功能
TEST(HashTableTest, Rehash) {
  HashTable<int, int> hashTable(2);
  hashTable.insert(1);
  // hashTable.print();
  hashTable.insert(2);
  // hashTable.print();
  hashTable.insert(3);
  // hashTable.print();

  EXPECT_TRUE(hashTable.find(1));
  EXPECT_TRUE(hashTable.find(2));
  EXPECT_TRUE(hashTable.find(3));
  // 因为初始大小为2，插入3个元素后，触发重哈希，大小应该变为4
  EXPECT_GE(4, hashTable.size());
}
#include "../include/multimap.hpp"
#include <gtest/gtest.h>

// Tests that the MultiMap is initially empty.
TEST(MultiMapTest, IsInitiallyEmpty) {
  MultiMap<int, std::string> map;
  EXPECT_TRUE(map.empty());
}

// Tests insertion into the MultiMap.
TEST(MultiMapTest, CanInsertElements) {
  MultiMap<int, std::string> map;
  map.insert(1, "one");
  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 1);
}

// Tests retrieval from the MultiMap.
TEST(MultiMapTest, CanRetrieveElements) {
  MultiMap<int, std::string> map;
  map.insert(1, "one");
  Vector<std::string> result = map.find(1);
  ASSERT_EQ(result.getSize(), 1);
  EXPECT_EQ(result[0], "one");
}

// Tests counting elements in the MultiMap.
TEST(MultiMapTest, CanCountElements) {
  MultiMap<int, std::string> map;
  map.insert(1, "one");
  map.insert(1, "another one");
  EXPECT_EQ(map.count(1), 2);
}

// Tests erasing elements from the MultiMap.
TEST(MultiMapTest, CanEraseElements) {
  MultiMap<int, std::string> map;
  map.insert(1, "one");
  map.erase(1);
  EXPECT_TRUE(map.empty());
}

// Tests clearing the MultiMap.
TEST(MultiMapTest, CanClearMultiMap) {
  MultiMap<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  map.clear();
  EXPECT_TRUE(map.empty());
}

// Tests the MultiMap does not find a non-existing key.
TEST(MultiMapTest, DoesNotFindNonExistingKey) {
  MultiMap<int, std::string> map;
  EXPECT_EQ(map.count(1),0);
}

// Tests the MultiMap does not count a non-existing key.
TEST(MultiMapTest, DoesNotCountNonExistingKey) {
  MultiMap<int, std::string> map;
  EXPECT_EQ(map.count(1), 0);
}

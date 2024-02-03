#include "../include/set.hpp" // Update this include path to wherever the 'Set' class definition is
#include <gtest/gtest.h>
#include <random>
#include <unordered_set>

TEST(SetTest, InsertAndCount) {
  Set<int> mySet;

  // Insert some elements and check count
  mySet.insert(1);
  mySet.insert(2);
  mySet.insert(3);

  EXPECT_EQ(mySet.count(1), 1);
  EXPECT_EQ(mySet.count(2), 1);
  EXPECT_EQ(mySet.count(3), 1);
  EXPECT_EQ(mySet.count(4), 0); // Not inserted, should be 0
}

TEST(SetTest, EraseAndEmpty) {
  Set<int> mySet;

  // Insert elements
  mySet.insert(1);
  mySet.insert(2);

  // Check size before erasure
  EXPECT_EQ(mySet.size(), 2);

  // Erase one element and check size
  mySet.erase(1);
  EXPECT_EQ(mySet.size(), 1);
  EXPECT_EQ(mySet.count(1), 0);

  // Erase another element and check if empty
  mySet.erase(2);
  EXPECT_TRUE(mySet.empty());
}

TEST(SetTest, Size) {
  Set<int> mySet;

  // Insert elements and check size
  mySet.insert(10);
  mySet.insert(20);
  mySet.insert(30);

  EXPECT_EQ(mySet.size(), 3);

  // Erase elements and check size
  mySet.erase(10);
  EXPECT_EQ(mySet.size(), 2);
  mySet.erase(20);
  EXPECT_EQ(mySet.size(), 1);
}

TEST(SetTest, RandomOperation) {
  Set<int> mySet;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 2000000);
  std::unordered_set<int> collect;

  // Insert random elements
  for (int i = 0; i < 1000; ++i) {
    int number = dis(gen);
    mySet.insert(number);
    collect.insert(number);
  }

  EXPECT_EQ(mySet.size(), collect.size());

  // Erase half of the elements
  int targetSize = collect.size() / 2;
  while (collect.size() > targetSize) {
    int number = *collect.begin();
    mySet.erase(number);
    collect.erase(number);
  }

  EXPECT_EQ(mySet.size(), collect.size());

  // Insert more random elements
  for (int i = 0; i < 1000; ++i) {
    int number = dis(gen);
    mySet.insert(number);
    collect.insert(number);
  }

  EXPECT_EQ(mySet.size(), collect.size());

  // Erase all elements
  while (!collect.empty()) {
    int number = *collect.begin();
    mySet.erase(number);
    collect.erase(number);
  }

  EXPECT_TRUE(mySet.empty());
  EXPECT_EQ(mySet.size(), collect.size());
}
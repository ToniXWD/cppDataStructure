#include "../include/unordered_set.hpp"
#include <gtest/gtest.h>

// Test case for basic functionality of Unordered_set
TEST(UnorderedSetTest, BasicFunctionality) {
  Unordered_set<int, int>
      set; // Assuming Val type is the same as Key for simplicity

  // Test empty set properties
  EXPECT_TRUE(set.empty());
  EXPECT_EQ(0, set.size());

  // Test insertion
  set.insert(1);
  EXPECT_EQ(1, set.size());
  EXPECT_FALSE(set.empty());

  // Test find for existing and non-existing elements
  int *found = set.find(1);
  EXPECT_NE(nullptr, found);
  EXPECT_EQ(1, *found);
  EXPECT_EQ(nullptr, set.find(2));

  // Test erase
  set.erase(1);
  EXPECT_EQ(0, set.size());
  EXPECT_EQ(nullptr, set.find(1));

  // Test clear
  set.insert(1);
  set.insert(2);
  set.insert(3);
  EXPECT_EQ(3, set.size());
  set.clear();
  EXPECT_TRUE(set.empty());
}

// Test case for more complex functionality of Unordered_set
TEST(UnorderedSetTest, ComplexFunctionality) {
  Unordered_set<int, int> set;

  // Insert multiple elements
  for (int i = 0; i < 10; ++i) {
    set.insert(i);
  }
  EXPECT_EQ(10, set.size());

  // Find all inserted elements
  for (int i = 0; i < 10; ++i) {
    int *found = set.find(i);
    ASSERT_NE(nullptr, found);
    EXPECT_EQ(i, *found);
  }

  // Attempt to find non-inserted elements
  for (int i = 10; i < 20; ++i) {
    EXPECT_EQ(nullptr, set.find(i));
  }

  // Remove half of the elements
  for (int i = 0; i < 5; ++i) {
    set.erase(i);
  }
  EXPECT_EQ(5, set.size());

  // Ensure erased elements are not found
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(nullptr, set.find(i));
  }

  // Ensure the remaining elements are still there
  for (int i = 5; i < 10; ++i) {
    int *found = set.find(i);
    ASSERT_NE(nullptr, found);
    EXPECT_EQ(i, *found);
  }
}
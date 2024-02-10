#include "../include/heap.hpp"
#include <gtest/gtest.h>

// Test case for inserting elements into the heap
TEST(HeapTest, InsertAndSize) {
  Heap<int> minHeap;
  minHeap.insert(5);
  minHeap.insert(2);
  minHeap.insert(8);

  EXPECT_EQ(minHeap.size(), 3);
}

// Test case for removing the root element
TEST(HeapTest, RemoveRoot) {
  Heap<int> minHeap;
  minHeap.insert(5);
  minHeap.insert(2);
  minHeap.insert(8);

  EXPECT_EQ(minHeap.removeRoot(), 2); // Assuming a min heap
  EXPECT_EQ(minHeap.size(), 2);
}

// Test case to check heap property is maintained after insertions
TEST(HeapTest, HeapPropertyAfterInsertion) {
  Heap<int> minHeap;
  minHeap.insert(5);
  minHeap.insert(2);
  minHeap.insert(8);
  minHeap.insert(1);
  minHeap.insert(3);

  EXPECT_EQ(minHeap.removeRoot(), 1);
  EXPECT_EQ(minHeap.removeRoot(), 2);
  EXPECT_EQ(minHeap.removeRoot(), 3);
  EXPECT_EQ(minHeap.removeRoot(), 5);
  EXPECT_EQ(minHeap.removeRoot(), 8);
}

// Test case for handling removal from an empty heap
TEST(HeapTest, RemoveFromEmptyHeap) {
  Heap<int> minHeap;
  EXPECT_THROW(minHeap.removeRoot(), std::out_of_range);
}

// Test case for dynamic resizing of the heap
TEST(HeapTest, ResizeHeap) {
  Heap<int> minHeap;
  size_t initialCapacity = 32; // Assuming initial capacity is 32
  for (int i = 0; i < initialCapacity + 1; ++i) {
    minHeap.insert(i);
  }

  EXPECT_GT(minHeap.size(), initialCapacity);
  for (int i = 0; i <= static_cast<int>(initialCapacity); ++i) {
    EXPECT_EQ(minHeap.removeRoot(), i); // Assuming a min heap
  }
}

// Test case for max heap property
TEST(HeapTest, MaxHeapProperty) {
  Heap<int, std::greater<int>> maxHeap;
  maxHeap.insert(5);
  maxHeap.insert(2);
  maxHeap.insert(8);
  maxHeap.insert(1);
  maxHeap.insert(3);
  maxHeap.insert(26);
  maxHeap.insert(-5);

  EXPECT_EQ(maxHeap.removeRoot(), 26);
  EXPECT_EQ(maxHeap.removeRoot(), 8);
  EXPECT_EQ(maxHeap.removeRoot(), 5);
  EXPECT_EQ(maxHeap.removeRoot(), 3);
  EXPECT_EQ(maxHeap.removeRoot(), 2);
  EXPECT_EQ(maxHeap.removeRoot(), 1);
  EXPECT_EQ(maxHeap.removeRoot(), -5);
}
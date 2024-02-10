#include "../include/priority_queue.hpp"
#include <gtest/gtest.h>

TEST(PriorityQueueTest, IsInitiallyEmpty) {
    PriorityQueue<int> queue;
    EXPECT_TRUE(queue.empty());
}

TEST(PriorityQueueTest, InsertIncreasesSize) {
    PriorityQueue<int> queue;
    queue.push(1);
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 1);
}

TEST(PriorityQueueTest, PopDecreasesSize) {
    PriorityQueue<int> queue;
    queue.push(1);
    queue.pop();
    EXPECT_TRUE(queue.empty());
}

TEST(PriorityQueueTest, TopReturnsHighestPriority) {
    PriorityQueue<int> queue;
    queue.push(3);
    queue.push(1);
    queue.push(2);
    EXPECT_EQ(queue.top(), 1); // Assuming a min-heap
}

TEST(PriorityQueueTest, MaintainsHeapProperty) {
    PriorityQueue<int> queue;
    queue.push(5);
    queue.push(1);
    queue.push(3);
    EXPECT_EQ(queue.top(), 1); // 1 should be the root of the min-heap
    queue.pop();
    EXPECT_EQ(queue.top(), 3); // After popping 1, 3 should be the root
    queue.pop();
    EXPECT_EQ(queue.top(), 5); // Finally, 5 should be the root
}

TEST(PriorityQueueTest, PopThrowsWhenEmpty) {
    PriorityQueue<int> queue;
    EXPECT_THROW(queue.pop(), std::out_of_range);
}

TEST(PriorityQueueTest, TopThrowsWhenEmpty) {
    PriorityQueue<int> queue;
    EXPECT_THROW(queue.top(), std::out_of_range);
}
#include "../include/queue.hpp" // Include your Queue class header file
#include <gtest/gtest.h>

// Test case for an empty queue
TEST(QueueTest, IsInitiallyEmpty) {
  Queue<int> queue;
  EXPECT_TRUE(queue.isEmpty());
}

// Test case for enqueue and front operations
TEST(QueueTest, EnqueueAndFront) {
  Queue<int> queue;
  queue.enqueue(1);
  EXPECT_EQ(1, queue.front());
  queue.enqueue(2);
  EXPECT_EQ(1, queue.front()); // The front should still be 1
}

// Test case for dequeue operation
TEST(QueueTest, Dequeue) {
  Queue<int> queue;
  queue.enqueue(1);
  queue.enqueue(2);
  queue.dequeue();
  EXPECT_EQ(2, queue.front()); // After dequeue, the front should now be 2
}

// Test case for queue size
TEST(QueueTest, Size) {
  Queue<int> queue;
  EXPECT_EQ(0, queue.size());
  queue.enqueue(1);
  queue.enqueue(2);
  EXPECT_EQ(2, queue.size());
  queue.dequeue();
  EXPECT_EQ(1, queue.size());
}

// Test case for dequeuing from an empty queue
TEST(QueueTest, DequeueEmptyQueueThrows) {
  Queue<int> queue;
  EXPECT_THROW(queue.dequeue(), std::out_of_range);
}

// Test case for accessing the front of an empty queue
TEST(QueueTest, FrontEmptyQueueThrows) {
  Queue<int> queue;
  EXPECT_THROW(queue.front(), std::out_of_range);
}

// Test to ensure the queue is empty after dequeuing all elements
TEST(QueueTest, IsEmptyAfterDequeues) {
  Queue<int> queue;
  queue.enqueue(1);
  queue.enqueue(2);
  queue.dequeue();
  queue.dequeue();
  EXPECT_TRUE(queue.isEmpty());
}

// Test to ensure the front element is correct after multiple enqueue and
// dequeue operations
TEST(QueueTest, FrontAfterMultipleEnqueueAndDequeue) {
  Queue<int> queue;
  queue.enqueue(1);
  queue.enqueue(2);
  queue.dequeue();
  queue.enqueue(3);
  EXPECT_EQ(2, queue.front()); // Should be 2 after dequeuing 1
}

// More complex test case that combines several operations
TEST(QueueTest, MultipleOperations) {
  Queue<int> queue;
  // Start with an empty queue
  EXPECT_TRUE(queue.isEmpty());

  // Enqueue elements onto the queue
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);
  EXPECT_EQ(3, queue.size());

  // Access the front element without dequeuing
  EXPECT_EQ(1, queue.front());

  // Dequeue an element and check size and front
  queue.dequeue();
  EXPECT_EQ(2, queue.size());
  EXPECT_EQ(2, queue.front());

  // Dequeue all elements and check if the queue is empty
  queue.dequeue();
  queue.dequeue();
  EXPECT_TRUE(queue.isEmpty());
  EXPECT_EQ(0, queue.size());

  // Test for exception when trying to access or dequeue from empty queue
  EXPECT_THROW(queue.front(), std::out_of_range);
  EXPECT_THROW(queue.dequeue(), std::out_of_range);
}
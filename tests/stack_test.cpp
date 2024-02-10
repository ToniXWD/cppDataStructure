#include "../include/stack.hpp" // Assuming stack.hpp is the correct path for your Stack class
#include <gtest/gtest.h>

// Test case for an empty stack
TEST(StackTest, IsInitiallyEmpty) {
  Stack<int> stack;
  EXPECT_TRUE(stack.isEmpty());
}

// Test case for push and top operations
TEST(StackTest, PushAndTop) {
  Stack<int> stack;
  stack.push(1);
  EXPECT_EQ(1, stack.top());
  stack.push(2);
  EXPECT_EQ(2, stack.top()); // The top should now be 2
}

// Test case for pop operation
TEST(StackTest, Pop) {
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.pop();
  EXPECT_EQ(1, stack.top()); // After popping, the top should now be 1
}

// Test case for stack size
TEST(StackTest, Size) {
  Stack<int> stack;
  EXPECT_EQ(0, stack.size());
  stack.push(1);
  stack.push(2);
  EXPECT_EQ(2, stack.size());
  stack.pop();
  EXPECT_EQ(1, stack.size());
}

// Test case for popping from an empty stack
TEST(StackTest, PopEmptyStackThrows) {
  Stack<int> stack;
  EXPECT_THROW(stack.pop(), std::out_of_range);
}

// Test case for accessing the top of an empty stack
TEST(StackTest, TopEmptyStackThrows) {
  Stack<int> stack;
  EXPECT_THROW(stack.top(), std::out_of_range);
}

// Test to ensure the stack is empty after popping all elements
TEST(StackTest, IsEmptyAfterPops) {
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.pop();
  stack.pop();
  EXPECT_TRUE(stack.isEmpty());
}

// Test to ensure the top element is correct after multiple push and pop
// operations
TEST(StackTest, TopAfterMultiplePushAndPop) {
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.pop();
  stack.push(3);
  EXPECT_EQ(3, stack.top());
}

// More complex test case that combines several operations
TEST(StackTest, MultipleOperations) {
  Stack<int> stack;
  // Start with an empty stack
  EXPECT_TRUE(stack.isEmpty());

  // Push elements onto the stack
  stack.push(1);
  stack.push(2);
  stack.push(3);
  EXPECT_EQ(3, stack.size());

  // Access the top element without popping
  EXPECT_EQ(3, stack.top());

  // Pop an element and check size and top
  stack.pop();
  EXPECT_EQ(2, stack.size());
  EXPECT_EQ(2, stack.top());

  // Pop all elements and check if the stack is empty
  stack.pop();
  stack.pop();
  EXPECT_TRUE(stack.isEmpty());
  EXPECT_EQ(0, stack.size());

  // Test for exception when trying to access or pop from empty stack
  EXPECT_THROW(stack.top(), std::out_of_range);
  EXPECT_THROW(stack.pop(), std::out_of_range);
}
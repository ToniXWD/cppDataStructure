#include "include/heap.hpp"
#include <iostream>
#include <string>

int main() {
  Heap<int> minHeap; // 默认是最小堆
  minHeap.insert(3);
  minHeap.insert(1);
  minHeap.insert(2);

  std::cout << minHeap.removeRoot() << std::endl; // 应该输出 1

  Heap<int, std::greater<int>> maxHeap; // 指定为最大堆
  maxHeap.insert(3);
  maxHeap.insert(1);
  maxHeap.insert(2);

  std::cout << maxHeap.removeRoot() << std::endl; // 应该输出 3

  return 0;
}
#include "include/multiset.hpp"
#include <iostream>


int main() {
  // 创建一个 MultiSet 的实例
  MultiSet<int> myMultiSet;

  // 插入元素
  std::cout << "Inserting elements...\n";
  myMultiSet.insert(10);
  myMultiSet.insert(20);
  myMultiSet.insert(20);
  myMultiSet.insert(30);
  myMultiSet.insert(10);

  // 显示 MultiSet 的大小
  std::cout << "Size of the MultiSet: " << myMultiSet.size() << std::endl;

  // 计数特定元素的数量
  std::cout << "Count of 20: " << myMultiSet.count(20) << std::endl;
  std::cout << "Count of 10: " << myMultiSet.count(10) << std::endl;
  std::cout << "Count of 30: " << myMultiSet.count(30) << std::endl;

  // 删除元素
  std::cout << "Erasing element 20...\n";
  myMultiSet.erase(20);

  // 显示 MultiSet 的大小
  std::cout << "Size of the MultiSet after erasing 20: " << myMultiSet.size()
            << std::endl;

  // 检查 MultiSet 是否为空
  std::cout << "Is the MultiSet empty? " << (myMultiSet.empty() ? "Yes" : "No")
            << std::endl;

  // 再次计数特定元素的数量
  std::cout << "Count of 20 after erasing: " << myMultiSet.count(20)
            << std::endl;

  return 0;
}
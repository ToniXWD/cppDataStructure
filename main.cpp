#include "./include/deque.hpp"
#include "./include/list.hpp"
#include "./include/rbTree.hpp"
#include <iostream>

int deque_test() {
  // 创建一个 Deque 对象
  Deque<int> myDeque;

  // 在前端和后端插入元素
  myDeque.push_front(1);
  myDeque.push_back(2);
  myDeque.push_front(0);
  myDeque.push_back(3);

  // 随机访问元素并修改
  std::cout << "Element at index 2: " << myDeque[2] << std::endl;
  myDeque[2] = 11;

  // 打印元素和deque大小
  std::cout << "Original Deque:";
  myDeque.printElements();
  std::cout << "Size: " << myDeque.getSize() << std::endl;

  // 从前端和后端移除元素
  myDeque.pop_front();
  myDeque.pop_back();
  std::cout << "Deque after pop_front and pop_back:";
  myDeque.printElements();

  // 清空deque
  myDeque.clear();
  std::cout << "Deque after clear:";
  myDeque.printElements();
  std::cout << "Size: " << myDeque.getSize() << std::endl;

  return 0;
}

int list_test() {
  // 创建一个 List 对象
  List<int> myList;

  // 在链表末尾添加元素
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);

  // 打印元素和链表大小
  std::cout << "Original List:";
  myList.printElements();
  std::cout << "Size: " << myList.getSize() << std::endl;

  // 在链表开头添加元素
  myList.push_front(0);
  std::cout << "List after push_front:";
  myList.printElements();

  // 访问链表中的元素
  std::cout << "Element at index 2: " << myList[2] << std::endl;

  // 删除链表末尾的元素
  myList.pop_back();
  std::cout << "List after pop_back:";
  myList.printElements();

  // 删除链表开头的元素
  myList.pop_front();
  std::cout << "List after pop_front:";
  myList.printElements();

  // 清空链表
  myList.clear();
  std::cout << "List after clear:";
  myList.printElements();
  std::cout << "Size: " << myList.getSize() << std::endl;

  return 0;
}

int rbTree_test() {
  // 创建 RedBlackTree 对象
  RedBlackTree<int> mySet;

  // 插入元素
  mySet.insert(42);
  mySet.insert(21);
  mySet.insert(63);
  mySet.insert(10);
  mySet.insert(4);
  mySet.insert(30);
  mySet.insert(36);
  mySet.insert(92);
  mySet.insert(75);
  mySet.insert(87);
  mySet.insert(58);

  mySet.remove(30);
  mySet.remove(63);

  // 打印集合
  std::cout << "Original Set:" << std::endl;
  mySet.print();

  // 插入重复元素（不会重复插入）
  mySet.insert(42);

  // 打印修改后的集合
  std::cout << "Set after inserting duplicate element:" << std::endl;
  mySet.print();

  std::cout << "红黑树长度为: " << mySet.len() << std::endl;
  std::cout << "红黑树长度为(手动计算): " << mySet.getSizeByTranverse() << std::endl;
  std::cout << "红黑树高度为: " << mySet.blackHeight() << std::endl;

  mySet.remove(42);

  return 0;
}

int main() {
  // deque_test();
  // list_test();
  rbTree_test();
}

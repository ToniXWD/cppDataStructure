#include "include/multimap.hpp"
#include <iostream>
#include <string>

int main() {
  // 创建一个 MultiMap 实例，键和值都是 std::string 类型
  MultiMap<std::string, std::string> myMultiMap;

  // 插入一些键值对
  myMultiMap.insert("fruit", "apple");
  myMultiMap.insert("fruit", "banana");
  myMultiMap.insert("fruit", "apple"); // 允许重复的值
  myMultiMap.insert("vegetable", "carrot");
  myMultiMap.insert("vegetable", "broccoli");

  // 显示特定键的值的数量
  std::cout << "Number of fruits: " << myMultiMap.count("fruit") << std::endl;
  std::cout << "Number of vegetables: " << myMultiMap.count("vegetable")
            << std::endl;

  // 查找并显示特定键的所有值
  auto fruits = myMultiMap.find("fruit");
  std::cout << "Fruits: ";
  for (const auto &fruit : fruits) {
    std::cout << fruit << " ";
  }
  std::cout << std::endl;

  // 删除键为 "fruit" 的所有值
  myMultiMap.erase("fruit");
  std::cout << "Number of fruits after erase: " << myMultiMap.count("fruit")
            << std::endl;

  // 检查 MultiMap 是否为空
  std::cout << "Is the MultiMap empty? " << (myMultiMap.empty() ? "Yes" : "No")
            << std::endl;

  // 清空 MultiMap
  myMultiMap.clear();
  std::cout << "Is the MultiMap empty after clear? "
            << (myMultiMap.empty() ? "Yes" : "No") << std::endl;

  // 清空后再添加
  myMultiMap.insert("player", "Jordan");
  myMultiMap.insert("player", "Messi");
  std::cout << "Number of player: " << myMultiMap.count("player") << std::endl;

  auto players = myMultiMap.find("player");
  std::cout << "players: ";
  for (const auto &player : players) {
    std::cout << player << " ";
  }
  std::cout << std::endl;

  return 0;
}
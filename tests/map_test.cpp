#include "../include/map.hpp"
#include <algorithm>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <random>
#include <string>

// Demonstrate some basic assertions.
TEST(MapTest, BasicTest) {
  std::map<int, int> collect;
  Map<int, int> myMap;

  // 初始化随机数引擎，使用随机设备来获取种子
  std::random_device rd;

  std::mt19937 gen(rd()); // 使用 Mersenne Twister 生成器

  // 定义随机数分布，这里以生成[0, 99]范围内的随机整数为例
  std::uniform_int_distribution<> dis(0, 2000000);

  // 先插入一部分元素
  for (int i = 0; i < 1000; i++) {
    int random_number_key = dis(gen);
    int random_number_val = dis(gen);
    myMap[random_number_key] = random_number_val;
    collect[random_number_key] = random_number_val;

    ASSERT_EQ(myMap.size(), collect.size());
  }
}
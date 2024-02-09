#pragma once

#include "iterator.hpp"

// template <typename T, typename U>
// BaseIterator<T> &iterFind(BaseIterator<T> &begin, BaseIterator<T> &end,
//                           U &target) {
//   while (begin != end) {
//     if (*begin == target) {
//       return begin;
//     }
//     ++begin;
//   }
//   return begin;
// }

template <typename Iterator, typename U>
Iterator iterFind(Iterator begin, Iterator end, const U &target) {
  while (begin != end) {
    if (*begin == target) {
      return begin;
    }
    ++begin;
  }
  return end; // 注意这里返回end而不是begin，因为当找不到目标时应该返回end迭代器
}
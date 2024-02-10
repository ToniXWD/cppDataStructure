#pragma once

#include <algorithm>
#include <cstddef>
#include <functional> // 引入 std::less 和 std::greater
#include <stdexcept>
#include <tuple>

template <typename T, typename Compare = std::less<T>> class Heap {
private:
  size_t size_;
  size_t capacity_;
  T *arr;        // 从索引1开始
  Compare comp_; // 比较函数对象

public:
  Heap(size_t capacity = 32, const Compare &comp = Compare())
      : size_(0), capacity_(capacity), comp_(comp) {
    arr = new T[capacity_ + 1];
  }
  ~Heap() { delete[] arr; }

  void siftUp(size_t idx) {
    size_t parent_idx = idx / 2;
    while (idx != 1 && comp_(arr[idx], arr[parent_idx])) {
      std::swap(arr[idx], arr[parent_idx]);
      idx = parent_idx;
      parent_idx /= 2;
    }
  }

  void siftDown(size_t idx) {
    size_t l_son = 2 * idx;
    size_t r_son = 2 * idx + 1;

    while (l_son <= size_) {
      if (r_son <= size_) {
        size_t extreme_son_idx = comp_(arr[l_son], arr[r_son]) ? l_son : r_son;
        if (comp_(arr[idx], arr[extreme_son_idx])) {
          break;
        }
        std::swap(arr[idx], arr[extreme_son_idx]);
        idx = extreme_son_idx;
      } else {
        if (comp_(arr[idx], arr[l_son])) {
          break;
        }
        std::swap(arr[idx], arr[l_son]);
      }
      l_son = 2 * idx;
      r_son = 2 * idx + 1;
    }
  }

  void resize() {
    size_t new_capacity = capacity_ * 2;
    T *newArr = new T[new_capacity + 1];
    std::copy(arr, arr + capacity_ + 1, newArr);
    delete[] arr;
    capacity_ = new_capacity;
    arr = newArr;
  }

  void insert(const T &val) {
    if (size_ == capacity_) {
      resize();
    }
    size_++;

    arr[size_] = val;
    siftUp(size_);
  }

  T removeRoot() {
    if (size_ == 0) {
      throw std::out_of_range("Heap is empty");
    }
    T r = arr[1];
    arr[1] = arr[size_];
    size_--;
    siftDown(1);
    return r;
  }
  size_t size() const { return size_; }

  T getRoot() const {
    if (size_ == 0) {
      throw std::out_of_range("Heap is empty");
    }
    return arr[1];
  }
};
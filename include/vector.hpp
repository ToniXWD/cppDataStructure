#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename T> class Vector {
private:
  T *elements;     // 指向动态数组的指针
  size_t capacity; // 数组的容量
  size_t size;     // 数组中元素的个数

public:
  // 构造函数
  Vector() : elements(nullptr), capacity(0), size(0) {}

  // 析构函数
  ~Vector() { delete[] elements; }

  // 拷贝构造函数
  Vector(const Vector &other) : capacity(other.capacity), size(other.size) {
    elements = new T[capacity];
    std::copy(other.elements, other.elements + size, elements);
  }

  // 拷贝赋值操作符
  Vector &operator=(const Vector &other) {
    if (this != &other) {
      delete[] elements;
      capacity = other.capacity;
      size = other.size;
      elements = new T[capacity];
      std::copy(other.elements, other.elements + size, elements);
    }
    return *this;
  }

  // 添加元素到数组末尾
  void push_back(const T &value) {
    if (size == capacity) {
      // 如果数组已满，扩展容量
      reserve(capacity == 0 ? 1 : 2 * capacity);
    }
    elements[size++] = value;
  }

  // 获取数组中元素的个数
  size_t getSize() const { return size; }

  // 获取数组的容量
  size_t getCapacity() const { return capacity; }

  // 访问数组中的元素
  T &operator[](size_t index) {
    // 检查索引是否越界
    if (index >= size) {
      throw std::out_of_range("Index out of range");
    }
    return elements[index];
  }

  // const版本的访问数组中的元素
  const T &operator[](size_t index) const {
    // 检查索引是否越界
    if (index >= size) {
      throw std::out_of_range("Index out of range");
    }
    return elements[index];
  }

  // 在指定位置插入元素
  void insert(size_t index, const T &value) {
    if (index > size) {
      throw std::out_of_range("Index out of range");
    }
    if (size == capacity) {
      reserve(capacity == 0 ? 1 : capacity * 2);
    }
    for (size_t i = size; i > index; --i) {
      elements[i] = elements[i - 1];
    }
    elements[index] = value;
    ++size;
  }

  // 删除数组末尾的元素
  void pop_back() {
    if (size > 0) {
      --size;
    }
  }

  // 清空数组
  void clear() { size = 0; }

  // 使用迭代器遍历数组的开始位置
  T *begin() { return elements; }

  // 使用迭代器遍历数组的结束位置
  T *end() { return elements + size; }

  // 使用迭代器遍历数组的开始位置（const版本）
  const T *begin() const { return elements; }

  // 使用迭代器遍历数组的结束位置（const版本）
  const T *end() const { return elements + size; }

  // 打印数组中的元素
  void printElements() const {
    std::cout << "Elements:";
    for (size_t i = 0; i < size; ++i) {
      std::cout << " " << elements[i];
    }
    std::cout << std::endl;
  }

private:
  // 扩展数组容量
  void reserve(size_t newCapacity) {
    if (newCapacity > capacity) {
      T *newElements = new T[newCapacity];
      std::copy(elements, elements + size, newElements);
      delete[] elements;
      elements = newElements;
      capacity = newCapacity;
    }
  }
};

#include <iostream>
#include <stdexcept>

template <typename T> class List {
private:
  // 定义节点结构
  struct Node {
    T data;     // 数据
    Node *next; // 指向下一个节点的指针
    Node *prev; // 指向前一个节点的指针

    // 构造函数
    Node(const T &value, Node *nextNode = nullptr, Node *prevNode = nullptr)
        : data(value), next(nextNode), prev(prevNode) {}
  };

  Node *head;  // 头节点指针
  Node *tail;  // 尾节点指针
  size_t size; // 链表中节点的数量

public:
  // 构造函数
  List() : head(nullptr), tail(nullptr), size(0) {}

  // 析构函数
  ~List() { clear(); }

  // 在链表末尾添加元素
  void push_back(const T &value) {
    // 创建新的节点
    Node *newNode = new Node(value, nullptr, tail);

    if (tail) {
      // 如果链表非空，将尾节点的 next 指针指向新节点
      tail->next = newNode;
    } else {
      // 如果链表为空，新节点同时也是头节点
      head = newNode;
    }

    // 更新尾节点指针和链表大小
    tail = newNode;
    ++size;
  }

  // 在链表开头添加元素
  void push_front(const T &value) {
    // 创建新的节点
    Node *newNode = new Node(value, head, nullptr);

    if (head) {
      // 如果链表非空，将头节点的 prev 指针指向新节点
      head->prev = newNode;
    } else {
      // 如果链表为空，新节点同时也是尾节点
      tail = newNode;
    }

    // 更新头节点指针和链表大小
    head = newNode;
    ++size;
  }

  // 获取链表中节点的数量
  size_t getSize() const { return size; }

  // 访问链表中的元素
  T &operator[](size_t index) {
    // 从头节点开始遍历链表，找到第 index 个节点
    Node *current = head;
    for (size_t i = 0; i < index; ++i) {
      if (!current) {
        // 如果 index 超出链表长度，则抛出异常
        throw std::out_of_range("Index out of range");
      }
      current = current->next;
    }

    // 返回节点中的数据
    return current->data;
  }

  // const版本的访问链表中的元素
  const T &operator[](size_t index) const {
    // 从头节点开始遍历链表，找到第 index 个节点
    Node *current = head;
    for (size_t i = 0; i < index; ++i) {
      if (!current) {
        // 如果 index 超出链表长度，则抛出异常
        throw std::out_of_range("Index out of range");
      }
      current = current->next;
    }

    // 返回节点中的数据
    return current->data;
  }

  // 删除链表末尾的元素
  void pop_back() {
    if (size > 0) {
      // 获取尾节点的前一个节点
      Node *newTail = tail->prev;

      // 删除尾节点
      delete tail;

      // 更新尾节点指针和链表大小
      tail = newTail;
      if (tail) {
        tail->next = nullptr;
      } else {
        head = nullptr; // 如果链表为空，头节点也置为空
      }

      --size;
    }
  }

  // 删除链表开头的元素
  void pop_front() {
    if (size > 0) {
      // 获取头节点的下一个节点
      Node *newHead = head->next;

      // 删除头节点
      delete head;

      // 更新头节点指针和链表大小
      head = newHead;
      if (head) {
        head->prev = nullptr;
      } else {
        tail = nullptr; // 如果链表为空，尾节点也置为空
      }

      --size;
    }
  }

  // 清空链表
  void clear() {
    while (head) {
      // 从头节点开始，依次删除节点
      Node *temp = head;
      head = head->next;
      delete temp;
    }

    // 更新尾节点指针和链表大小
    tail = nullptr;
    size = 0;
  }

  // 使用迭代器遍历链表的开始位置
  Node *begin() { return head; }

  // 使用迭代器遍历链表的结束位置
  Node *end() { return nullptr; }

  // 使用迭代器遍历链表的开始位置（const版本）
  const Node *begin() const { return head; }

  // 使用迭代器遍历链表的结束位置（const版本）
  const Node *end() const { return nullptr; }

  // 打印链表中的元素
  void printElements() const {
    std::cout << "Elements:";
    for (Node *current = head; current; current = current->next) {
      std::cout << " " << current->data;
    }
    std::cout << std::endl;
  }
};
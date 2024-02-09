#include <exception>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <unordered_set>
#include <utility>

enum class Color { RED, BLACK };

template <typename Key> class RedBlackTree {
  class Node {
  public:
    Key key;
    Color color;
    Node *left;
    Node *right;
    Node *parent;

    // 构造函数
    Node(const Key &k, Color c, Node *p = nullptr)
        : key(k), color(c), left(nullptr), right(nullptr), parent(p) {}
    Node()
        : color(Color::BLACK), left(nullptr), right(nullptr), parent(nullptr) {}
  };

private:
  Node *root;
  size_t size;
  Node *Nil;

  // 查询某节点
  Node *lookUp(Key key) {
    Node *cmpNode = root;

    while (cmpNode) {
      if (key < cmpNode->key) {
        cmpNode = cmpNode->left;
      } else if (key > cmpNode->key) {
        cmpNode = cmpNode->right;
      } else {
        return cmpNode;
      }
    }
    return cmpNode;
  }

  // 右旋函数
  void rightRotate(Node *node) {
    Node *l_son = node->left; // 获取当前节点的左子节点

    // 当前节点的左子树变成左子节点的右子树
    node->left = l_son->right;
    // 如果左子节点的右子树非空，更新其父指针
    if (l_son->right) {
      l_son->right->parent = node;
    }

    // 左子节点升为当前节点位置，并处理父节点关系
    l_son->parent = node->parent;
    // 如果当前节点是根节点，更新根节点为左子节点
    if (!node->parent) {
      root = l_son;
      // 如果当前节点是其父节点的左子节点，更新父节点的左子节点为左子节点
    } else if (node == node->parent->left) {
      node->parent->left = l_son;
      // 如果当前节点是其父节点的右子节点，更新父节点的右子节点为左子节点
    } else {
      node->parent->right = l_son;
    }

    // 完成右旋转，将当前节点成为左子节点的右子节点
    l_son->right = node;
    // 更新当前节点的父节点为左子节点
    node->parent = l_son;
  }

  // 左旋
  // 是右旋的对称情况, 逻辑和右旋是一样的
  void leftRotate(Node *node) {
    Node *r_son = node->right;

    node->right = r_son->left;

    if (r_son->left) {
      r_son->left->parent = node;
    }

    r_son->parent = node->parent;
    if (!node->parent) {
      root = r_son;
    } else if (node == node->parent->left) {
      node->parent->left = r_son;
    } else {
      node->parent->right = r_son;
    }

    r_son->left = node;
    node->parent = r_son;
  }

  // 插入修复函数
  void insertFixup(Node *target) {
    // 当目标节点的父节点存在且父节点的颜色是红色时，需要修复
    while (target->parent && target->parent->color == Color::RED) {
      // 当目标节点的父节点是祖父节点的左子节点时
      if (target->parent == target->parent->parent->left) {
        Node *uncle = target->parent->parent->right; // 叔叔节点
        // 如果叔叔节点存在且为红色，进行颜色调整
        if (uncle && uncle->color == Color::RED) {
          target->parent->color = Color::BLACK; // 父节点设为黑色
          uncle->color = Color::BLACK;          // 叔叔节点设为黑色
          target->parent->parent->color = Color::RED; // 祖父节点设为红色
          target = target->parent->parent; // 将祖父节点设为下一个目标节点
        } else {
          // 如果目标节点是父节点的右子节点，进行左旋转
          if (target == target->parent->right) {
            target = target->parent; // 更新目标节点为父节点
            leftRotate(target);      // 对目标节点进行左旋
          }
          // 调整父节点和祖父节点的颜色，并进行右旋转
          target->parent->color = Color::BLACK;
          target->parent->parent->color = Color::RED;
          rightRotate(target->parent->parent);
        }
      } else {
        // 当目标节点的父节点是祖父节点的右子节点时，与上面对称
        Node *uncle = target->parent->parent->left; // 叔叔节点
        if (uncle && uncle->color == Color::RED) {
          target->parent->color = Color::BLACK;
          uncle->color = Color::BLACK;
          target->parent->parent->color = Color::RED;
          target = target->parent->parent;
        } else {
          if (target == target->parent->left) {
            target = target->parent; // 更新目标节点为父节点
            rightRotate(target);     // 对目标节点进行右旋
          }
          // 调整父节点和祖父节点的颜色，并进行左旋转
          target->parent->color = Color::BLACK;
          target->parent->parent->color = Color::RED;
          leftRotate(target->parent->parent);
        }
      }
    }
    // 确保根节点始终为黑色
    root->color = Color::BLACK;
  }

  // 插入节点函数
  void insertNode(const Key &key) {
    // 创建一个新节点，节点的颜色初始化为红色
    Node *newNode = new Node(key, Color::RED);
    Node *parent = nullptr; // 新节点的父节点指针
    Node *cmpNode = root;   // 用于比较的节点，初始为根节点

    // 遍历树，找到新节点的正确位置
    while (cmpNode) {
      parent = cmpNode; // 保留当前节点作为新节点的潜在父节点
      // 如果新节点的键小于当前比较节点的键，则向左子树移动
      if (newNode->key < cmpNode->key) {
        cmpNode = cmpNode->left;
        // 如果新节点的键大于当前比较节点的键，则向右子树移动
      } else if (newNode->key > cmpNode->key) {
        cmpNode = cmpNode->right;
        // 如果键相等，则说明树中已有相同键的节点，删除新节点并返回
      } else {
        delete newNode;
        return;
      }
    }

    // 树的大小增加
    size++;

    // 将新节点的父节点设置为找到的父节点位置
    newNode->parent = parent;
    // 如果父节点为空，说明树是空的，新节点成为根节点
    if (!parent) {
      root = newNode;
      // 如果新节点的键小于父节点的键，将新节点插入父节点的左子树
    } else if (newNode->key < parent->key) {
      parent->left = newNode;
      // 否则，将新节点插入父节点的右子树
    } else {
      parent->right = newNode;
    }

    // 插入新节点后，调用insertFixup函数来修复可能破坏的红黑树性质
    insertFixup(newNode);
  }

  // 中序遍历
  void inorderTraversal(Node *node) const {
    if (node) {
      inorderTraversal(node->left);
      std::cout << node->key << " ";
      inorderTraversal(node->right);
    }
  }
  // 辅助函数，用新节点替换旧节点
  void replaceNode(Node *targetNode, Node *newNode) {
    if (!targetNode->parent) {
      root = newNode;
    } else if (targetNode == targetNode->parent->left) {
      targetNode->parent->left = newNode;
    } else {
      targetNode->parent->right = newNode;
    }
    if (newNode) {
      newNode->parent = targetNode->parent;
    }
  }

  // 寻找以某个节点为根节点的子树中的最小节点
  Node *findMinimumNode(Node *node) {
    while (node->left) {
      node = node->left;
    }
    return node;
  }

  // removeFixup函数用于在删除节点后恢复红黑树的性质
  void removeFixup(Node *node) {
    // 如果节点为Nil并且没有父节点，说明它是唯一的节点，直接返回
    if (node == Nil && node->parent == nullptr) {
      return;
    }

    // 当我们没有到达根节点时继续循环
    while (node != root) {
      // 如果节点是其父节点的左子节点
      if (node == node->parent->left) {
        // 兄弟节点是节点父亲的右子节点
        Node *sibling = node->parent->right;

        // 情况1：节点的兄弟节点是红色
        if (getColor(sibling) == Color::RED) {
          // 重新着色兄弟节点和父节点，并进行左旋
          setColor(sibling, Color::BLACK);
          setColor(node->parent, Color::RED);
          leftRotate(node->parent);
          // 旋转后更新兄弟节点
          sibling = node->parent->right;
        }

        // 情况2：兄弟节点的两个子节点都是黑色
        if (getColor(sibling->left) == Color::BLACK &&
            getColor(sibling->right) == Color::BLACK) {
          // 重新着色兄弟节点并向上移动
          setColor(sibling, Color::RED);
          node = node->parent;
          // 如果父节点是红色，将其改为黑色并结束
          if (node->color == Color::RED) {
            node->color = Color::BLACK;
            node = root;
          }
        } else {
          // 情况3：兄弟节点的右子节点是黑色（左子节点是红色）
          if (getColor(sibling->right) == Color::BLACK) {
            // 重新着色兄弟节点和兄弟节点的左子节点，并进行右旋
            setColor(sibling->left, Color::BLACK);
            setColor(sibling, Color::RED);
            rightRotate(sibling);
            // 旋转后更新兄弟节点
            sibling = node->parent->right;
          }

          // 情况4：兄弟节点的右子节点是红色
          setColor(sibling, getColor(node->parent));
          setColor(node->parent, Color::BLACK);
          setColor(sibling->right, Color::BLACK);
          leftRotate(node->parent);
          // 移动到根节点结束
          node = root;
        }
      } else {
        // 当节点是其父节点的右子节点时，对称的情况
        Node *sibling = node->parent->left;

        if (getColor(sibling) == Color::RED) {
          setColor(sibling, Color::BLACK);
          setColor(node->parent, Color::RED);
          rightRotate(node->parent);
          sibling = node->parent->left;
        }

        if (getColor(sibling->right) == Color::BLACK &&
            getColor(sibling->left) == Color::BLACK) {
          setColor(sibling, Color::RED);
          node = node->parent;
          if (node->color == Color::RED) {
            node->color = Color::BLACK;
            node = root;
          }
        } else {
          if (getColor(sibling->left) == Color::BLACK) {
            setColor(sibling->right, Color::BLACK);
            setColor(sibling, Color::RED);
            leftRotate(sibling);
            sibling = node->parent->left;
          }
          setColor(sibling, getColor(node->parent));
          setColor(node->parent, Color::BLACK);
          setColor(sibling->left, Color::BLACK);
          rightRotate(node->parent);
          node = root;
        }
      }
    }
    // 确保当前节点是黑色的，以维持红黑树性质
    setColor(node, Color::BLACK);
  }

  // 获取颜色, 空指针为黑色
  Color getColor(Node *node) {
    if (node == nullptr) {
      return Color::BLACK;
    }
    return node->color;
  }

  void setColor(Node *node, Color color) {
    if (node == nullptr) {
      return;
    }
    node->color = color;
  }

  // 取消Nil哨兵的连接
  void dieConnectNil() {
    if (Nil == nullptr) {
      return;
    }
    if (Nil->parent != nullptr) {
      if (Nil == Nil->parent->left) {
        Nil->parent->left = nullptr;
      } else {
        Nil->parent->right = nullptr;
      }
    }
  }

  // 删除节点
  void deleteNode(Node *del) {
    Node *rep = del; // rep（替代节点）初始指向要删除的节点
    Node *child = nullptr;      // 要删除节点的孩子节点
    Node *parentRP;             // 替代节点的父节点
    Color origCol = rep->color; // 保存要删除节点的原始颜色

    // 如果删除节点没有左孩子
    if (!del->left) {
      rep = del->right;        // 替代节点指向删除节点的右孩子
      parentRP = del->parent;  // 更新替代节点的父节点
      origCol = getColor(rep); // 获取替代节点的颜色
      replaceNode(del, rep);   // 用替代节点替换删除节点
    }
    // 如果删除节点没有右孩子
    else if (!del->right) {
      rep = del->left;         // 替代节点指向删除节点的左孩子
      parentRP = del->parent;  // 更新替代节点的父节点
      origCol = getColor(rep); // 获取替代节点的颜色
      replaceNode(del, rep);   // 用替代节点替换删除节点
    }
    // 如果删除节点有两个孩子
    else {
      rep = findMinimumNode(
          del->right); // 找到删除节点右子树中的最小节点作为替代节点
      origCol = rep->color; // 保存替代节点的原始颜色
      // 如果替代节点不是删除节点的直接右孩子
      if (rep != del->right) {
        parentRP = rep->parent; // 更新替代节点的父节点
        child = rep->right; // 替代节点的右孩子变成要处理的孩子节点
        parentRP->left =
            child; // 替代节点的父节点的左孩子指向替代节点的孩子（因为替代节点是最小节点，所以不可能有左孩子）
        if (child != nullptr) {
          child->parent = parentRP; // 如果替代节点的孩子存在，则更新其父节点
        }
        // 将替代节点放到删除节点的位置
        del->left->parent = rep;
        del->right->parent = rep;
        rep->left = del->left;
        rep->right = del->right;
        // 如果删除节点有父节点，更新父节点的孩子指向
        if (del->parent != nullptr) {
          if (del == del->parent->left) {
            del->parent->left = rep;
            rep->parent = del->parent;
          } else {
            del->parent->right = rep;
            rep->parent = del->parent;
          }
        }
        // 如果删除节点没有父节点，说明它是根节点
        else {
          root = rep;
          root->parent = nullptr;
        }
      }
      // 如果替代节点是删除节点的直接右孩子
      else {
        child = rep->right; // 孩子节点指向替代节点的右孩子
        rep->left = del->left; // 替代节点的左孩子指向删除节点的左孩子
        del->left->parent = rep; // 更新左孩子的父节点
        // 更新删除节点父节点的孩子指向
        if (del->parent != nullptr) {
          if (del == del->parent->left) {
            del->parent->left = rep;
            rep->parent = del->parent;
          } else {
            del->parent->right = rep;
            rep->parent = del->parent;
          }
        }
        // 如果删除节点是根节点
        else {
          root = rep;
          root->parent = nullptr;
        }
        parentRP = rep; // 更新替代节点的父节点
      }
    }

    // 如果替代节点存在，更新其颜色为删除节点的颜色
    if (rep != nullptr) {
      rep->color = del->color;
    }
    // 如果替代节点不存在，将删除节点的颜色赋给origCol变量
    else {
      origCol = del->color;
    }

    // 如果原始颜色是黑色，需要进行额外的修复操作，因为黑色节点的删除可能会破坏红黑树的性质
    if (origCol == Color::BLACK) {
      // 如果存在孩子节点，进行修复操作
      if (child != nullptr) {
        removeFixup(child);
      }
      // 如果不存在孩子节点，将Nil节点（代表空节点）的父节点设置为替代节点的父节点
      else {
        Nil->parent = parentRP;
        // 如果替代节点的父节点存在，设置其对应的孩子指针为Nil节点
        if (parentRP != nullptr) {
          if (parentRP->left == nullptr) {
            parentRP->left = Nil;
          } else {
            parentRP->right = Nil;
          }
        }
        // 进行修复操作
        removeFixup(Nil);
        // 断开Nil节点与树的连接，因为在红黑树中Nil节点通常是单独存在的
        dieConnectNil();
      }
    }

    // 删除节点
    delete del;
  }

public:
  // 构造函数
  RedBlackTree() : root(nullptr), size(0), Nil(new Node()) {
    Nil->color = Color::BLACK;
  }

  // 插入
  void insert(const Key &key) { insertNode(key); }

  // 删除
  void remove(const Key &key) {
    Node *nodeToBeRemoved = lookUp(key);
    if (nodeToBeRemoved != nullptr) {
      deleteNode(nodeToBeRemoved);
      size--;
    }
  }

  int getSize() { return size; }

  bool empty() const { return size == 0; }

  bool isRootBlack() { return root == nullptr || root->color == Color::BLACK; }

  // 中序遍历打印
  void print() const {
    inorderTraversal(root);
    std::cout << std::endl;
  }

  // 析构函数
  ~RedBlackTree() {
    // 释放节点内存
    deleteTree(root);
  }

private:
  // 递归释放节点内存
  void deleteTree(Node *node) {
    if (node) {
      deleteTree(node->left);
      deleteTree(node->right);
      delete node;
    }
  }
};

int main() {
  RedBlackTree<int> tree; // 创建一个红黑树的实例，用于存储整数类型的数据

  std::random_device rd; // 随机数设备，用于生成随机种子

  std::mt19937 gen(rd()); // 使用随机种子初始化 Mersenne Twister 随机数生成器

  std::uniform_int_distribution<> dis(0, 2000000); // 定义一个分布，用于生成 0 到 200万之间的均匀分布的随机整数

  std::unordered_set<int> collect; // 创建一个哈希集合，用于跟踪已经插入到红黑树中的元素

  // 先插入一部分元素
  for (int i = 0; i < 1000; i++) {
    int random_number = dis(gen); // 生成一个随机整数
    tree.insert(random_number); // 将这个随机整数插入到红黑树中
    collect.insert(random_number); // 同时将这个随机整数添加到集合中
  }

  int first_resize = collect.size() / 2; // 计算集合当前大小的一半

  // 再删除一半的元素
  while (collect.size() > first_resize) {
    int del_target = *(collect.begin()); // 获取集合中的一个元素作为待删除目标
    collect.erase(collect.begin()); // 从集合中删除这个元素

    tree.remove(del_target); // 从红黑树中删除这个元素

    // 检查红黑树的大小是否与集合中剩余元素的数量一致
    if (tree.getSize() != collect.size()) {
      std::cout << "error" << '\n'; // 如果不一致，输出错误信息
      return -1; // 并终止程序
    }
  }

  // 再插入一部分元素
  for (int i = 0; i < 1000; i++) {
    int random_number = dis(gen); // 再次生成一个随机整数
    tree.insert(random_number); // 将这个随机整数插入到红黑树中
    collect.insert(random_number); // 同时将这个随机整数添加到集合中
  }

  // 再删除所有元素
  while (!collect.empty()) { // 当集合不为空时，继续删除操作
    int del_target = *(collect.begin()); // 获取集合中的一个元素作为待删除目标
    collect.erase(collect.begin()); // 从集合中删除这个元素

    tree.remove(del_target); // 从红黑树中删除这个元素

    // 再次检查红黑树的大小是否与集合中剩余元素的数量一致
    if (tree.getSize() != collect.size()) {
      std::cout << "error" << '\n'; // 如果不一致，输出错误信息
      return -1; // 并终止程序
    }
  }

  // 如果一切正常，主函数返回0表示程序正常终止
  return 0;
}

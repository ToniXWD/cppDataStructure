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

  // 左旋
  void leftRotate(Node *node) {
    Node *r_son = node->right;

    // 将右孩子的左子树交付给node作为右子树
    node->right = r_son->left;

    // 为右孩子的左子树安排新的父亲为root
    if (r_son->left) {
      r_son->left->parent = node;
    }

    // 将右孩子作为新的node, 分配原node的父节点并协调其关系
    r_son->parent = node->parent;
    if (!node->parent) {
      root = r_son;
    } else if (node == node->parent->left) {
      node->parent->left = r_son;
    } else {
      node->parent->right = r_son;
    }

    // node变成了右孩子的左节点
    r_son->left = node;
    node->parent = r_son;
  }

  // 右旋
  void rightRotate(Node *node) {
    Node *l_son = node->left;
    node->left = l_son->right;
    if (l_son->right) {
      l_son->right->parent = node;
    }
    l_son->parent = node->parent;
    if (!node->parent) {
      root = l_son;
    } else if (node == node->parent->left) {
      node->parent->left = l_son;
    } else {
      node->parent->right = l_son;
    }
    l_son->right = node;
    node->parent = l_son;
  }

  // 插入修复
  void insertFixup(Node *target) {
    while (target->parent && target->parent->color == Color::RED) {
      // 如果新节点的父节点是红色，就需要进行一些调整来修复树的性质，因为这违反了性质:
      // 红色节点的子节点必须是黑色的
      if (target->parent == target->parent->parent->left) {
        // 父节点是爷爷节点的左孩子
        Node *uncle = target->parent->parent->right;
        if (uncle && uncle->color == Color::RED) {
          // 叔叔节点为红色, 更改叔叔和父亲颜色即可
          target->parent->color = Color::BLACK;
          uncle->color = Color::BLACK;
          target->parent->parent->color = Color::RED;
          // 将当前节点设置为爷爷节点，继续进行调整
          target = target->parent->parent;
        } else {
          // 叔叔节点是黑色或不存在
          if (target == target->parent->right) {
            // 新节点是其父节点的右孩子, 将操作的目标节点变为其父亲, 并左旋
            target = target->parent;
            leftRotate(target);
          }
          // 更改操作节点的父节点为黑色, 爷爷节点为红色
          target->parent->color = Color::BLACK;
          target->parent->parent->color = Color::RED;
          // 右旋爷爷节点
          rightRotate(target->parent->parent);
        }
      } else {
        // 父节点是爷爷节点的右孩子
        Node *uncle = target->parent->parent->left;
        if (uncle && uncle->color == Color::RED) {
          // 叔叔节点为红色, 更改叔叔和父亲颜色即可
          target->parent->color = Color::BLACK;
          uncle->color = Color::BLACK;
          target->parent->parent->color = Color::RED;
          // 将当前节点设置为爷爷节点，继续进行调整
          target = target->parent->parent;
        } else {
          if (target == target->parent->left) {
            // 新节点是其父节点的左孩子, 将操作的目标节点变为其父亲, 并右旋
            target = target->parent;
            rightRotate(target);
          }
          // 更改底部节点为黑色, 爷爷节点为红色
          target->parent->color = Color::BLACK;
          target->parent->parent->color = Color::RED;
          // 左旋爷爷节点
          leftRotate(target->parent->parent);
        }
      }
    }
    // 其他情况:
    // 如果新节点的父节点是黑色，不违反红黑树的性质，不需要做任何额外的操作

    // 如果新插入的节点是根节点，仅将其颜色改为黑色即可满足所有性质
    root->color = Color::BLACK;
  }

  // 插入节点
  void insertNode(const Key &key) {
    Node *newNode = new Node(key, Color::RED);
    Node *parent = nullptr;
    Node *cmpNode = root;

    while (cmpNode) {
      parent = cmpNode;
      if (newNode->key < cmpNode->key) {
        cmpNode = cmpNode->left;
      } else if (newNode->key > cmpNode->key) {
        cmpNode = cmpNode->right;
      } else {
        // 如果已存在相同键值，不进行插入
        delete newNode;
        return;
      }
    }

    size++;

    newNode->parent = parent;
    if (!parent) {
      root = newNode;
    } else if (newNode->key < parent->key) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }

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
      // 如果删除了根节点, 用删除节点的子树补上
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

  void removeFixup(Node *node) {
    if (node == Nil && node->parent == nullptr) {
      return;
    }
    while (node != root) {
      if (node == node->parent->left) {
        // 是其父节点的左子节点
        Node *sibling = node->parent->right;
        if (getColor(sibling) == Color::RED) {
          // 如果兄弟节点是红色的，将其颜色设置为黑色
          setColor(sibling, Color::BLACK);
          // 将父节点颜色设置为红色
          setColor(node->parent, Color::RED);
          leftRotate(node->parent);
          // 旋转后兄弟节点的颜色也是黑色了
          sibling = node->parent->right;
        }

        if (getColor(sibling->left) == Color::BLACK &&
            getColor(sibling->right) == Color::BLACK) {
          // 如果兄弟节点也是黑色的，且兄弟节点的两个子节点都是黑色的
          // 将兄弟节点的颜色设置为红色
          setColor(sibling, Color::RED);
          // 将当前节点设置为其父节点, 下一次循环继续修复
          // 因为将兄弟节点的颜色设置为红色后, 从父节点开始的路径高度相同了,
          // 但又比其他的路径高度小了
          node = node->parent;
          if (node->color == Color::RED) {
            node->color = Color::BLACK;
            node = root;
          }
        } else {
          // 兄弟节点为黑色, 且至少有一个红色孩子
          // 下面的if统一将兄弟节点设置为右孩子为红色
          if (getColor(sibling->right) == Color::BLACK) {
            setColor(sibling->left, Color::BLACK);
            setColor(sibling, Color::RED);
            rightRotate(sibling);
            sibling = node->parent->right;
          }
          //   将兄弟节点的颜色设置为当前节点的父节点的颜色，将当前节点的父节点设置为黑色，将兄弟节点的右子节点设置为黑色
          setColor(sibling, getColor(node->parent));
          setColor(node->parent, Color::BLACK);
          setColor(sibling->right, Color::BLACK);
          //   当前节点的父节点进行左旋转, 左旋后各个路径上高度相同
          leftRotate(node->parent);
          node = root;
        }
      } else {
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
    setColor(node, Color::BLACK);
  }

  // Utility functions for getting and setting color of a node
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
    Node *rep = del;
    Node *child = nullptr;
    Node *parentRP;
    Color origCol = rep->color;

    if (!del->left) {
      rep = del->right;
      parentRP = del->parent;
      origCol = getColor(rep);
      replaceNode(del, rep);
    } else if (!del->right) {
      rep = del->left;
      parentRP = del->parent;
      origCol = getColor(rep);
      replaceNode(del, rep);
    } else {
      rep = findMinimumNode(del->right);
      origCol = rep->color;
      if (rep != del->right) {
        parentRP = rep->parent;
        child = rep->right;
        parentRP->left = child;
        if (child != nullptr) {
          child->parent = parentRP;
        }
        del->left->parent = rep;
        del->right->parent = rep;
        rep->left = del->left;
        rep->right = del->right;
        if (del->parent != nullptr) {
          if (del == del->parent->left) {
            del->parent->left = rep;
            rep->parent = del->parent;
          } else {
            del->parent->right = rep;
            rep->parent = del->parent;
          }
        } else {
          root = rep;
          root->parent = nullptr;
        }
      } else {
        child = rep->right;
        rep->left = del->left;
        del->left->parent = rep;
        if (del->parent != nullptr) {
          if (del == del->parent->left) {
            del->parent->left = rep;
            rep->parent = del->parent;
          } else {
            del->parent->right = rep;
            rep->parent = del->parent;
          }
        } else {
          root = rep;
          root->parent = nullptr;
        }
        parentRP = rep;
      }
    }

    if (rep != nullptr) {
      rep->color = del->color;
    } else {
      origCol = del->color;
    }

    if (origCol == Color::BLACK) {
      if (child != nullptr) {
        removeFixup(child);
      } else {
        Nil->parent = parentRP;
        if (parentRP != nullptr) {
          if (parentRP->left == nullptr) {
            parentRP->left = Nil;
          } else {
            parentRP->right = Nil;
          }
        }
        removeFixup(Nil);
        dieConnectNil();
      }
    }

    delete del;
  }

public:
  // 构造函数
  RedBlackTree() : root(nullptr), size(0), Nil(new Node()) {
    Nil->color = Color::BLACK;
  }

  // 插入元素
  void insert(const Key &key) { insertNode(key); }

  // 删除元素
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
  // 创建 RedBlackTree 对象
  RedBlackTree<int> tree;

  // 初始化随机数引擎，使用随机设备来获取种子
  std::random_device rd;

  std::mt19937 gen(rd()); // 使用 Mersenne Twister 生成器

  // 定义随机数分布，这里以生成[0, 99]范围内的随机整数为例
  std::uniform_int_distribution<> dis(0, 2000000);

  std::unordered_set<int> collect;

  // 先插入一部分元素
  for (int i = 0; i < 1000; i++) {
    int random_number = dis(gen);
    tree.insert(random_number);
    collect.insert(random_number);
  }

  int first_resize = collect.size() / 2;

  // 再删除一半的元素
  while (collect.size() > first_resize) {
    int del_target = *(collect.begin());
    collect.erase(collect.begin());

    tree.remove(del_target);

    if (tree.getSize() != collect.size()) {
      std::cout << "error" << '\n';
      return -1;
    }
  }

  // 再插入一部分元素
  for (int i = 0; i < 1000; i++) {
    int random_number = dis(gen);
    tree.insert(random_number);
    collect.insert(random_number);
  }

  // 再删除所有元素
  while (!collect.empty()) {
    int del_target = *(collect.begin());
    collect.erase(collect.begin());

    tree.remove(del_target);
    if (tree.getSize() != collect.size()) {
      std::cout << "error" << '\n';
      return -1;
    }
  }
}
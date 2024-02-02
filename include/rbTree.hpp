#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <utility>

enum class Color { RED, BLACK };

template <typename Key> class Node {
public:
  Key key;
  Color color;
  Node<Key> *left;
  Node<Key> *right;
  Node<Key> *parent;

  // 构造函数
  Node(const Key &k, Color c, Node<Key> *p = nullptr)
      : key(k), color(c), left(nullptr), right(nullptr), parent(p) {}
  Node()
      : color(Color::BLACK), left(nullptr), right(nullptr), parent(nullptr) {}

  int getLen() {
    // 获取某个子树的节点数量
    if (left == nullptr && right == nullptr) {
      return 1;
    }
    int l_len = 0;
    int r_len = 0;
    if (left != nullptr) {
      l_len = left->getLen();
    }
    if (right != nullptr) {
      r_len = right->getLen();
    }
    return 1 + l_len + r_len;
  }

  int getBlackHeight() {
    // 返回挡墙节点的黑色节点高度, 如果高度不合法, 返回-1
    if (left == nullptr && right == nullptr) {
      return color == Color::BLACK ? 1 : 0;
    }
    int hei_l = 0;
    int hei_r = 0;
    if (left != nullptr) {
      hei_l = left->getBlackHeight();
    }
    if (right != nullptr) {
      hei_r = right->getBlackHeight();
    }

    if (hei_l == -1 || hei_r == -1 || hei_l != hei_r) {
      return -1;
    }

    return color == Color::BLACK ? 1 + hei_l : hei_l;
  }

  bool isNoDoubleRed() {
    bool left_legal = true;
    bool right_legal = true;
    if (left != nullptr) {
      left_legal = left->isNoDoubleRed();
    }
    if (right != nullptr) {
      right_legal = right->isNoDoubleRed();
    }
    if (left_legal == false || right_legal == false) {
      return false;
    }
    if (color == Color::BLACK) {
      return true;
    }
    if (left != nullptr && left->color == Color::RED) {
      return false;
    }
    if (right != nullptr && right->color == Color::RED) {
      return false;
    }
    if (parent != nullptr && parent->color == Color::RED) {
      return false;
    }
    return true;
  }
};

template <typename Key>
void printTreeHelper(Node<Key> *root, std::string indent = "",
                     bool last = true) {
  // 当前节点为null，直接返回
  if (root == nullptr) {
    return;
  }

  // 打印缩进
  std::cout << indent;
  if (last) {
    std::cout << "R----";
    // 更新缩进标记为垂直线
    indent += "   ";
  } else {
    std::cout << "L----";
    // 更新缩进标记
    indent += "|  ";
  }

  // 打印当前节点的颜色和键值
  std::string color = root->color == Color::RED ? "RED" : "BLACK";
  std::cout << root->key << "(" << color << ")" << std::endl;

  // 递归打印左子树
  printTreeHelper(root->left, indent, false);
  // 递归打印右子树
  printTreeHelper(root->right, indent, true);
}

template <typename Key> void printTree(Node<Key> *root) {
  if (root == nullptr) {
    std::cout << "<empty tree>" << std::endl;
    return;
  }
  // 调用递归辅助函数
  printTreeHelper(root);
}

template <typename Key> class RedBlackTree {
private:
  Node<Key> *root;
  int size;
  Node<Key> *Nil;

  // 左旋
  void leftRotate(Node<Key> *node) {
    Node<Key> *r_son = node->right;

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
  void rightRotate(Node<Key> *node) {
    Node<Key> *l_son = node->left;
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
  void insertFixup(Node<Key> *target) {
    while (target->parent && target->parent->color == Color::RED) {
      // 如果新节点的父节点是红色，就需要进行一些调整来修复树的性质，因为这违反了性质:
      // 红色节点的子节点必须是黑色的
      if (target->parent == target->parent->parent->left) {
        // 父节点是爷爷节点的左孩子
        Node<Key> *uncle = target->parent->parent->right;
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
        Node<Key> *uncle = target->parent->parent->left;
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
    Node<Key> *newNode = new Node<Key>(key, Color::RED);
    Node<Key> *parent = nullptr;
    Node<Key> *cmpNode = root;

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

  Node<Key> *GetNode(Key key) {
    Node<Key> *cmpNode = root;

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

  // 中序遍历
  void inorderTraversal(Node<Key> *node) const {
    if (node) {
      inorderTraversal(node->left);
      std::cout << node->key << " ";
      inorderTraversal(node->right);
    }
  }
  // 辅助函数，用新节点替换旧节点
  void replaceNode(Node<Key> *targetNode, Node<Key> *newNode) {
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
  Node<Key> *findMinimumNode(Node<Key> *node) {
    while (node->left) {
      node = node->left;
    }
    return node;
  }

  void removeFixup(Node<Key> *node) {
    if (node == Nil && node->parent == nullptr) {
      return;
    }
    while (node != root) {
      if (node == node->parent->left) {
        // 是其父节点的左子节点
        Node<Key> *sibling = node->parent->right;
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
        Node<Key> *sibling = node->parent->left;
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
  Color getColor(Node<Key> *node) {
    if (node == nullptr) {
      return Color::BLACK;
    }
    return node->color;
  }

  void setColor(Node<Key> *node, Color color) {
    if (node == nullptr) {
      return;
    }
    node->color = color;
  }

  void removeNil() {
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
  void deleteNode(Node<Key> *nodeToDelete) {
    Node<Key> *nodeToReplace = nodeToDelete;
    Node<Key> *childOfReplaceNode = nullptr;
    Node<Key> *parentOfReplaceNode;
    Color originalColor = nodeToReplace->color;

    if (!nodeToDelete->left) {
      // 要删除的节点没有左子树, 两个子树都为空的情况也包含在内
      nodeToReplace = nodeToDelete->right;
      parentOfReplaceNode = nodeToDelete->parent;
      // 交换的节点虽然不需要删除, 但删除的颜色却等效于交换的节点
      originalColor = getColor(nodeToReplace);
      replaceNode(nodeToDelete, nodeToReplace);
    } else if (!nodeToDelete->right) {
      // 要删除的节点没有右子树
      nodeToReplace = nodeToDelete->left;
      parentOfReplaceNode = nodeToDelete->parent;
      // 交换的节点虽然不需要删除, 但删除的颜色却等效于交换的节点F
      originalColor = getColor(nodeToReplace);
      replaceNode(nodeToDelete, nodeToReplace);
    } else {
      // 2个子树都存在
      // 用要删除节点在中序遍历中的后继来替换当前要删除的元素
      nodeToReplace = findMinimumNode(nodeToDelete->right);
      // 交换的节点虽然不需要删除, 但删除的颜色却等效于交换的节点
      originalColor = nodeToReplace->color;
      if (nodeToReplace != nodeToDelete->right) {
        // 交换节点不是删除节点的右孩子
        parentOfReplaceNode = nodeToReplace->parent;
        // 交换的节点只可能有右孩子
        childOfReplaceNode = nodeToReplace->right;
        // 将交换的节点的右孩子托付给交换节点的父亲
        parentOfReplaceNode->left = childOfReplaceNode;
        if (childOfReplaceNode != nullptr) {
          // 交换的节点的右孩子非空, 重新指定其父节点
          childOfReplaceNode->parent = parentOfReplaceNode;
        }
        // 现在交换2个节点
        // 将删除节点的孩子分配给交换节点
        nodeToDelete->left->parent = nodeToReplace;
        nodeToDelete->right->parent = nodeToReplace;
        nodeToReplace->left = nodeToDelete->left;
        nodeToReplace->right = nodeToDelete->right;
        // 连接删除节点的父亲和交换节点
        if (nodeToDelete->parent != nullptr) {
          if (nodeToDelete == nodeToDelete->parent->left) {
            nodeToDelete->parent->left = nodeToReplace;
            nodeToReplace->parent = nodeToDelete->parent;
          } else {
            nodeToDelete->parent->right = nodeToReplace;
            nodeToReplace->parent = nodeToDelete->parent;
          }
        } else {
          // 如果删除节点就是根节点, 需要重新分配根节点为交换节点
          root = nodeToReplace;
          root->parent = nullptr;
        }
      } else {
        // 交换节点就是删除节点的右孩子
        // 直接将交换节点替代删除节点

        // 将删除节点的左孩子分配给交换节点
        nodeToReplace->left = nodeToDelete->left;
        nodeToDelete->left->parent = nodeToReplace;
        // 连接删除节点的父亲和交换节点
        if (nodeToDelete->parent != nullptr) {
          if (nodeToDelete == nodeToDelete->parent->left) {
            nodeToDelete->parent->left = nodeToReplace;
            nodeToReplace->parent = nodeToDelete->parent;
          } else {
            nodeToDelete->parent->right = nodeToReplace;
            nodeToReplace->parent = nodeToDelete->parent;
          }
        } else {
          // 如果删除节点就是根节点, 需要重新分配根节点为交换节点
          root = nodeToReplace;
          root->parent = nullptr;
        }
        // 这种情况下, 交换节点的父亲就是交换节点自己
        parentOfReplaceNode = nodeToReplace;
      }
    }

    // 将替换的节点颜色着色为删除节点的颜色
    if (nodeToReplace != nullptr) {
      nodeToReplace->color = nodeToDelete->color;
    } else {
      // 替换的节点是空节点, 所以损失的就是删除节点的颜色
      originalColor = nodeToDelete->color;
    }

    if (originalColor == Color::BLACK) {
      // 删除的是黑色节点才需要修复
      if (childOfReplaceNode != nullptr) {
        removeFixup(childOfReplaceNode);
      } else {
        // 被替换的是叶子节点, 所以childOfReplaceNode为空, 无法从其开始修复,
        // 需要使用哨兵节点替换
        Nil->parent = parentOfReplaceNode;
        if (parentOfReplaceNode != nullptr) {
          if (parentOfReplaceNode->left == nullptr) {
            parentOfReplaceNode->left = Nil;
          } else {
            parentOfReplaceNode->right = Nil;
          }
        }
        removeFixup(Nil);
        removeNil();
      }
    }

    delete nodeToDelete;
  }

public:
  // 构造函数
  RedBlackTree() : root(nullptr), size(0), Nil(new Node<Key>()) {
    Nil->color = Color::BLACK;
  }

  // 构造函数
  RedBlackTree(Node<Key> *_root, int _size)
      : root(_root), size(_size), Nil(new Node<Key>()) {
    Nil->color = Color::BLACK;
  }

  // 插入元素
  void insert(const Key &key) { insertNode(key); }

  // 删除元素
  void remove(const Key &key) {
    Node<Key> *nodeToBeRemoved = GetNode(key);
    if (nodeToBeRemoved != nullptr) {
      deleteNode(nodeToBeRemoved);
      size--;
    }
  }

  int blackHeight() {
    // 不包括空节点的黑色节点的高度
    int height = 0;
    Node<Key> *node = root;
    while (node != nullptr) {
      if (node->color == Color::BLACK) {
        height++;
      }
      node = node->left;
    }
    return height;
  }

  bool isBlackLenLegal() {
    // 判断黑色节点高度是否合法
    if (root == nullptr) {
      return true;
    } else {
      return root->getBlackHeight() != -1;
    }
  }

  bool isNoDoubleRed() {
    if (root == nullptr) {
      return true;
    }
    return root->isNoDoubleRed();
  }

  int getSizeByTranverse() {
    // 节点总数量
    if (root == nullptr) {
      return 0;
    }
    return root->getLen();
  }

  int len() { return size; }

  bool empty() { return size == 0; }

  bool isRootBlack() { return root == nullptr || root->color == Color::BLACK; }

  // 中序遍历打印
  void print() const {
    inorderTraversal(root);
    std::cout << std::endl;
  }

  void Print() { printTreeHelper(root, " "); }

  // 析构函数
  ~RedBlackTree() {
    // 释放节点内存
    deleteTree(root);
  }

private:
  // 递归释放节点内存
  void deleteTree(Node<Key> *node) {
    if (node) {
      deleteTree(node->left);
      deleteTree(node->right);
      delete node;
    }
  }
};
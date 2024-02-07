#pragma once

#include <memory>
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

// TrieNode 类定义了Trie树中的每一个节点
class TrieNode {
public:
  // 构造函数，用一个字符初始化节点
  explicit TrieNode(char key_char) {
    key_char_ = key_char;
    is_end_ = false;
    children_.clear();
  }

  // 移动构造函数
  TrieNode(TrieNode &&other_trie_node) noexcept {
    key_char_ = other_trie_node.key_char_;
    is_end_ = other_trie_node.is_end_;
    children_.swap(other_trie_node.children_);
  }

  // 检查当前节点是否有给定字符的子节点
  bool HasChild(char key_char) const {
    return children_.find(key_char) != children_.end();
  }

  // 检查当前节点是否有任何子节点
  bool HasChildren() const { return !children_.empty(); }

  // 检查当前节点是否为一个结束节点（即是否代表一个键的结束）
  bool IsEndNode() const { return is_end_; }

  // 获取当前节点存储的字符
  char GetKeyChar() const { return key_char_; }

  // 插入一个子节点
  std::unique_ptr<TrieNode> *
  InsertChildNode(char key_char, std::unique_ptr<TrieNode> &&child) {
    if (HasChild(key_char) || key_char != child->key_char_) {
      return nullptr;
    }
    children_[key_char] = std::forward<std::unique_ptr<TrieNode>>(child);
    return &children_[key_char];
  }

  // 获取一个子节点
  std::unique_ptr<TrieNode> *GetChildNode(char key_char) {
    auto node = children_.find(key_char);
    if (node != children_.end()) {
      return &(node->second);
    }
    return nullptr;
  }

  // 移除一个子节点
  void RemoveChildNode(char key_char) {
    auto node = children_.find(key_char);
    if (node != children_.end()) {
      children_.erase(key_char);
    }
  }

  // 设置当前节点为结束节点
  void SetEndNode(bool is_end) { is_end_ = is_end; }

  virtual ~TrieNode() = default;

protected:
  char key_char_;
  bool is_end_{false};
  // 子节点的映射表，键为字符，值为对应的TrieNode指针
  std::unordered_map<char, std::unique_ptr<TrieNode>> children_;
};

// TrieNodeWithValue 类继承自 TrieNode，并添加了值的存储功能
template <typename T> class TrieNodeWithValue : public TrieNode {
private:
  T value_; // 存储的值

public:
  // 构造函数，接受一个TrieNode和值
  TrieNodeWithValue(TrieNode &&trieNode, T value)
      : TrieNode(std::forward<TrieNode>(trieNode)) {
    value_ = value;
    SetEndNode(true);
  }

  // 构造函数，接受一个字符和值
  TrieNodeWithValue(char key_char, T value) : TrieNode(key_char) {
    value_ = value;
    SetEndNode(true);
  }

  // 默认析构函数
  ~TrieNodeWithValue() = default;

  // 获取存储的值
  T GetValue() const { return value_; }
};

// Trie 类定义了整个Trie树
class Trie {
private:
  std::unique_ptr<TrieNode> root_; // Trie树的根节点

public:
  // 构造函数，初始化根节点
  Trie() {
    auto *root = new TrieNode('\0');
    root_.reset(root);
  }

  // 插入键值对的模板函数
  template <typename T> bool Insert(const std::string &key, T value) {
    // 如果键为空，返回false
    if (key.empty()) {
      return false;
    }
    auto c = key.begin();
    auto pre_child = &root_;
    // 遍历键中的每个字符
    while (c != key.end()) {
      auto cur = c++;
      if (c == key.end()) {
        break;
      }

      // 如果前一个子节点没有当前字符的子节点，插入它
      if (!pre_child->get()->HasChild(*cur)) {
        pre_child = pre_child->get()->InsertChildNode(
            *cur, std::make_unique<TrieNode>(*cur));
      } else {
        pre_child = pre_child->get()->GetChildNode(*cur);
      }
    }

    c--;

    // 检查最后一个字符节点是否存在，如果是结束节点则返回false
    auto end_node = pre_child->get()->GetChildNode(*c);
    if (end_node != nullptr && end_node->get()->IsEndNode()) {
      return false;
    }

    // 如果最后一个节点存在，用新值更新它
    if (end_node != nullptr) {
      auto new_node = new TrieNodeWithValue<T>(std::move(**end_node), value);
      end_node->reset(new_node);
      return true;
    }

    // 如果最后一个节点不存在，创建它
    pre_child =
        pre_child->get()->InsertChildNode(*c, std::make_unique<TrieNode>(*c));
    auto new_node = new TrieNodeWithValue<T>(std::move(**pre_child), value);
    pre_child->reset(new_node);
    return true;
  }

  // 从Trie树中移除一个键
  bool Remove(const std::string &key) {
    // 如果键为空，返回false
    if (key.empty()) {
      return false;
    }

    // 使用栈来追踪移除过程中的路径
    std::stack<std::tuple<char, std::unique_ptr<TrieNode> *>> s;
    auto c = key.begin();
    auto pre_child = &root_;
    // 遍历键中的每个字符
    while (c != key.end()) {
      auto cur = c++;
      if (pre_child->get()->HasChild(*cur)) {
        s.push(std::make_tuple(*cur, pre_child));
        pre_child = pre_child->get()->GetChildNode(*cur);
        continue;
      }
      return false;
    }

    // 检查并移除没有子节点的节点
    while (!s.empty()) {
      auto t = s.top();
      s.pop();
      auto key = std::get<0>(t);
      auto node = std::get<1>(t);
      auto flag = (*node)->GetChildNode(key);
      if (flag != nullptr && (*flag)->HasChildren()) {
        continue;
      }
      (*node)->RemoveChildNode(key);
    }
    return true;
  }

  // 获取键对应的值
  template <typename T> T GetValue(const std::string &key, bool *success) {
    *success = false;

    auto pre_child = &root_;
    auto c = key.begin();
    // 遍历键中的每个字符
    while (c != key.end()) {
      auto cur = c++;
      auto next_node = pre_child->get()->GetChildNode(*cur);

      // 如果没有下一个节点，设置成功标志为false并退出
      if (!next_node) {
        *success = false;
        break;
      }

      // 如果是结束节点且已经到达键的最后，尝试获取值
      if (next_node->get()->IsEndNode() && c == key.end()) {
        auto flag_node = dynamic_cast<TrieNodeWithValue<T> *>(next_node->get());
        if (!flag_node) {
          *success = false;
          break;
        }
        *success = true;
        return flag_node->GetValue();
      }
      pre_child = next_node;
    }
    return {};
  }
};
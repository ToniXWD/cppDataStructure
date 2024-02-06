#pragma once

#include <memory>
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

class TrieNode {
public:
  explicit TrieNode(char key_char) {
    key_char_ = key_char;
    is_end_ = false;
    children_.clear();
  }

  TrieNode(TrieNode &&other_trie_node) noexcept {
    key_char_ = other_trie_node.key_char_;
    is_end_ = other_trie_node.is_end_;
    children_.swap(other_trie_node.children_);
  }

  bool HasChild(char key_char) const {
    return children_.find(key_char) != children_.end();
  }

  bool HasChildren() const { return !children_.empty(); }

  bool IsEndNode() const { return is_end_; }

  char GetKeyChar() const { return key_char_; }

  std::unique_ptr<TrieNode> *
  InsertChildNode(char key_char, std::unique_ptr<TrieNode> &&child) {
    if (HasChild(key_char) || key_char != child->key_char_) {
      return nullptr;
    }
    children_[key_char] = std::forward<std::unique_ptr<TrieNode>>(child);
    return &children_[key_char];
  }

  std::unique_ptr<TrieNode> *GetChildNode(char key_char) {
    auto node = children_.find(key_char);
    if (node != children_.end()) {
      return &(node->second);
    }
    return nullptr;
  }

  void RemoveChildNode(char key_char) {
    auto node = children_.find(key_char);
    if (node != children_.end()) {
      children_.erase(key_char);
    }
  }

  void SetEndNode(bool is_end) { is_end_ = is_end; }

protected:
  char key_char_;
  bool is_end_{false};
  std::unordered_map<char, std::unique_ptr<TrieNode>> children_;
};

template <typename T> class TrieNodeWithValue : public TrieNode {
private:
  T value_;

public:
  TrieNodeWithValue(TrieNode &&trieNode, T value)
      : TrieNode(std::forward<TrieNode>(trieNode)) {
    value_ = value;
    SetEndNode(true);
  }

  TrieNodeWithValue(char key_char, T value) : TrieNode(key_char) {
    value_ = value;
    SetEndNode(true);
  }

  ~TrieNodeWithValue() = default;

  T GetValue() const { return value_; }
};

class Trie {
private:
  std::unique_ptr<TrieNode> root_;

public:
  Trie() {
    auto *root = new TrieNode('\0');
    root_.reset(root);
  }

  template <typename T> bool Insert(const std::string &key, T value) {
    if (key.empty()) {
      return false;
    }
    auto c = key.begin();
    auto pre_child = &root_;
    while (c != key.end()) {
      auto cur = c++;
      if (c == key.end()) {
        break;
      }

      if (!pre_child->get()->HasChild(*cur)) {
        pre_child = pre_child->get()->InsertChildNode(
            *cur, std::make_unique<TrieNode>(*cur));
      } else {
        pre_child = pre_child->get()->GetChildNode(*cur);
      }
    }

    c--;

    auto end_node = pre_child->get()->GetChildNode(*c);
    if (end_node != nullptr && end_node->get()->IsEndNode()) {
      return false;
    }

    if (end_node != nullptr) {
      auto new_node = new TrieNodeWithValue<T>(std::move(**end_node), value);
      end_node->reset(new_node);
      return true;
    }

    pre_child =
        pre_child->get()->InsertChildNode(*c, std::make_unique<TrieNode>(*c));
    auto new_node = new TrieNodeWithValue<T>(std::move(**pre_child), value);
    pre_child->reset(new_node);
    return true;
  }

  bool Remove(const std::string &key) {
    if (key.empty()) {
      return false;
    }

    std::stack<std::tuple<char, std::unique_ptr<TrieNode> *>> s;
    auto c = key.begin();
    auto pre_child = &root_;
    while (c != key.end()) {
      auto cur = c++;
      if (pre_child->get()->HasChild(*cur)) {
        s.push(std::make_tuple(*cur, pre_child));
        pre_child = pre_child->get()->GetChildNode(*cur);
        continue;
      }
      return false;
    }

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

  template <typename T> T GetValue(const std::string &key, bool *success) {
    *success = false;

    auto pre_child = &root_;
    auto c = key.begin();
    while (c != key.end()) {
      auto cur = c++;
      auto next_node = pre_child->get()->GetChildNode(*cur);

      if (!next_node) {
        *success = false;
        break;
      }

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

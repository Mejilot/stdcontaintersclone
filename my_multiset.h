#ifndef CPP2_my_CONTAINERS_my_MULTISET_H_
#define CPP2_my_CONTAINERS_my_MULTISET_H_

#include "my_vector.h"
#include "tree.h"

namespace my {
template <class Key>
class Multiset : public Tree<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using size_type = size_t;

  using iterator = typename Tree<key_type>::iterator;
  using const_iterator = typename Tree<key_type>::ConstIterator;
  using data = typename Tree<value_type>::Data;

  Multiset() : Tree<key_type>::Tree() {}
  explicit Multiset(std::initializer_list<value_type> const& items)
      : Tree<key_type>::Tree() {
    typename std::initializer_list<value_type>::const_iterator i =
        items.begin();
    while (i != items.end()) {
      Insert(*i);
      ++i;
    }
  }
  Multiset(const Multiset& s) : Tree<value_type>() {
    iterator i = s.Begin();
    while (i != s.End()) {
      Insert(*i);
      ++i;
    }
  }
  Multiset(Multiset&& s) : Tree<key_type>::Tree(std::move(s)) {}
  ~Multiset() {}

  iterator Insert(const value_type& value) {
    if (this->Empty()) {
      this->InsertRoot(value);
      return iterator(this->root);
    }
    data* parent_node = this->root;
    while (parent_node->left || parent_node->right) {
      if (parent_node->key > value) {
        if (parent_node->left)
          parent_node = parent_node->left;
        else
          break;
      } else {
        if (parent_node->right && iterator(parent_node->right) != this->End())
          parent_node = parent_node->right;
        else
          break;
      }
    }
    return iterator(this->InsertData(value, parent_node));
  }

  void Merge(Tree<key_type>& other) {
    if (this->Empty()) {
      this->Swap(other);
    } else {
      iterator i = other.Begin();
      while (i != other.End()) this->MergeData(i++, other);
    }
  }

  size_type Count(const Key& key) {
    iterator i = this->Find(key);
    size_type n = 0;
    while (i != this->End() && *i == key) {
      ++i;
      ++n;
    }
    return n;
  }

  std::pair<iterator, iterator> EqualRange(const Key& key) {
    iterator i = this->Find(key);
    iterator j = this->Find(key);
    while (j != this->End() && *j == key) ++j;
    return std::pair<iterator, iterator>{i, j};
  }

  iterator LowerBound(const Key& key) { return this->Find(key); }

  iterator UpperBound(const Key& key) { return std::get<1>(EqualRange(key)); }

  template <class... Args>
  Vector<iterator> Emplace(Args&&... args) {
    Vector<iterator> v;
    const value_type data[] = {args...};
    for (const value_type item : data) v.PushBack(Insert(item));
    return v;
  }
};
}  // namespace my

#endif  // CPP2_my_CONTAINERS_MULTISET_H_

#ifndef CPP2_my_CONTAINERS_my_MAP_H_
#define CPP2_my_CONTAINERS_my_MAP_H_

#include <stdexcept>

#include "my_vector.h"
#include "tree.h"

namespace my {
template <class Key, class T>
class Map : public Tree<std::pair<const Key, T>> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename Tree<value_type>::iterator;
  using const_iterator = typename Tree<value_type>::ConstIterator;
  using size_type = size_t;

  using pair = std::pair<const key_type, mapped_type>;
  using data = typename Tree<value_type>::Data;

  Map() : Tree<value_type>::Tree() {}

  explicit Map(std::initializer_list<value_type> const& items)
      : Tree<value_type>::Tree() {
    typename std::initializer_list<value_type>::const_iterator i =
        items.begin();
    while (i != items.end()) {
      if (!(Contains(std::get<0>(*i)))) Insert(*i);
      ++i;
    }
  }

  Map(const Map& m) : Tree<value_type>::Tree() {
    iterator i = m.Begin();
    while (i != m.End()) {
      Insert(*i);
      ++i;
    }
  }
  Map(Map&& m) : Tree<value_type>::Tree(std::move(m)) {}
  ~Map() {}

  T& at(const Key& key) {
    data* n = FindNode(key);
    if (n == nullptr)
      throw std::out_of_range("There's no obj in Map with such key");
    return std::get<1>(n->key);
  }

  T& operator[](const Key& key) {
    data* n = FindNode(key);
    if (n)
      return std::get<1>(n->key);
    else
      return std::get<1>(*(std::get<0>(Insert(key, mapped_type()))));
  }

  std::pair<iterator, bool> Insert(const value_type& value) {
    if (this->Empty()) {
      this->InsertRoot(value);
      return std::pair<iterator, bool>{iterator(Tree<value_type>::root), true};
    }
    data* parent_node = Tree<value_type>::root;
    while ((parent_node->left || parent_node->right) ||
           std::get<0>(parent_node->key) == std::get<0>(value)) {
      if (std::get<0>(parent_node->key) > std::get<0>(value)) {
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
    bool not_equal_keys = std::get<0>(parent_node->key) != std::get<0>(value);
    return std::pair<iterator, bool>{
        iterator(InsertNode(value, not_equal_keys ? parent_node : nullptr)),
        not_equal_keys};
  }

  std::pair<iterator, bool> Insert(const Key& key, const T& obj) {
    return Insert(pair{key, obj});
  }

  std::pair<iterator, bool> InsertOrAssign(const Key& key, const T& obj) {
    data* n = FindNode(key);
    if (n) {
      iterator i(n);
      std::get<1>(*i) = obj;
      return std::pair<iterator, bool>{i, false};
    } else {
      return Insert(key, obj);
    }
  }

  void Merge(Map& other) {
    if (this->Empty()) {
      this->Swap(other);
    } else {
      iterator i = other.Begin();
      while (i != other.End()) {
        if (!(Contains(std::get<0>(*i)))) {
          MergeNode(i++, other);
        } else {
          ++i;
        }
      }
    }
  }

  bool Contains(const Key& key) const { return FindNode(key) != nullptr; }

  template <class... Args>
  Vector<std::pair<iterator, bool>> Emplace(Args&&... args) {
    Vector<std::pair<iterator, bool>> v;
    auto arguments = {args...};
    for (auto i = arguments.begin(), j = 0; i != arguments.end(); ++i, ++j) {
      v.PushBack(Insert(*i));
    }
    return v;
  }

 private:
  data* InsertNode(value_type k, data* p) {
    if (p) {
      data* n = new data(k, p);
      if (std::get<0>(k) < std::get<0>(p->key)) {
        p->left = n;
      } else {
        if (p->right) {
          n->right = p->right;
          p->right->parent = n;
        }
        p->right = n;
      }
      return n;
    }
    return nullptr;
  }

  void MergeNode(iterator i, Map& other) {
    data* n = other.FindNode(std::get<0>(*i));
    data* p = FindParent(n->key);
    other.RemoveData(n);
    n->parent = p;
    n->left = nullptr;
    n->right = nullptr;
    if (std::get<0>(n->key) < std::get<0>(p->key)) {
      p->left = n;
    } else {
      if (p->right) {
        p->right->parent = n;
        n->right = p->right;
      }
      p->right = n;
    }
  }

  data* FindNode(const Key& key) const {
    data* n = this->root;
    while (n && std::get<0>(n->key) != key) {
      if (key < std::get<0>(n->key)) {
        n = n->left;
      } else {
        n = n->right;
      }
    }
    return n;
  }

  data* FindParent(value_type key) const {
    data* p = this->root;
    while (p->left || (p->right && iterator(p->right) != this->End())) {
      if (std::get<0>(key) < std::get<0>(p->key) && p->left)
        p = p->left;
      else if (std::get<0>(key) > std::get<0>(p->key) && p->right)
        p = p->right;
      else
        break;
    }
    return p;
  }
};
}  // namespace my

#endif  // CPP2_my_CONTAINERS_MAP_H_

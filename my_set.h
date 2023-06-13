#ifndef CPP2_my_CONTAINERS_my_SET_H_
#define CPP2_my_CONTAINERS_my_SET_H_

#include "my_vector.h"
#include "tree.h"

namespace my {
template <class Key>
class Set : public Tree<Key> {
 public:
  using key_type = Key;
  using value_type = Key;

  using iterator = typename Tree<value_type>::iterator;
  using const_iterator = typename Tree<value_type>::ConstIterator;
  using node = typename Tree<value_type>::Data;

  Set() : Tree<value_type>::Tree() {}
  explicit Set(std::initializer_list<value_type> const& items)
      : Tree<value_type>::Tree() {
    typename std::initializer_list<value_type>::const_iterator i =
        items.begin();
    while (i != items.end()) {
      if (!(this->Contains(*i))) this->Insert(*i);
      ++i;
    }
  }
  Set(const Set& s) : Tree<value_type>::Tree(s) {}
  Set(Set&& s) : Tree<value_type>::Tree(std::move(s)) {}
  ~Set() {}

  void Merge(Set& other) {
    if (this->Empty()) {
      this->Swap(other);
    } else {
      iterator i = other.Begin();
      while (i != other.End()) {
        if (!(this->Contains(*i))) {
          this->MergeData(i++, other);
        } else {
          ++i;
        }
      }
    }
  }

  template <class... Args>
  Vector<std::pair<iterator, bool>> Emplace(Args&&... args) {
    Vector<std::pair<iterator, bool>> v;
    const value_type data[] = {args...};
    for (const value_type item : data) {
      v.PushBack(this->Insert(item));
    }
    return v;
  }
};
}  // namespace my

#endif  // CPP2_my_CONTAINERS_my_SET_H
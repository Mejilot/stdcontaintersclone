#ifndef CPP2_my_CONTAINERS_TREE_H_
#define CPP2_my_CONTAINERS_TREE_H_

#include <cstdint>
#include <limits>

namespace my {
template <class T>
class Tree {
 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  struct Data {
    value_type key;
    Data* parent;
    Data* left;
    Data* right;

    Data()
        : key(value_type()), parent(nullptr), left(nullptr), right(nullptr) {}
    explicit Data(value_type k, Data* p = nullptr)
        : key(value_type(k)), parent(p), left(nullptr), right(nullptr) {}
  };

  class iterator {
    friend class Tree;

   public:
    explicit iterator(Data* pointer = nullptr) : pointer_(pointer) {}

    reference operator*() { return pointer_->key; }

    iterator& operator++() {
      if (pointer_->right) {
        pointer_ = MinData();
      } else if (pointer_->parent && pointer_ == pointer_->parent->left) {
        pointer_ = pointer_->parent;
      } else if (pointer_->parent) {
        while (pointer_->parent->parent && pointer_ == pointer_->parent->right)
          pointer_ = pointer_->parent;
        pointer_ = pointer_->parent;
      }
      return *this;
    }

    iterator operator++(int) {
      iterator ret(pointer_);
      ++(*this);
      return ret;
    }

    iterator& operator--() {
      if (pointer_->left) {
        pointer_ = MaxData();
      } else if (pointer_->parent && pointer_->parent->left) {
        while (pointer_->parent->parent && pointer_ == pointer_->parent->left)
          pointer_ = pointer_->parent;
        pointer_ = pointer_->parent;
      } else if (pointer_->parent && pointer_->parent->right) {
        pointer_ = pointer_->parent;
      }
      return *this;
    }

    iterator operator--(int) {
      iterator ret(pointer_);
      --(*this);
      return ret;
    }

    bool operator==(const iterator& i) const { return pointer_ == i.pointer_; }
    bool operator!=(const iterator& i) const { return !(*this == i); }

    iterator& operator=(const iterator& i) {
      if (this == &i) return *this;
      pointer_ = i.pointer_;
      return *this;
    }

   private:
    Data* pointer_;

    Data* MinData() {
      Data* min = pointer_->right;
      while (min && min->left) min = min->left;
      return min;
    }

    Data* MaxData() {
      Data* max = pointer_->left;
      while (max && max->right) max = max->right;
      return max;
    }
  };

  class ConstIterator : public iterator {
    explicit ConstIterator(Data* pointer) : iterator(pointer) {}

    const_reference operator*() const {
      return static_cast<iterator*>(this)->operator*();
    }
  };

  Tree() : root(new Data()) {}
  Tree(const Tree& t) : Tree() {
    iterator i = t.Begin();
    while (i != t.End()) {
      Insert(*i);
      ++i;
    }
  }
  Tree(Tree&& t) : root(nullptr) { std::swap(root, t.root); }
  ~Tree() {
    if (root != nullptr) {
      Clear();
      delete root;
      root = nullptr;
    }
  }
  Tree& operator=(Tree&& t) {
    if (&t == this) return *this;
    if (!Empty()) {
      Clear();
      delete root;
    }
    root = nullptr;
    std::swap(root, t.root);
    return *this;
  }

  iterator Begin() const {
    Data* i = root;
    while (i->left) i = i->left;
    return iterator(i);
  }

  iterator End() const {
    Data* i = root;
    while (i->right) i = i->right;
    return iterator(i);
  }

  bool Empty() const { return Begin() == End(); }

  size_type Size() const {
    iterator i = Begin();
    size_type res = 0;
    while (i != End()) {
      ++i;
      ++res;
    }
    return res;
  }

  size_type MaxSize() const {
    return std::numeric_limits<intmax_t>::max() /
           (sizeof(Data) + sizeof(iterator));
  }

  void Clear() {
    while (!Empty()) {
      Erase(Begin());
    }
  }

  std::pair<iterator, bool> Insert(const value_type& value) {
    if (Empty()) {
      InsertRoot(value);
      return std::pair<iterator, bool>{iterator(this->root), true};
    }
    Data* parent_data = root;
    while ((parent_data->left || parent_data->right) ||
           parent_data->key == value) {
      if (parent_data->key > value) {
        if (parent_data->left)
          parent_data = parent_data->left;
        else
          break;
      } else {
        if (parent_data->right && iterator(parent_data->right) != this->End())
          parent_data = parent_data->right;
        else
          break;
      }
    }
    bool not_equal_keys = parent_data->key != value;
    return std::pair<iterator, bool>{
        iterator(
            this->InsertData(value, not_equal_keys ? parent_data : nullptr)),
        not_equal_keys};
  }

  void Erase(iterator pos) {
    Data* data = pos.pointer_;
    RemoveData(data);
    delete data;
  }

  void Swap(Tree& other) { std::swap(root, other.root); }

  iterator Find(const T& key) const {
    Data* data = FindData(key);
    return data ? iterator(data) : End();
  }

  bool Contains(const T& key) const { return Find(key) != End(); }

 protected:
  Data* root;

  void InsertRoot(const value_type& value) {
    Data* new_root = new Data(value, nullptr);
    new_root->right = root;
    root->parent = new_root;
    root = new_root;
  }

  Data* InsertData(value_type k, Data* p) {
    if (p) {
      Data* data = new Data(k, p);
      if (k < p->key) {
        p->left = data;
      } else {
        if (p->right) {
          data->right = p->right;
          p->right->parent = data;
        }
        p->right = data;
      }
      return data;
    }
    return nullptr;
  }

  void MergeData(iterator i, Tree& other) {
    Data* data = i.pointer_;
    Data* p = FindParent(data->key);
    other.RemoveData(data);
    data->parent = p;
    data->left = nullptr;
    data->right = nullptr;
    if (data->key < p->key) {
      p->left = data;
    } else {
      if (p->right) {
        p->right->parent = data;
        data->right = p->right;
      }
      p->right = data;
    }
  }

  void RemoveData(Data* data) {
    if (data->left && data->right) {
      RemoveTwoChildrenData(data);
    } else if (data->left || data->right) {
      RemoveOneChildData(data);
    } else {
      RemoveChildlessData(data);
    }
  }

 private:
  Data* FindData(const T& key) const {
    Data* data = root;
    while (data && data->key != key) {
      if (key < data->key) {
        data = data->left;
      } else {
        data = data->right;
      }
    }
    return data;
  }

  Data* FindParent(value_type key) const {
    Data* p = root;
    while (p->left || (p->right && iterator(p->right) != End())) {
      if (key < p->key && p->left)
        p = p->left;
      else if (key > p->key && p->right)
        p = p->right;
      else
        break;
    }
    return p;
  }

  void RemoveTwoChildrenData(Data* data) {
    Data* replacement = iterator(data->right) == End()
                            ? iterator(data).MaxData()
                            : iterator(data).MinData();
    if (replacement == data->right) {
      replacement->left = data->left;
    } else if (replacement == data->left) {
      replacement->right = data->right;
    } else if (replacement->right) {
      replacement->right->parent = replacement->parent;
      replacement->parent->left = replacement->right;
    } else if (replacement->left) {
      replacement->left->parent = replacement->parent;
      replacement->parent->right = replacement->left;
    } else {
      replacement->left = data->left;
      replacement->right = data->right;
      if (replacement == replacement->parent->left)
        replacement->parent->left = nullptr;
      else
        replacement->parent->right = nullptr;
    }
    if (replacement != data->right) {
      data->right->parent = replacement;
    }
    if (replacement != data->left) {
      data->left->parent = replacement;
    }
    if (data == root) {
      root = replacement;
      replacement->parent = nullptr;
    } else {
      if (data == data->parent->left)
        data->parent->left = replacement;
      else
        data->parent->right = replacement;
      replacement->parent = data->parent;
    }
  }

  void RemoveOneChildData(Data* data) {
    if (data == root) {
      root = data->left ? data->left : data->right;
    } else {
      if (data == data->parent->left) {
        if (data->left)
          data->parent->left = data->left;
        else
          data->parent->left = data->right;
      } else {
        if (data->left) {
          data->parent->right = data->left;
        } else {
          data->parent->right = data->right;
        }
      }
    }
    if (data->left) {
      data->left->parent = data->left == root ? nullptr : data->parent;
    } else {
      data->right->parent = data->right == root ? nullptr : data->parent;
    }
  }

  void RemoveChildlessData(Data* data) {
    if (data == data->parent->left)
      data->parent->left = nullptr;
    else
      data->parent->right = nullptr;
  }
};
}  // namespace my

#endif  // CPP2_my_CONTAINERS_TREE_H_

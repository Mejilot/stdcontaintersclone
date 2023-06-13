#ifndef CPP2_my_CONTAINERS_my_LIST_H_
#define CPP2_my_CONTAINERS_my_LIST_H_

#include <initializer_list>

namespace my {
template <typename T>
struct ListNode {
  T value;
  ListNode *next;
  ListNode *prev;
};

template <typename T>
class ListIterator {
 public:
  using value_type = T;
  using reference = T &;

  ListNode<T> *current_;

  explicit ListIterator(ListNode<T> *pit) : current_{pit} {}

  reference operator*() { return current_->value; }

  ListIterator<T> &operator++() {
    current_ = current_->next;
    return *this;
  }

  ListIterator<T> &operator--() {
    current_ = current_->prev;
    return *this;
  }

  ListIterator<T> operator++(int) {
    ListIterator<T> temp(current_);
    current_ = current_->next;
    return temp;
  }

  ListIterator<T> operator--(int) {
    ListIterator<T> temp(current_);
    current_ = current_->prev;
    return temp;
  }

  bool operator!=(const ListIterator<T> &other) {
    return current_ != other.current_;
  }

  bool operator==(const ListIterator<T> &other) {
    return current_ == other.current_;
  }
};

template <typename T>
class ListConstIterator {
 public:
  using value_type = T;
  using const_reference = const T &;
  const ListNode<T> *current_;

  explicit ListConstIterator(const ListNode<T> *pit) : current_{pit} {}

  ListConstIterator(ListIterator<T> other) : current_{other.current_} {}

  const_reference operator*() { return current_->value; }

  ListConstIterator<T> &operator++() {
    current_ = current_->next;
    return *this;
  }

  ListConstIterator<T> &operator--() {
    current_ = current_->prev;
    return *this;
  }

  ListConstIterator<T> operator++(int) {
    ListConstIterator<T> temp(current_);
    current_ = current_->next;
    return temp;
  }

  ListConstIterator<T> operator--(int) {
    ListConstIterator<T> temp(current_);
    current_ = current_->prev;
    return temp;
  }

  bool operator!=(const ListConstIterator<T> &other) {
    return current_ != other.current_;
  }

  bool operator==(const ListConstIterator<T> &other) {
    return current_ == other.current_;
  }

  ListIterator<T> ConstCast() {
    return ListIterator<T>(const_cast<ListNode<T> *>(current_));
  }
};

template <typename T>
class List {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = size_t;

  List() : size_{0} { Init(); }

  explicit List(size_type n) {
    Init();
    for (; n; --n) PushBackEmpty();
  }

  explicit List(std::initializer_list<T> const &items) {
    Init();
    for (auto &el : items) PushBack(el);
  }

  List(const List<T> &v) {
    Init();
    *this = v;
  }

  List(List<T> &&v) {
    Init();
    *this = std::move(v);
  }

  ~List() {
    Clear();
    alloc_.deallocate(end_, 1);
  }

  List<T> &operator=(const List<T> &v) {
    Clear();
    for (auto it = v.Begin(); it != v.End(); ++it) {
      PushBack(*it);
    }
    return *this;
  }

  List<T> &operator=(List<T> &&v) {
    Clear();
    std::swap(end_, v.end_);
    std::swap(size_, v.size_);
    return *this;
  }

  const_reference Front() { return end_->next->value; }

  const_reference Back() { return end_->prev->value; }

  iterator Begin() { return iterator(end_->next); }

  iterator End() { return iterator(end_); }

  const_iterator Begin() const { return const_iterator(end_->next); }

  const_iterator End() const { return const_iterator(end_); }

  bool Empty() { return size_ == 0; }

  size_type Size() { return size_; }

  size_type MaxSize() { return alloc_.max_size(); }

  void Clear() noexcept {
    while (size_) PopBack();
  }

  iterator Insert(iterator pos, const_reference value) {
    ListNode<T> *temp = alloc_.allocate(1);
    *temp = {const_cast<reference>(value), pos.current_, pos.current_->prev};
    pos.current_->prev->next = temp;
    pos.current_->prev = temp;
    ++size_;
    if (pos.current_ == end_) {
      end_->value = value;
    }
    return iterator(temp);
  }

  void Erase(iterator pos) {
    pos.current_->next->prev = pos.current_->prev;
    pos.current_->prev->next = pos.current_->next;
    --size_;
    alloc_.destroy(pos.current_);
    alloc_.deallocate(pos.current_, 1);
  }

  void PushBack(const_reference value) { Insert(End(), value); }

  void PopBack() { Erase(iterator(end_->prev)); }

  void PushFront(const_reference value) { Insert(Begin(), value); }

  void PopFront() { Erase(Begin()); }

  void Swap(List<T> &other) {
    std::swap(end_, other.end_);
    std::swap(size_, other.size_);
  }

  void Merge(List<T> &other) {
    if (this != &other) {
      auto first = Begin();
      auto second = other.Begin();
      while (first != End() && second != other.End()) {
        if (*first < *second) {
          ++first;
        } else {
          MoveNode(first, second++);
          --other.size_;
        }
      }
      while (second != other.End()) {
        MoveNode(first, second++);
        --other.size_;
      }
    }
  }

  void Splice(const_iterator pos, List<T> &other) {
    for (auto it = other.Begin(); it != other.End();) {
      MoveNode(pos.ConstCast(), it++);
      --other.size_;
    }
  }

  void Reverse() {
    end_->value = end_->prev->value;
    ListNode<T> *b = end_->next;
    std::swap(end_->next, end_->prev);
    while (b != end_) {
      std::swap(b->next, b->prev);
      b = b->prev;
    }
  }

  void Unique() {
    for (auto it = Begin(); it.current_->next != end_;) {
      if (*it == it.current_->next->value) {
        Erase(it++);
      } else {
        ++it;
      }
    }
  }

  void Sort() {
    if (size_ > 1) end_->next = MergeSort(end_->next);
    for (auto it = Begin(); it != End(); ++it) end_->prev = it.current_;
  }

  template <typename... Args>
  iterator Emplace(const_iterator pos, Args &&... args) {
    iterator res = pos.ConstCast();
    --res;
    auto arguments = {args...};
    for (auto i = arguments.begin(), j = pos.ConstCast(); i != arguments.end();
         ++i) {
      Insert(j, *i);
    }
    ++res;
    return res;
  }

  template <typename... Args>
  void EmplaceBack(Args &&... args) {
    auto arguments = {args...};
    for (auto i = arguments.begin(), j = End(); i != arguments.end(); ++i) {
      Insert(j, *i);
    }
  }

  template <typename... Args>
  void EmplaceFront(Args &&... args) {
    auto arguments = {args...};
    for (auto i = arguments.begin(), j = Begin(); i != arguments.end(); ++i) {
      Insert(j, *i);
    }
  }

 private:
  void PushBackEmpty() {
    ListNode<T> *temp = alloc_.allocate(1);
    alloc_.construct(temp);
    temp->next = end_;
    temp->prev = end_->prev;
    end_->prev->next = temp;
    end_->prev = temp;
    ++size_;
  }

  void MoveNode(iterator pos, iterator other) {
    ListNode<T> *temp = other.current_;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    temp->next = pos.current_;
    temp->prev = pos.current_->prev;
    pos.current_->prev->next = temp;
    pos.current_->prev = temp;
    ++size_;
    if (pos.current_ == end_) {
      end_->value = other.current_->value;
    }
  }

  ListNode<T> *MergeSort(ListNode<T> *head) {
    if (!head || !head->next || head == end_ || head->next == end_) return head;
    ListNode<T> *fast = head, *slow = head;
    while (fast && fast->next != end_ && fast->next &&
           fast->next->next != end_ && fast->next->next) {
      fast = fast->next->next;
      slow = slow->next;
    }
    ListNode<T> *second = slow->next;
    slow->next = end_;
    head = MergeSort(head);
    second = MergeSort(second);
    return Merge(head, second);
  }

  ListNode<T> *Merge(ListNode<T> *first, ListNode<T> *second) {
    if (!first || first == end_) return second;

    if (!second || second == end_) return first;

    if (first->value < second->value) {
      first->next = Merge(first->next, second);
      first->next->prev = first;
      first->prev = end_;
      return first;
    } else {
      second->next = Merge(first, second->next);
      second->next->prev = second;
      second->prev = end_;
      return second;
    }
  }

  void Init() {
    end_ = alloc_.allocate(1);
    end_->next = end_;
    end_->prev = end_;
  }

  size_type size_ = 0;
  ListNode<T> *end_;
  std::allocator<ListNode<T>> alloc_;
};
}  // namespace my

#endif  // CPP2_my_CONTAINERS_my_LIST_H_

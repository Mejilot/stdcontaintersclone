#ifndef CPP2_my_CONTAINERS_my_STACK_H_
#define CPP2_my_CONTAINERS_my_STACK_H_

#include <initializer_list>
#include <limits>

#include "my_list.h"

namespace my {
template <typename T>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Stack() : seq_() {}

  explicit Stack(std::initializer_list<value_type> const &items)
      : seq_(items) {}

  Stack(const Stack &s) : seq_(s.seq_) {}

  Stack(Stack &&s) : seq_(std::move(s.seq_)) {}

  ~Stack() { seq_.Clear(); }

  Stack<T> &operator=(const Stack &v) {
    seq_ = v.seq_;
    return *this;
  }

  Stack<T> &operator=(Stack &&v) {
    seq_ = std::move(v.seq_);
    return *this;
  }

  const_reference Top() { return seq_.Back(); }

  bool Empty() { return seq_.Size() == 0; }

  size_type Size() { return seq_.Size(); }

  void Push(const_reference value) { seq_.PushBack(value); }

  void Pop() {
    if (Size()) seq_.PopBack();
  }

  void Swap(Stack &other) { seq_.Swap(other.seq_); }

  template <typename... Args>
  void EmplaceFront(Args &&... args) {
    seq_.EmplaceFront(args...);
  }

 private:
  List<T> seq_;
};
}  // namespace my

#endif  // CPP2_my_CONTAINERS_my_STACK_H_

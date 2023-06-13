#ifndef CPP2_my_CONTAINERS_my_QUEUE_H_
#define CPP2_my_CONTAINERS_my_QUEUE_H_

#include <initializer_list>
#include <limits>

#include "my_list.h"

namespace my {
template <typename T>
class Queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Queue() : seq_() {}

  explicit Queue(std::initializer_list<value_type> const &items)
      : seq_(items) {}

  Queue(const Queue &q) : seq_(q.seq_) {}

  Queue(Queue &&q) : seq_(std::move(q.seq_)) {}

  ~Queue() { seq_.Clear(); }

  Queue<T> &operator=(const Queue &v) {
    seq_ = v.seq_;
    return *this;
  }

  Queue<T> &operator=(Queue &&v) {
    seq_ = std::move(v.seq_);
    return *this;
  }

  const_reference Front() { return seq_.Front(); }

  const_reference Back() { return seq_.Back(); }

  bool Empty() { return seq_.Size() == 0; }

  size_type Size() { return seq_.Size(); }

  void Push(const_reference value) { seq_.PushBack(value); }

  void Pop() {
    if (Size()) seq_.PopFront();
  }

  void Swap(Queue &other) { seq_.Swap(other.seq_); }

  template <typename... Args>
  void EmplaceBack(Args &&... args) {
    seq_.EmplaceBack(args...);
  }

 private:
  List<T> seq_;
};
}  // namespace my

#endif  // CPP2_my_CONTAINERS_my_QUEUE_H_

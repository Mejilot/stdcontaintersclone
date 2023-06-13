#ifndef CPP2_my_CONTAINERS_my_ARRAY_H_
#define CPP2_my_CONTAINERS_my_ARRAY_H_

#include <initializer_list>
#include <stdexcept>

namespace my {

template <typename T, size_t N>
class Array final {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Array() {}
  explicit Array(std::initializer_list<value_type> const &items) {
    if (N < items.size()) {
      throw std::runtime_error("Too many arguments!");
    }
    for (auto it = items.begin(), i = 0; it != items.end(); ++it, ++i) {
      array_[i] = *it;
    }
  }
  Array(const Array<T, N> &a) { std::copy(a.array_, a.array_ + N, array_); }
  Array(Array<T, N> &&a) { std::copy(a.array_, a.array_ + N, array_); }
  ~Array() {}
  Array<T, N> &operator=(const Array<T, N> &a) {
    if (this != &a) {
      std::copy(a.array_, a.array_ + N, array_);
    }
    return *this;
  }
  Array<T, N> &operator=(Array<T, N> &&a) {
    if (this != &a) {
      std::copy(a.array_, a.array_ + N, array_);
    }
    return *this;
  }

  reference At(size_type pos) {
    if (pos >= N) {
      throw std::runtime_error("Out of range!");
    }
    return array_[pos];
  }
  reference operator[](size_type pos) { return array_[pos]; }
  const_reference Front() const { return array_[0]; }
  const_reference Back() const { return array_[N - 1]; }
  iterator Data() { return array_; }

  iterator Begin() { return array_; }
  iterator End() { return array_ + N; }

  bool Empty() const { return N == 0 ? true : false; }
  size_type Size() const { return N; }
  size_type MaxSize() const { return N; }

  void Swap(Array<T, N> &other) {
    for (size_type i = 0; i < N; ++i) {
      value_type temp = array_[i];
      array_[i] = other.array_[i];
      other.array_[i] = temp;
    }
  }
  void Fill(const_reference value) {
    for (size_type i = 0; i < N; ++i) {
      array_[i] = value;
    }
  }

 private:
  value_type array_[N];
};

}  // namespace my

#endif  // CPP2_my_CONTAINERS_my_ARRAY_H_

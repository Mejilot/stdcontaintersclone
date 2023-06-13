#ifndef CPP2_my_CONTAINERS_my_VECTOR_H_
#define CPP2_my_CONTAINERS_my_VECTOR_H_

#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace my {
template <typename T>
class Vector final {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Vector() : size_{0}, capacity_{0}, array_{nullptr} {}
  explicit Vector(size_type n) {
    size_ = n;
    capacity_ = n;
    AllocateMemory(n);
    FillZero(n);
  }
  explicit Vector(std::initializer_list<value_type> const &items) {
    AllocateMemory(items.size());
    size_ = items.size();
    capacity_ = items.size();
    for (auto it = items.begin(), i = 0; it != items.end(); ++it, ++i) {
      array_[i] = *it;
    }
  }
  Vector(const Vector<T> &v) { CopyVectorObject(v); }
  Vector(Vector<T> &&v) : Vector<T>() { Swap(v); }
  ~Vector() { ClearMemory(); }
  Vector<T> &operator=(const Vector<T> &v) {
    if (array_ != v.array_) {
      ClearMemory();
      CopyVectorObject(v);
    }
    return *this;
  }
  Vector<T> &operator=(Vector<T> &&v) {
    if (array_ != v.array_) {
      ClearMemory();
      Swap(v);
    }
    return *this;
  }

  reference At(size_type pos) {
    if (pos >= size_) {
      throw std::runtime_error("Out of range!");
    }
    return array_[pos];
  }
  reference operator[](size_type pos) { return array_[pos]; }
  const_reference Front() const { return array_[0]; }
  const_reference Back() const { return array_[size_ - 1]; }
  iterator Data() { return array_; }

  iterator Begin() { return array_; }
  iterator End() { return array_ + size_; }

  bool Empty() const { return size_ == 0 ? true : false; }
  size_type Size() const { return size_; }
  size_type MaxSize() const {
    return std::numeric_limits<std::ptrdiff_t>().max() / sizeof(value_type);
  }
  void Reserve(size_type size) {
    if (size > capacity_) {
      if (size > MaxSize()) {
        throw std::runtime_error("Can't reserve that much!");
      }
      ReallocateAndCopyData(size);
    }
  }
  size_type Capacity() const { return capacity_; }
  void ShrinkToFit() { ReallocateAndCopyData(size_); }

  void Clear() {
    for (auto i = size_; i > 0; --i) {
      PopBack();
    }
  }
  iterator Insert(iterator pos, const_reference value) {
    size_type position = pos - array_;
    if (size_ >= capacity_) {
      Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    value_type temp_val = array_[position];
    ++size_;
    array_[position] = value;
    for (auto i = position + 1; i < size_; ++i) {
      value_type buffer = array_[i];
      array_[i] = temp_val;
      temp_val = buffer;
    }
    return (array_ + position);
  }
  void Erase(iterator pos) {
    size_type position = pos - array_;
    for (size_type i = 0, j = 0; i < size_; ++i, ++j) {
      if (i == position) {
        ++i;
      }
      array_[j] = array_[i];
    }
    --size_;
  }
  void PushBack(const_reference value) {
    if (size_ >= capacity_) {
      Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    array_[size_] = value;
    ++size_;
  }
  void PopBack() {
    array_[size_ - 1] = value_type();
    --size_;
  }
  void Swap(Vector<T> &other) {
    if (array_ != other.array_) {
      std::swap(size_, other.size_);
      std::swap(capacity_, other.capacity_);
      std::swap(array_, other.array_);
    }
  }

  template <typename... Args>
  iterator Emplace(const_iterator pos, Args &&... args) {
    size_type offset = pos - Begin();
    Reserve(size_ + sizeof...(args));
    iterator result = Begin() + offset;
    auto arguments = {args...};
    for (auto i = arguments.begin(), j = 0; i != arguments.end(); ++i, ++j) {
      Insert(result + j, *i);
    }
    return result;
  }
  template <typename... Args>
  void EmplaceBack(Args &&... args) {
    auto arguments = {args...};
    for (auto i = arguments.begin(); i != arguments.end(); ++i) {
      Insert(End(), *i);
    }
  }

 private:
  void AllocateMemory(const size_type n) { array_ = new T[n]; }
  void FillZero(const size_type n) {
    for (size_type i = 0; i < n; ++i) {
      array_[i] = 0;
    }
  }
  void ClearMemory() {
    delete[] array_;
    array_ = nullptr;
  }
  void CopyVectorObject(const Vector<T> &other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    AllocateMemory(capacity_);
    for (size_type i = 0; i < size_; ++i) {
      array_[i] = other.array_[i];
    }
  }
  void ReallocateAndCopyData(const size_type size) {
    iterator temp = new T[size];
    for (size_type i = 0; i < size_; ++i) {
      temp[i] = array_[i];
    }
    delete[] array_;
    array_ = temp;
    capacity_ = size;
  }

  size_type size_;
  size_type capacity_;
  value_type *array_;
};

}  // namespace my

#endif  // CPP2_my_CONTAINERS_my_VECTOR_H_

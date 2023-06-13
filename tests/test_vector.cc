#include <gtest/gtest.h>

#include <vector>

#include "../my_vector.h"

TEST(test_constructor_vector, t1) {
  std::vector<int> a;
  my::Vector<int> A;
  ASSERT_TRUE(a.size() == A.Size());
  ASSERT_TRUE(a.capacity() == A.Capacity());
  ASSERT_TRUE(a.data() == A.Data());
}

TEST(test_constructor_vector, t2) {
  std::vector<int> a(7);
  my::Vector<int> A(7);
  ASSERT_TRUE(a.size() == A.Size());
  ASSERT_TRUE(a.capacity() == A.Capacity());
  for (size_t i = 0; i < 7; ++i) {
    ASSERT_TRUE(a.at(i) == A.At(i));
  }
}

TEST(test_constructor_vector, t3) {
  std::vector<int> a({0, 1, 2, 3, 4});
  my::Vector<int> A({0, 1, 2, 3, 4});
  ASSERT_TRUE(a.size() == A.Size());
  ASSERT_TRUE(a.capacity() == A.Capacity());
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a.at(i) == A.At(i));
  }
}

TEST(test_constructor_vector, t4) {
  my::Vector<int> *a = new my::Vector<int>(5);
  my::Vector<int> b(*a);
  ASSERT_TRUE(a->Size() == b.Size());
  ASSERT_TRUE(a->Capacity() == b.Capacity());
  for (size_t i = 0; i < a->Size(); ++i) {
    ASSERT_TRUE(a->At(i) == b.At(i));
  }
  delete a;
}

TEST(test_constructor_vector, t5) {
  my::Vector<int> a(5);
  my::Vector<int> b(std::move(a));
  ASSERT_TRUE(b.Size() == 5);
  ASSERT_TRUE(b.Capacity() == 5);
  for (size_t i = 0; i < b.Size(); ++i) {
    ASSERT_TRUE(b.At(i) == 0);
  }
}

TEST(test_operators_vector, t1) {
  my::Vector<int> *a = new my::Vector<int>(5);
  my::Vector<int> b;
  b = *a;
  ASSERT_TRUE(a->Size() == b.Size());
  ASSERT_TRUE(a->Capacity() == b.Capacity());
  for (size_t i = 0; i < a->Size(); ++i) {
    ASSERT_TRUE(a->At(i) == b.At(i));
  }
  delete a;
}

TEST(test_operators_vector, t2) {
  my::Vector<int> a(5);
  my::Vector<int> b;
  b = std::move(a);
  ASSERT_TRUE(b.Size() == 5);
  ASSERT_TRUE(b.Capacity() == 5);
  for (size_t i = 0; i < b.Size(); ++i) {
    ASSERT_TRUE(b.At(i) == 0);
  }
}

TEST(test_operators_vector, t3) {
  std::vector<int> a({0, 1, 2, 3, 4});
  my::Vector<int> A({0, 1, 2, 3, 4});
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a[i] == A[i]);
  }
}

TEST(test_access_vector, t1) {
  std::vector<int> a({0, 1, 2, 3, 4});
  my::Vector<int> A({0, 1, 2, 3, 4});
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a.at(i) == A.At(i));
  }
  ASSERT_ANY_THROW(A.At(555));
}

TEST(test_access_vector, t2) {
  std::vector<int> a({666, 2});
  my::Vector<int> A({666, 4, 1, 7, 2, 9, 5});
  ASSERT_TRUE(a.front() == A.Front());
}

TEST(test_access_vector, t3) {
  std::vector<int> a({666, 2});
  my::Vector<int> A({666, 4, 1, 7, 2, 9, 5, 2});
  ASSERT_TRUE(a.back() == A.Back());
}

TEST(test_access_vector, t4) {
  std::vector<int> a({666, 2});
  my::Vector<int> A({666, 4, 1, 7, 2, 9, 5});
  ASSERT_TRUE(*a.data() == *A.Data());
}

TEST(test_iterator_vector, t1) {
  std::vector<int> a({666, 2});
  my::Vector<int> A({666, 4, 1, 7, 2, 9, 5});
  ASSERT_TRUE(*a.begin() == *A.Begin());
}

TEST(test_iterator_vector, t2) {
  std::vector<int> a({666, 2});
  my::Vector<int> A({666, 4, 1, 7, 2, 9, 2});
  ASSERT_TRUE(*(a.end() - 1) == *(A.End() - 1));
}

TEST(test_capacity_vector, t1) {
  std::vector<int> a({666, 2});
  my::Vector<int> A({666, 4, 1, 7, 2, 9, 5, 2});
  ASSERT_TRUE(a.empty() == A.Empty());
  std::vector<double> b;
  my::Vector<double> B;
  ASSERT_TRUE(b.empty() == B.Empty());
}

TEST(test_capacity_vector, t2) {
  std::vector<int> a({666, 2, 1, 1, 1, 1, 1, 1});
  my::Vector<int> A({666, 4, 1, 7, 2, 9, 5, 2});
  ASSERT_TRUE(a.size() == A.Size());
}

TEST(test_capacity_vector, t3) {
  std::vector<int> a;
  my::Vector<int> A;
  ASSERT_TRUE(a.max_size() == A.MaxSize());
  std::vector<double> b;
  my::Vector<double> B;
  ASSERT_TRUE(b.max_size() == B.MaxSize());
  std::vector<unsigned long long int> c;
  my::Vector<unsigned long long int> C;
  ASSERT_TRUE(c.max_size() == C.MaxSize());
}

TEST(test_capacity_vector, t4) {
  std::vector<int> a({666, 2, 1, 1, 1, 1, 1, 1});
  my::Vector<int> A({666, 4, 1, 7, 2, 9, 5, 2});
  ASSERT_TRUE(a.capacity() == A.Capacity());
  a.reserve(0);
  A.Reserve(0);
  ASSERT_TRUE(a.capacity() == A.Capacity());
  a.reserve(123);
  A.Reserve(123);
  ASSERT_TRUE(a.capacity() == A.Capacity());
}

TEST(test_capacity_vector, t5) {
  std::vector<int> a({666, 2, 1, 1, 1, 1, 1, 1});
  my::Vector<int> A({666, 4, 1, 7, 2, 9, 5, 2});
  ASSERT_TRUE(a.capacity() == A.Capacity());
  std::vector<double> b;
  my::Vector<double> B;
  ASSERT_TRUE(b.capacity() == B.Capacity());
}

TEST(test_capacity_vector, t6) {
  std::vector<int> a({666, 2, 1, 1, 1, 1, 1, 1});
  my::Vector<int> A({666, 4, 1, 7, 2, 9, 5, 2});
  a.reserve(21);
  A.Reserve(21);
  ASSERT_TRUE(a.capacity() == A.Capacity());
  a.shrink_to_fit();
  A.ShrinkToFit();
  ASSERT_TRUE(a.capacity() == A.Capacity());
}

TEST(test_modifiers_vector, t1) {
  std::vector<int> a({666, 2, 1, 1, 1, 1, 1, 1});
  my::Vector<int> A({666, 4, 1, 7, 2, 9, 5, 2});
  ASSERT_TRUE(a.capacity() == A.Capacity());
  ASSERT_TRUE(a.size() == A.Size());
  a.clear();
  A.Clear();
  ASSERT_TRUE(a.capacity() == A.Capacity());
  ASSERT_TRUE(a.size() == A.Size());
}

TEST(test_modifiers_vector, t2_1) {
  std::vector<int> a({21, 21, 21});
  my::Vector<int> A({21, 21, 21});
  ASSERT_TRUE(a.capacity() == A.Capacity());
  ASSERT_TRUE(a.size() == A.Size());
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a.at(i) == A.At(i));
  }
  int value = 5;
  a.insert(a.begin(), value);
  A.Insert(A.Begin(), value);
  ASSERT_TRUE(a.capacity() == A.Capacity());
  ASSERT_TRUE(a.size() == A.Size());
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a.at(i) == A.At(i));
  }
}

TEST(test_modifiers_vector, t2_2) {
  std::vector<int> a({21, 21, 21});
  my::Vector<int> A({21, 21, 21});
  ASSERT_TRUE(a.capacity() == A.Capacity());
  ASSERT_TRUE(a.size() == A.Size());
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a.at(i) == A.At(i));
  }
  int value = 5;
  a.insert(a.end(), value);
  A.Insert(A.End(), value);
  ASSERT_TRUE(a.capacity() == A.Capacity());
  ASSERT_TRUE(a.size() == A.Size());
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a.at(i) == A.At(i));
  }
}

TEST(test_modifiers_vector, t3) {
  std::vector<int> a({666, 21, 21});
  my::Vector<int> A({777, 21, 21});
  ASSERT_TRUE(a.capacity() == A.Capacity());
  ASSERT_TRUE(a.size() == A.Size());
  a.erase(a.begin());
  A.Erase(A.Begin());
  ASSERT_TRUE(a.capacity() == A.Capacity());
  ASSERT_TRUE(a.size() == A.Size());
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a.at(i) == A.At(i));
  }
}

TEST(test_modifiers_vector, t4) {
  std::vector<int> a({666, 21});
  my::Vector<int> A({666, 21});
  ASSERT_TRUE(a.capacity() == A.Capacity());
  ASSERT_TRUE(a.size() == A.Size());
  a.push_back(15);
  A.PushBack(15);
  ASSERT_TRUE(a.capacity() == A.Capacity());
  ASSERT_TRUE(a.size() == A.Size());
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a.at(i) == A.At(i));
  }
  a.push_back(638);
  A.PushBack(638);
  a.push_back(123);
  A.PushBack(123);
  ASSERT_TRUE(a.capacity() == A.Capacity());
  ASSERT_TRUE(a.size() == A.Size());
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a.at(i) == A.At(i));
  }
}

TEST(test_modifiers_vector, t5) {
  std::vector<int> a({666, 21, 19, 28, 716, 5});
  my::Vector<int> A({666, 21, 19, 28, 716, 5});
  ASSERT_TRUE(a.capacity() == A.Capacity());
  ASSERT_TRUE(a.size() == A.Size());
  a.pop_back();
  A.PopBack();
  ASSERT_TRUE(a.capacity() == A.Capacity());
  ASSERT_TRUE(a.size() == A.Size());
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a.at(i) == A.At(i));
  }
}

TEST(test_modifiers_vector, t6) {
  my::Vector<int> a({666, 21, 19, 28, 716, 5});
  my::Vector<int> b({666});
  my::Vector<int> c({666, 21, 19, 28, 716, 5});
  a.Swap(b);
  ASSERT_TRUE(b.Capacity() == c.Capacity());
  ASSERT_TRUE(b.Size() == c.Size());
  for (size_t i = 0; i < a.Size(); ++i) {
    ASSERT_TRUE(b.At(i) == c.At(i));
  }
}

TEST(test_emplace_vector, t1) {
  my::Vector<unsigned long long int> a({5, 6, 7, 8});
  a.Emplace(a.End(), 9, 10, 11, 12);
  ASSERT_TRUE(a.Capacity() == 8);
  ASSERT_TRUE(a.Size() == 8);
  a.Emplace(a.Begin(), 1, 2, 3, 4);
  ASSERT_TRUE(a.Capacity() == 12);
  ASSERT_TRUE(a.Size() == 12);
  for (size_t i = 0; i < a.Size(); ++i) {
    ASSERT_TRUE(a.At(i) == i + 1);
  }
}

TEST(test_emplace_vector, t2) {
  my::Vector<unsigned long long int> a({1, 2, 3, 4});
  a.EmplaceBack(5, 6, 7, 8);
  ASSERT_TRUE(a.Capacity() == 8);
  ASSERT_TRUE(a.Size() == 8);
  for (size_t i = 0; i < a.Size(); ++i) {
    ASSERT_TRUE(a.At(i) == i + 1);
  }
}

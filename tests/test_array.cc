#include <gtest/gtest.h>

#include <array>

#include "../my_array.h"

TEST(test_constructor_array, t1) {
  std::array<int, 5> a;
  my::Array<int, 5> A;
  ASSERT_TRUE(a.size() == A.Size());
}

TEST(test_constructor_array, t2) {
  std::array<int, 5> a({1, 2, 3, 4, 5});
  my::Array<int, 5> A({1, 2, 3, 4, 5});
  ASSERT_TRUE(a.size() == A.Size());
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a.at(i) == A.At(i));
  }
}

TEST(test_constructor_array, t3) {
  my::Array<int, 5> *a = new my::Array<int, 5>({1, 19, 4, 5, 6});
  my::Array<int, 5> b(*a);
  ASSERT_TRUE(a->Size() == b.Size());
  for (size_t i = 0; i < a->Size(); ++i) {
    ASSERT_TRUE(a->At(i) == b.At(i));
  }
  delete a;
}

TEST(test_constructor_array, t4) {
  my::Array<int, 5> a({61, 23, 32, 53, 74});
  my::Array<int, 5> c({61, 23, 32, 53, 74});
  my::Array<int, 5> b(std::move(a));
  ASSERT_TRUE(b.Size() == 5);
  for (size_t i = 0; i < b.Size(); ++i) {
    ASSERT_TRUE(b.At(i) == c.At(i));
  }
}

TEST(test_operators_array, t1) {
  my::Array<int, 5> *a = new my::Array<int, 5>({1, 19, 4, 5, 6});
  my::Array<int, 5> b;
  b = *a;
  ASSERT_TRUE(a->Size() == b.Size());
  for (size_t i = 0; i < a->Size(); ++i) {
    ASSERT_TRUE(a->At(i) == b.At(i));
  }
  delete a;
}

TEST(test_operators_array, t2) {
  my::Array<int, 5> a({1, 2, 3, 4, 5});
  my::Array<int, 5> b;
  b = std::move(a);
  ASSERT_TRUE(b.Size() == 5);
  for (size_t i = 0; i < b.Size(); ++i) {
    ASSERT_TRUE(b.At(i) == (int)(i + 1));
  }
}

TEST(test_operators_array, t3) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::Array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a[i] == A[i]);
  }
}

TEST(test_access_array, t1) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::Array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a.at(i) == A.At(i));
  }
  ASSERT_ANY_THROW(a.at(666));
}

TEST(test_access_array, t2) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::Array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_TRUE(a.front() == A.Front());
}

TEST(test_access_array, t3) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::Array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_TRUE(a.back() == A.Back());
}

TEST(test_access_array, t4) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::Array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_TRUE(*a.data() == *A.Data());
}

TEST(test_iterator_array, t1) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::Array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_TRUE(*a.begin() == *A.Begin());
}

TEST(test_iterator_array, t2) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::Array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_TRUE(*(a.end() - 1) == *(A.End() - 1));
}

TEST(test_capacity_array, t1) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::Array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_TRUE(a.empty() == A.Empty());
  std::array<int, 9> b;
  my::Array<int, 9> B;
  ASSERT_TRUE(b.empty() == B.Empty());
}

TEST(test_capacity_array, t2) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::Array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_TRUE(a.size() == A.Size());
  std::array<int, 15> b;
  my::Array<int, 15> B;
  ASSERT_TRUE(b.size() == B.Size());
}

TEST(test_capacity_array, t3) {
  std::array<int, 15> a;
  my::Array<int, 15> A;
  ASSERT_TRUE(a.max_size() == A.MaxSize());
  std::array<double, 6> b;
  my::Array<double, 6> B;
  ASSERT_TRUE(b.max_size() == B.MaxSize());
  std::array<std::array<int, 100>, 6> c;
  my::Array<std::array<int, 100>, 6> C;
  ASSERT_TRUE(c.max_size() == C.MaxSize());
}

TEST(test_modifiers_array, t1) {
  my::Array<int, 9> a({1, 2, 5, 5, 5, 5, 5, 5, 9});
  my::Array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::Array<int, 9> b({1, 2, 3, 4, 5, 6, 7, 8, 9});
  a.Swap(A);
  for (size_t i = 0; i < a.Size(); ++i) {
    ASSERT_TRUE(b.At(i) == a.At(i));
  }
}

TEST(test_modifiers_array, t2) {
  my::Array<int, 9> a({1, 2, 5, 5, 5, 5, 5, 5, 9});
  a.Fill(16);
  for (size_t i = 0; i < a.Size(); ++i) {
    ASSERT_TRUE(a.At(i) == 16);
  }
}

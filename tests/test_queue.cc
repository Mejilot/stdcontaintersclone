#include <gtest/gtest.h>

#include <queue>

#include "../my_queue.h"

TEST(queue_test_constructor, t1) {
  std::queue<int> a;
  my::Queue<int> A;
  ASSERT_TRUE(a.size() == A.Size());
}

TEST(queue_test_constructor, t2) {
  std::queue<int> a({1, 2, 3, 4, 6, 8, 666});
  my::Queue<int> A({1, 2, 3, 4, 6, 8, 666});
  ASSERT_TRUE(a.size() == A.Size());
  for (size_t i = a.size(); i > 0; --i) {
    ASSERT_TRUE(a.front() == A.Front());
    a.pop();
    A.Pop();
  }
}

TEST(queue_test_constructor, t3) {
  my::Queue<int> *a = new my::Queue<int>({16, 312, 2, 4, 6, 2});
  my::Queue<int> b(*a);
  ASSERT_TRUE(a->Size() == b.Size());
  delete a;
}

TEST(queue_test_constructor, t4) {
  my::Queue<int> a({16, 312, 2, 4, 6, 2});
  my::Queue<int> b(std::move(a));
  ASSERT_TRUE(b.Size() == 6);
}

TEST(queue_test_operators, t1) {
  my::Queue<int> *a = new my::Queue<int>({16, 312, 2, 4, 6, 2});
  my::Queue<int> b({9, 3, 2, 1});
  b = *a;
  ASSERT_TRUE(b.Size() == 6);
  for (size_t i = 0; i < a->Size(); ++i) {
    ASSERT_TRUE(a->Front() == b.Front());
    a->Pop();
    b.Pop();
  }
  delete a;
}

TEST(queue_test_operators, t2) {
  my::Queue<int> a({16, 312, 2, 4, 6, 2});
  my::Queue<int> b({9, 3, 2, 1});
  b = std::move(a);
  ASSERT_TRUE(b.Size() == 6);
}

TEST(queue_test_access, t1) {
  std::queue<int> a({15, 12, 3, 4, 5, 6, 7, 8});
  my::Queue<int> A({15, 13});
  ASSERT_TRUE(a.front() == A.Front());
}

TEST(queue_test_access, t2) {
  std::queue<int> a({15, 12, 3, 4, 5, 6, 7, 8});
  my::Queue<int> A({15, 8});
  ASSERT_TRUE(a.back() == A.Back());
}

TEST(queue_test_capacity, t1) {
  std::queue<int> a({15, 12, 3, 4, 5, 6, 7, 8});
  my::Queue<int> A({15, 13});
  ASSERT_TRUE(a.empty() == A.Empty());
  std::queue<int> b;
  my::Queue<int> B;
  ASSERT_TRUE(b.empty() == B.Empty());
}

TEST(queue_test_capacity, t2) {
  std::queue<int> a({15, 12, 3, 4, 5, 6, 7, 8});
  my::Queue<int> A({15, 12, 3, 4, 5, 6, 7, 8});
  ASSERT_TRUE(a.size() == A.Size());
  std::queue<int> b;
  my::Queue<int> B;
  ASSERT_TRUE(b.size() == B.Size());
}

TEST(queue_test_modifiers, t1) {
  std::queue<int> a;
  my::Queue<int> A;
  ASSERT_TRUE(a.size() == A.Size());
  a.push(15);
  A.Push(15);
  ASSERT_TRUE(a.size() == A.Size());
  a.push(52);
  A.Push(52);
  a.push(67899);
  A.Push(67899);
  a.push(7);
  A.Push(7);
  ASSERT_TRUE(a.size() == A.Size());
  for (size_t i = a.size(); i > 0; --i) {
    ASSERT_TRUE(a.front() == A.Front());
    a.pop();
    A.Pop();
  }
}

TEST(queue_test_modifiers, t2) {
  std::queue<int> a({15, 12, 3, 4, 5, 6, 7, 8});
  my::Queue<int> A({15, 12, 3, 4, 5, 6, 7, 8});
  ASSERT_TRUE(a.size() == A.Size());
  ASSERT_TRUE(a.front() == A.Front());
  a.pop();
  A.Pop();
  ASSERT_TRUE(a.front() == A.Front());
}

TEST(queue_test_modifiers, t3) {
  my::Queue<int> a({15, 12, 3, 4, 5, 6, 7, 8});
  my::Queue<int> b({666});
  my::Queue<int> c({15, 12, 3, 4, 5, 6, 7, 8});
  a.Swap(b);
  ASSERT_TRUE(b.Size() == c.Size());
  for (size_t i = b.Size(); i > 0; --i) {
    ASSERT_TRUE(b.Front() == c.Front());
    b.Pop();
    c.Pop();
  }
}

TEST(queue_test_emplace, t1) {
  my::Queue<int> a;
  my::Queue<int> c({15, 12, 3, 4, 5, 6, 7, 8});
  a.EmplaceBack(15, 12, 3, 4, 5, 6, 7, 8);
  ASSERT_TRUE(a.Size() == c.Size());
  for (size_t i = a.Size(); i > 0; --i) {
    ASSERT_TRUE(a.Front() == c.Front());
    a.Pop();
    c.Pop();
  }
}

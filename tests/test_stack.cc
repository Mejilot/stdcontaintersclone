#include <gtest/gtest.h>

#include <stack>

#include "../my_stack.h"

TEST(stack_test_constructors, t1) {
  std::stack<int> ss;
  my::Stack<int> ms;

  ASSERT_TRUE(ss.size() == ms.Size());
}

TEST(stack_test_constructors, t2) {
  std::stack<int> ss({1, 2, 3});
  my::Stack<int> ms({1, 2, 3});

  while (!ss.empty()) {
    ASSERT_TRUE(ss.top() == ms.Top());
    ss.pop();
    ms.Pop();
  }
}

TEST(stack_test_constructors, t3) {
  my::Stack<int> ms1({1, 2, 3});
  my::Stack<int> ms2(ms1);

  while (!ms1.Empty()) {
    ASSERT_TRUE(ms2.Top() == ms1.Top());
    ms1.Pop();
    ms2.Pop();
  }
}

TEST(stack_test_constructors, t4) {
  my::Stack<int> ms1({1, 2, 3});
  my::Stack<int> ms2({1, 2, 3});
  my::Stack<int> ms3(std::move(ms1));

  ASSERT_TRUE(ms1.Empty());
  ASSERT_TRUE(ms3.Size() == ms2.Size());

  while (!ms3.Empty()) {
    ASSERT_TRUE(ms2.Top() == ms3.Top());
    ms2.Pop();
    ms3.Pop();
  }
}

TEST(stack_test_copy_operator, t1) {
  my::Stack<int> ms1({1, 2, 3});
  my::Stack<int> ms2;

  ms2 = ms1;

  while (!ms1.Empty()) {
    ASSERT_TRUE(ms2.Top() == ms1.Top());
    ms1.Pop();
    ms2.Pop();
  }
}

TEST(stack_test_move_operator, t1) {
  my::Stack<int> ms1({1, 2, 3});
  my::Stack<int> ms2({1, 2, 3});
  my::Stack<int> ms3;

  ms3 = std::move(ms1);

  ASSERT_TRUE(ms1.Empty());
  ASSERT_TRUE(ms3.Size() == ms2.Size());

  while (!ms3.Empty()) {
    ASSERT_TRUE(ms2.Top() == ms3.Top());
    ms2.Pop();
    ms3.Pop();
  }
}

TEST(stack_test_top, t1) {
  my::Stack<int> ms({1, 2, 3});
  std::stack<int> ss({1, 2, 3});

  ASSERT_TRUE(ms.Top() == ss.top());
}

TEST(stack_test_top, t2) {
  my::Stack<int> ms({1, 1, 2, 3});
  std::stack<int> ss({1, 1, 2, 3});

  ASSERT_TRUE(ms.Top() == ss.top());
}

TEST(stack_test_empty, t1) {
  my::Stack<int> ms;
  std::stack<int> ss;

  ASSERT_TRUE(ms.Empty() == ss.empty());
}

TEST(stack_test_empty, t2) {
  my::Stack<int> ms({1});
  std::stack<int> ss({1});

  ASSERT_TRUE(ms.Empty() == ss.empty());
}

TEST(stack_test_size, t1) {
  my::Stack<int> ms;
  std::stack<int> ss;

  ASSERT_TRUE(ms.Size() == ss.size());
}

TEST(stack_test_size, t2) {
  my::Stack<int> ms({1, 2});
  std::stack<int> ss({1, 2});

  ASSERT_TRUE(ms.Size() == ss.size());
}

TEST(stack_test_size, t3) {
  my::Stack<int> ms({1, 2, 3, 4});
  std::stack<int> ss({1, 2, 3, 4});

  ASSERT_TRUE(ms.Size() == ss.size());
}

TEST(stack_test_push, t1) {
  my::Stack<int> ms;
  std::stack<int> ss;
  ms.Push(1);
  ss.push(1);
  ms.Push(2);
  ss.push(2);
  ms.Push(2);
  ss.push(2);

  ASSERT_TRUE(ms.Size() == ss.size());

  while (!ss.empty()) {
    ASSERT_TRUE(ss.top() == ms.Top());
    ss.pop();
    ms.Pop();
  }
}

TEST(stack_test_pop, t1) {
  my::Stack<int> ms;
  std::stack<int> ss;

  ms.Push(1);
  ss.push(1);
  ms.Pop();
  ss.pop();
  ms.Push(2);
  ss.push(2);
  ms.Push(2);
  ss.push(2);
  ms.Pop();
  ss.pop();

  ASSERT_TRUE(ms.Size() == ss.size());

  while (!ss.empty()) {
    ASSERT_TRUE(ss.top() == ms.Top());
    ss.pop();
    ms.Pop();
  }
}

TEST(stack_test_swap, t1) {
  my::Stack<int> ms1({1, 2, 3, 4});
  my::Stack<int> ms2({1, 2});
  std::stack<int> ss1({1, 2, 3, 4});
  std::stack<int> ss2({1, 2});

  ms1.Swap(ms2);
  ss1.swap(ss2);

  ASSERT_TRUE(ms1.Size() == ss1.size());
  ASSERT_TRUE(ms2.Size() == ss2.size());

  while (!ss1.empty()) {
    ASSERT_TRUE(ss1.top() == ms1.Top());
    ss1.pop();
    ms1.Pop();
  }
  while (!ss2.empty()) {
    ASSERT_TRUE(ss2.top() == ms2.Top());
    ss2.pop();
    ms2.Pop();
  }
}

TEST(stack_test_emplace_front, t1) {
  my::Stack<int> ms1({1, 2, 3, 4});
  my::Stack<int> ms2;

  ms2.EmplaceFront(1, 2, 3, 4);

  while (!ms1.Empty()) {
    ASSERT_TRUE(ms1.Top() == ms2.Top());
    ms1.Pop();
    ms2.Pop();
  }
}

#include <gtest/gtest.h>

#include <list>

#include "../my_list.h"

TEST(list_test_constructor, t1) {
  my::List<int> ml;
  std::list<int> sl;
  ASSERT_DOUBLE_EQ(ml.Size(), sl.size());
  ASSERT_EQ(ml.Empty(), sl.empty());
}

TEST(list_test_constructor, t2) {
  my::List<int> ml(2);
  std::list<int> sl(2);
  auto it1 = ml.Begin();
  auto it2 = sl.begin();
  for (; it2 != sl.end(); it2++, it1++) ASSERT_DOUBLE_EQ(*it1, *it2);
  std::list<double> u2(2);
  my::List<double> u1(2);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); ++it3, ++it4) ASSERT_DOUBLE_EQ(*it3, *it4);
}

TEST(list_test_constructor, t3) {
  std::list<double> u2;
  my::List<double> u1;
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
}

TEST(list_test_constructor, t4) {
  std::list<int> u2({1, 2, 3, 4});
  my::List<int> u1({1, 2, 3, 4});
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
}

TEST(list_test_constructor, t5) {
  std::list<int> u2({1, 2, 3, 4});
  my::List<int> u1({1, 2, 3, 4});
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
}

TEST(list_test_copy_constructor, t1) {
  my::List<int> u2({1, 2, 3, 4});
  my::List<int> u1(u2);
  auto it3 = u1.Begin();
  auto it4 = u2.Begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
}

TEST(list_test_copy_operator, t1) {
  my::List<int> u2({1, 2, 3, 4});
  my::List<int> u1 = u2;
  ASSERT_DOUBLE_EQ(u1.Size(), u2.Size());
  auto it3 = u1.Begin();
  auto it4 = u2.Begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
}

TEST(list_test_move_operator, t1) {
  my::List<int> u2({1, 2, 3, 4});
  my::List<int> u1(std::move(u2));
  std::list<int> u3({1, 2, 3, 4});
  ASSERT_DOUBLE_EQ(0, u2.Size());
  auto it3 = u1.Begin();
  auto it4 = u3.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
}

TEST(list_test_move_operator, t2) {
  my::List<int> u2({1, 2, 3, 4});
  my::List<int> u1 = std::move(u2);
  std::list<int> u3({1, 2, 3, 4});
  ASSERT_DOUBLE_EQ(0, u2.Size());
  auto it3 = u1.Begin();
  auto it4 = u3.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
}

TEST(list_test_front, t1) {
  my::List<int> u1({1, 2});
  std::list<int> u2({1, 2});
  ASSERT_DOUBLE_EQ(u1.Front(), u2.front());
}

TEST(list_test_front, t2) {
  my::List<int> u1({1, 2});
  my::List<int> u2 = u1;
  ASSERT_DOUBLE_EQ(u1.Front(), u2.Front());
}

TEST(list_test_back, t1) {
  my::List<int> u1({1, 2});
  std::list<int> u2({1, 2});
  ASSERT_DOUBLE_EQ(u1.Back(), u2.back());
}

TEST(list_test_size, t1) {
  my::List<int> u1({1, 2});
  std::list<int> u2({1, 2});
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_size, t2) {
  my::List<int> u1;
  std::list<int> u2;
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_size, t3) {
  my::List<int> u1(10);
  std::list<int> u2(10);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_max_size, t1) {
  my::List<int> u1({1, 2});
  std::list<int> u2({1, 2});
  ASSERT_DOUBLE_EQ(u1.MaxSize(), u2.max_size());
}

TEST(list_test_max_size, t2) {
  my::List<int> u1;
  std::list<int> u2;
  ASSERT_DOUBLE_EQ(u1.MaxSize(), u2.max_size());
}

TEST(list_test_max_size, t3) {
  my::List<int> u1(10);
  std::list<int> u2(10);
  ASSERT_DOUBLE_EQ(u1.MaxSize(), u2.max_size());
}

TEST(list_test_clear, t1) {
  my::List<int> u1({1, 2});
  std::list<int> u2({1, 2});
  u1.Clear();
  u2.clear();
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_clear, t2) {
  my::List<int> u1;
  std::list<int> u2;
  u1.Clear();
  u2.clear();
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_clear, t3) {
  my::List<int> u1(10);
  std::list<int> u2(10);
  u1.Clear();
  u2.clear();
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_insert, t1) {
  my::List<int> u1({1, 2});
  std::list<int> u2({1, 2});
  u1.Insert(u1.Begin(), 3);
  u2.insert(u2.begin(), 3);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_insert, t2) {
  my::List<int> u1({1, 2});
  std::list<int> u2({1, 2});
  u1.Insert(u1.End(), 3);
  u2.insert(u2.end(), 3);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_insert, t3) {
  my::List<int> u1;
  std::list<int> u2;
  u1.Insert(u1.Begin(), 3);
  u2.insert(u2.begin(), 3);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_insert, t4) {
  my::List<int> u1;
  std::list<int> u2;
  u1.Insert(u1.End(), 3);
  u2.insert(u2.end(), 3);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_insert, t5) {
  my::List<int> u1(5);
  std::list<int> u2(5);
  u1.Insert(u1.Begin(), 3);
  u2.insert(u2.begin(), 3);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_insert, t6) {
  my::List<int> u1(5);
  std::list<int> u2(5);
  u1.Insert(u1.End(), 3);
  u2.insert(u2.end(), 3);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_insert, t7) {
  my::List<int> u1(5);
  std::list<int> u2(5);
  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  it1++;
  it1++;
  advance(it2, 2);
  u1.Insert(it1, 3);
  u2.insert(it2, 3);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_insert, t8) {
  my::List<int> u1(5);
  std::list<int> u2(5);
  auto it1 = u1.End();
  auto it2 = u2.end();
  it1--;
  it1--;
  advance(it2, -2);
  u1.Insert(it1, 3);
  u2.insert(it2, 3);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_erase, t1) {
  my::List<int> u1({1, 2});
  std::list<int> u2({1, 2});
  u1.Erase(u1.Begin());
  u2.erase(u2.begin());
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_erase, t2) {
  my::List<int> u1(5);
  std::list<int> u2(5);
  u1.Erase(u1.Begin());
  u2.erase(u2.begin());
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_erase, t3) {
  my::List<int> u1(5);
  std::list<int> u2(5);
  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  it1++;
  it1++;
  advance(it2, 2);
  u1.Erase(it1);
  u2.erase(it2);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_erase, t4) {
  my::List<int> u1(5);
  std::list<int> u2(5);
  auto it1 = u1.End();
  auto it2 = u2.end();
  it1--;
  it1--;
  advance(it2, -2);
  u1.Erase(it1);
  u2.erase(it2);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_push_back, t1) {
  my::List<int> u1({1, 2});
  std::list<int> u2({1, 2});
  u1.PushBack(4);
  u2.push_back(4);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_push_back, t2) {
  my::List<int> u1;
  std::list<int> u2;
  u1.PushBack(4);
  u2.push_back(4);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_push_back, t3) {
  my::List<int> u1(5);
  std::list<int> u2(5);
  u1.PushBack(4);
  u2.push_back(4);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_pop_back, t1) {
  my::List<int> u1({1, 2});
  std::list<int> u2({1, 2});
  u1.PopBack();
  u2.pop_back();
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_pop_back, t2) {
  my::List<int> u1(5);
  std::list<int> u2(5);
  u1.PopBack();
  u2.pop_back();
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_push_front, t1) {
  my::List<int> u1({1, 2});
  std::list<int> u2({1, 2});
  u1.PushFront(4);
  u2.push_front(4);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_push_front, t2) {
  my::List<int> u1;
  std::list<int> u2;
  u1.PushFront(4);
  u2.push_front(4);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_push_front, t3) {
  my::List<int> u1(5);
  std::list<int> u2(5);
  u1.PushFront(4);
  u2.push_front(4);
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_pop_front, t1) {
  my::List<int> u1({1, 2});
  std::list<int> u2({1, 2});
  u1.PopFront();
  u2.pop_front();
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_pop_front, t2) {
  my::List<int> u1(5);
  std::list<int> u2(5);
  u1.PopFront();
  u2.pop_front();
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  for (; it3 != u1.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
}

TEST(list_test_swap, t1) {
  my::List<int> u1({2, 3, 5});
  my::List<int> u3(3);
  std::list<int> u2({2, 3, 5});
  std::list<int> u4(3);
  u1.Swap(u3);
  u2.swap(u4);
  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
  auto it3 = u3.Begin();
  auto it4 = u4.begin();
  for (; it3 != u3.End(); it3++, it4++) ASSERT_DOUBLE_EQ(*it3, *it4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
  ASSERT_DOUBLE_EQ(u3.Size(), u4.size());
}

TEST(list_test_merge, t1) {
  my::List<int> u1({1, 2, 3});
  my::List<int> u3({4, 5, 6});
  std::list<int> u2({1, 2, 3});
  std::list<int> u4({4, 5, 6});
  u1.Merge(u3);
  u2.merge(u4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
  ASSERT_DOUBLE_EQ(u3.Size(), u4.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_merge, t2) {
  my::List<int> u1({1, 7, 8});
  my::List<int> u3({4, 5, 6});
  std::list<int> u2({1, 7, 8});
  std::list<int> u4({4, 5, 6});
  u1.Merge(u3);
  u2.merge(u4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
  ASSERT_DOUBLE_EQ(u3.Size(), u4.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_merge, t3) {
  my::List<int> u1({7, 8});
  my::List<int> u3({4, 5, 6});
  std::list<int> u2({7, 8});
  std::list<int> u4({4, 5, 6});
  u1.Merge(u3);
  u2.merge(u4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
  ASSERT_DOUBLE_EQ(u3.Size(), u4.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_merge, t4) {
  my::List<int> u1({1, 7, 8});
  my::List<int> u3({4, 8, 9});
  std::list<int> u2({1, 7, 8});
  std::list<int> u4({4, 8, 9});
  u1.Merge(u3);
  u2.merge(u4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
  ASSERT_DOUBLE_EQ(u3.Size(), u4.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_merge, t5) {
  my::List<int> u1;
  my::List<int> u3({4, 8, 9});
  std::list<int> u2;
  std::list<int> u4({4, 8, 9});
  u1.Merge(u3);
  u2.merge(u4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
  ASSERT_DOUBLE_EQ(u3.Size(), u4.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_merge, t6) {
  my::List<int> u1({4, 8, 9});
  my::List<int> u3;
  std::list<int> u2({4, 8, 9});
  std::list<int> u4;
  u1.Merge(u3);
  u2.merge(u4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
  ASSERT_DOUBLE_EQ(u3.Size(), u4.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_merge, t7) {
  my::List<int> u1({5, 7, 8, 10});
  my::List<int> u3({4, 6, 8, 9, 11});
  std::list<int> u2({5, 7, 8, 10});
  std::list<int> u4({4, 6, 8, 9, 11});
  u1.Merge(u3);
  u2.merge(u4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
  ASSERT_DOUBLE_EQ(u3.Size(), u4.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_splice, t1) {
  my::List<int> u1({5, 7, 8, 10});
  my::List<int> u3({4, 6, 8, 9, 11});
  std::list<int> u2({5, 7, 8, 10});
  std::list<int> u4({4, 6, 8, 9, 11});
  u1.Splice(u1.Begin(), u3);
  u2.splice(u2.begin(), u4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
  ASSERT_DOUBLE_EQ(u3.Size(), u4.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_splice, t2) {
  my::List<int> u1({5, 7, 8, 10});
  my::List<int> u3({4, 6, 8, 9, 11});
  std::list<int> u2({5, 7, 8, 10});
  std::list<int> u4({4, 6, 8, 9, 11});
  u1.Splice(u1.End(), u3);
  u2.splice(u2.end(), u4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
  ASSERT_DOUBLE_EQ(u3.Size(), u4.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_splice, t3) {
  my::List<int> u1({5, 7, 8, 10});
  my::List<int> u3({4, 6, 8, 9, 11});
  std::list<int> u2({5, 7, 8, 10});
  std::list<int> u4({4, 6, 8, 9, 11});
  auto it3 = u1.Begin();
  auto it4 = u2.begin();
  it3++;
  it3++;
  advance(it4, 2);
  u1.Splice(it3, u3);
  u2.splice(it4, u4);
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());
  ASSERT_DOUBLE_EQ(u3.Size(), u4.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_reverse, t1) {
  my::List<int> u1({5, 7, 8, 10});
  std::list<int> u2({5, 7, 8, 10});
  u1.Reverse();
  u2.reverse();
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_reverse, t2) {
  my::List<int> u1;
  std::list<int> u2;
  u1.Reverse();
  u2.reverse();
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_reverse, t3) {
  my::List<int> u1(5);
  std::list<int> u2(5);
  u1.Reverse();
  u2.reverse();
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_unique, t1) {
  my::List<int> u1({1, 1, 1, 2, 3, 3, 2, 2, 5, 5, 66});
  std::list<int> u2({1, 1, 1, 2, 3, 3, 2, 2, 5, 5, 66});
  u1.Unique();
  u2.unique();
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); ++it1, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_unique, t2) {
  my::List<int> u1({1, 1, 1});
  std::list<int> u2({1, 1, 1});
  u1.Unique();
  u2.unique();
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); ++it1, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_unique, t3) {
  my::List<int> u1({1, 1, 1, 1});
  std::list<int> u2({1, 1, 1, 1});
  u1.Unique();
  u2.unique();
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_sort, t1) {
  my::List<int> u1({1, 1, 1, 1, 3});
  std::list<int> u2({1, 1, 1, 1, 3});
  u1.Sort();
  u2.sort();
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_sort, t2) {
  my::List<int> u1 = {};
  std::list<int> u2 = {};
  u1.Sort();
  u2.sort();
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_sort, t3) {
  my::List<int> u1({1});
  std::list<int> u2({1});
  u1.Sort();
  u2.sort();
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_sort, t4) {
  my::List<int> u1({2, 1, 3, 3, -5, -9, 0});
  std::list<int> u2({2, 1, 3, 3, -5, -9, 0});
  u1.Sort();
  u2.sort();
  ASSERT_DOUBLE_EQ(u1.Size(), u2.size());

  auto it1 = u1.Begin();
  auto it2 = u2.begin();
  for (; it1 != u1.End(); it1++, it2++) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_const_iterator, t1) {
  my::List<int> u1({1, 1, 1, 1, 3});
  std::list<int> u2({1, 1, 1, 1, 3});

  my::List<int>::const_iterator it1 = u1.Begin();
  std::list<int>::const_iterator it2 = u2.begin();
  for (; it1 != u1.End(); ++it1, ++it2) ASSERT_DOUBLE_EQ(*it1, *it2);
  for (; it1 != u1.End(); ++it1, ++it2) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_const_iterator, t2) {
  my::List<int> u1({1, 1, 1, 1, 3});
  std::list<int> u2({1, 1, 1, 1, 3});

  my::List<int>::const_iterator it1 = u1.Begin();
  std::list<int>::const_iterator it2 = u2.begin();
  ++it1;
  ++it2;
  for (; it1 != u1.Begin(); --it1, --it2) ASSERT_DOUBLE_EQ(*it1, *it2);
  for (; it1 != u1.Begin(); --it1, --it2) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_iterator, t1) {
  my::List<int> u1({1, 1, 1, 1, 3});
  std::list<int> u2({1, 1, 1, 1, 3});

  my::List<int>::iterator it1 = u1.Begin();
  std::list<int>::iterator it2 = u2.begin();
  for (; it1 != u1.End(); ++it1, ++it2) ASSERT_DOUBLE_EQ(*it1, *it2);
  for (; it1 != u1.End(); ++it1, ++it2) ASSERT_DOUBLE_EQ(*it1, *it2);

  my::List<int>::iterator it3 = u1.End();
  std::list<int>::iterator it4 = u2.end();
  for (; it3 != u1.End(); --it3, --it4) ASSERT_DOUBLE_EQ(*it3, *it4);
  for (; it3 != u1.End(); --it3, --it4) ASSERT_DOUBLE_EQ(*it3, *it4);
}

TEST(list_test_emplace, t1) {
  my::List<int> u1;
  std::list<int> u2;

  u1.Emplace(u1.Begin(), 2);
  u2.emplace(u2.begin(), 2);

  my::List<int>::const_iterator it1 = u1.Begin();
  std::list<int>::const_iterator it2 = u2.begin();

  for (; it1 != u1.End(); ++it1, ++it2) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_emplace, t2) {
  my::List<int> u1({0, 1, 2, 3, 4});
  my::List<int> u2({0, 4});

  auto it = u2.Begin();
  ++it;

  u2.Emplace(it, 1, 2, 3);

  my::List<int>::const_iterator it1 = u1.Begin();
  my::List<int>::const_iterator it2 = u2.Begin();

  for (; it1 != u1.End(); ++it1, ++it2) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_emplace, t3) {
  my::List<int> u1({0, 1, 2, 3, 4});
  my::List<int> u2;

  u2.Emplace(u2.Begin(), 0, 1, 2, 3, 4);

  my::List<int>::const_iterator it1 = u1.Begin();
  my::List<int>::const_iterator it2 = u2.Begin();

  for (; it1 != u1.End(); ++it1, ++it2) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_emplace, t4) {
  my::List<int> u1({0, 1, 2, 3, 4});
  my::List<int> u2;

  u2.Emplace(u2.End(), 0, 1, 2, 3, 4);

  my::List<int>::const_iterator it1 = u1.Begin();
  my::List<int>::const_iterator it2 = u2.Begin();

  for (; it1 != u1.End(); ++it1, ++it2) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_emplace, t5) {
  my::List<int> u1({-1, 0, 1, 2, 3, 4});
  my::List<int> u2({-1});

  u2.Emplace(u2.End(), 0, 1, 2, 3, 4);

  my::List<int>::const_iterator it1 = u1.Begin();
  my::List<int>::const_iterator it2 = u2.Begin();

  for (; it1 != u1.End(); ++it1, ++it2) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_emplace_back, t1) {
  my::List<int> u1;
  std::list<int> u2;

  u1.EmplaceBack(2);
  u2.emplace_back(2);

  my::List<int>::const_iterator it1 = u1.Begin();
  std::list<int>::const_iterator it2 = u2.begin();

  for (; it1 != u1.End(); ++it1, ++it2) ASSERT_DOUBLE_EQ(*it1, *it2);
}

TEST(list_test_emplace_front, t1) {
  my::List<int> u1;
  std::list<int> u2;

  u1.EmplaceFront(1);
  u2.emplace_front(1);

  my::List<int>::const_iterator it1 = u1.Begin();
  std::list<int>::const_iterator it2 = u2.begin();

  for (; it1 != u1.End(); ++it1, ++it2) ASSERT_DOUBLE_EQ(*it1, *it2);
}

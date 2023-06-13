#include <gtest/gtest.h>

#include <set>

#include "../my_set.h"

class SetTest : public ::testing::Test {
 protected:
  my::Set<int> set{8,  20,  -14, -18, 1, -18, -8,  -20, -14, -12, -9,
                    15, -19, -17, -3,  7, 4,   -12, -17, -14, -20};
  std::set<int> std_set{8,  20,  -14, -18, 1, -18, -8,  -20, -14, -12, -9,
                        15, -19, -17, -3,  7, 4,   -12, -17, -14, -20};
  void eq_set(my::Set<int> set, std::set<int> std_set);
};

void SetTest::eq_set(my::Set<int> set, std::set<int> std_set) {
  EXPECT_EQ(set.Size(), std_set.size());
  my::Set<int>::iterator i1 = set.Begin();
  std::set<int>::iterator i2 = std_set.begin();
  while (i2 != std_set.end()) {
    EXPECT_EQ(*i1, *i2);
    ++i1;
    ++i2;
  }
  i1 = --(set.End());
  i2 = --(std_set.end());
  while (i2 != std_set.begin()) {
    EXPECT_EQ(*i1, *i2);
    --i1;
    --i2;
  }
  EXPECT_EQ(*i1, *i2);
}

TEST(set, default_constructor_empty) {
  my::Set<int> set;
  EXPECT_TRUE(set.Empty());
}

TEST_F(SetTest, init_constructor_insert) { eq_set(set, std_set); }

TEST_F(SetTest, copy_constructor) {
  my::Set<int> Copy(set);
  eq_set(Copy, std_set);
}

TEST_F(SetTest, move_constructor_assignment) {
  my::Set<int> Move1(std::move(set));
  eq_set(Move1, std_set);
  my::Set<int> Move2 = std::move(Move1);
  eq_set(Move2, std_set);
}

TEST_F(SetTest, max_size) { EXPECT_EQ(set.MaxSize(), std_set.max_size()); }

TEST_F(SetTest, clear) {
  set.Clear();
  EXPECT_TRUE(set.Empty());
}

TEST_F(SetTest, erase) {
  set.Erase(set.Begin());
  std_set.erase(std_set.begin());
  set.Erase(++set.Begin());
  std_set.erase(++(std_set.begin()));
  set.Erase(--set.End());
  std_set.erase(--(std_set.end()));
  eq_set(set, std_set);
}

TEST_F(SetTest, swap) {
  my::Set<int> empty;
  std::set<int> std_empty;
  set.Swap(empty);
  std_set.swap(std_empty);
  eq_set(empty, std_empty);
  EXPECT_TRUE(set.Empty());
}

TEST_F(SetTest, merge) {
  std::initializer_list<int> init = {14, 8, 13, 15, 6, 7, 13, 9, 16, 8};
  my::Set<int> set2(init);
  std::set<int> std_set2(init);
  set.Merge(set2);
  std_set.merge(std_set2);
  eq_set(set, std_set);
  eq_set(set2, std_set2);
  my::Set<int> set3;
  std::set<int> std_set3;
  set3.Merge(set2);
  std_set3.merge(std_set2);
  eq_set(set3, std_set3);
  EXPECT_EQ(set2.Empty(), std_set2.empty());
}

TEST_F(SetTest, find) {
  my::Set<int>::iterator i = set.Find(10);
  EXPECT_EQ(i, set.End());
  i = set.Find(20);
  EXPECT_EQ(i, --(set.End()));
  i = set.Find(-20);
  EXPECT_EQ(i, set.Begin());
  i = set.Find(-19);
  EXPECT_EQ(i, (++(set.Begin())));
}

TEST_F(SetTest, contains) {
  EXPECT_TRUE(set.Contains(8));
  EXPECT_TRUE(set.Contains(-18));
  EXPECT_TRUE(set.Contains(15));
  EXPECT_FALSE(set.Contains(10));
}

TEST_F(SetTest, emplace) {
  set.Emplace(0, 1, 2, 3, 4);
  for (int i = 0; i < 5; ++i) std_set.insert(i);
  eq_set(set, std_set);
}

#include <gtest/gtest.h>

#include <set>

#include "../my_multiset.h"

class MultisetTest : public ::testing::Test {
 protected:
  my::Multiset<int> multiset{8,  20,  -14, -18, 1, -18, -8,  -20, -14, -12, -9,
                              15, -19, -17, -3,  7, 4,   -12, -17, -14, -20};
  std::multiset<int> std_multiset{8,   20,  -14, -18, 1,   -18, -8,
                                  -20, -14, -12, -9,  15,  -19, -17,
                                  -3,  7,   4,   -12, -17, -14, -20};
  void eq_set(my::Multiset<int> multiset, std::multiset<int> std_multiset);
};

void MultisetTest::eq_set(my::Multiset<int> multiset,
                          std::multiset<int> std_multiset) {
  EXPECT_EQ(multiset.Size(), std_multiset.size());
  my::Multiset<int>::iterator i1 = multiset.Begin();
  std::multiset<int>::iterator i2 = std_multiset.begin();
  while (i2 != std_multiset.end()) {
    EXPECT_EQ(*i1, *i2);
    ++i1;
    ++i2;
  }
  i1 = --(multiset.End());
  i2 = --(std_multiset.end());
  while (i2 != std_multiset.begin()) {
    EXPECT_EQ(*i1, *i2);
    --i1;
    --i2;
  }
  EXPECT_EQ(*i1, *i2);
}

TEST(Multiset, default_constructor_empty) {
  my::Multiset<int> multiset;
  EXPECT_TRUE(multiset.Empty());
}

TEST_F(MultisetTest, init_constructor_insert) {
  eq_set(multiset, std_multiset);
}

TEST_F(MultisetTest, copy_constructor) {
  my::Multiset<int> copy(multiset);
  eq_set(copy, std_multiset);
}

TEST_F(MultisetTest, move_constructor_assignment) {
  my::Multiset<int> move1(std::move(multiset));
  eq_set(move1, std_multiset);
  my::Multiset<int> move2 = std::move(move1);
  eq_set(move2, std_multiset);
}

TEST_F(MultisetTest, max_size) {
  EXPECT_EQ(multiset.MaxSize(), std_multiset.max_size());
}

TEST_F(MultisetTest, clear) {
  multiset.Clear();
  EXPECT_TRUE(multiset.Empty());
}

TEST_F(MultisetTest, erase) {
  multiset.Erase(multiset.Begin());
  std_multiset.erase(std_multiset.begin());
  multiset.Erase(++multiset.Begin());
  std_multiset.erase(++(std_multiset.begin()));
  multiset.Erase(--multiset.End());
  std_multiset.erase(--(std_multiset.end()));
  eq_set(multiset, std_multiset);
}

TEST_F(MultisetTest, swap) {
  my::Multiset<int> empty;
  std::multiset<int> std_empty;
  multiset.Swap(empty);
  std_multiset.swap(std_empty);
  eq_set(empty, std_empty);
  EXPECT_TRUE(multiset.Empty());
}

TEST_F(MultisetTest, merge) {
  std::initializer_list<int> init = {14, 8, 13, 15, 6, 7, 13, 9, 16, 8};
  my::Multiset<int> multiset2(init);
  std::multiset<int> std_multiset2(init);
  multiset.Merge(multiset2);
  std_multiset.merge(std_multiset2);
  eq_set(multiset, std_multiset);
  EXPECT_EQ(multiset2.Empty(), std_multiset2.empty());
  multiset2.Merge(multiset);
  std_multiset2.merge(std_multiset);
  eq_set(multiset2, std_multiset2);
  EXPECT_EQ(multiset.Empty(), std_multiset.empty());
}

TEST_F(MultisetTest, count) {
  EXPECT_EQ(multiset.Count(-14), std_multiset.count(-14));
}

TEST_F(MultisetTest, find) {
  my::Multiset<int>::iterator i = multiset.Find(10);
  EXPECT_EQ(i, multiset.End());
  i = multiset.Find(20);
  EXPECT_EQ(i, --(multiset.End()));
  i = multiset.Find(-20);
  EXPECT_EQ(i, multiset.Begin());
  i = multiset.Find(-19);

  my::Multiset<int>::iterator test = ++multiset.Begin();
  ++test;
  EXPECT_EQ(i, test);
}

TEST_F(MultisetTest, contains) {
  EXPECT_TRUE(multiset.Contains(8));
  EXPECT_TRUE(multiset.Contains(-18));
  EXPECT_TRUE(multiset.Contains(15));
  EXPECT_FALSE(multiset.Contains(10));
}

TEST_F(MultisetTest, equal_range_bound) {
  my::Multiset<int>::iterator i1 = multiset.Find(-14);
  my::Multiset<int>::iterator i2 = multiset.Find(-12);
  std::pair<my::Multiset<int>::iterator, my::Multiset<int>::iterator> pair =
      multiset.EqualRange(-14);
  EXPECT_EQ(i1, std::get<0>(pair));
  EXPECT_EQ(i2, std::get<1>(pair));
  my::Multiset<int>::iterator low = multiset.LowerBound(-14);
  my::Multiset<int>::iterator up = multiset.UpperBound(-14);
  EXPECT_EQ(i1, low);
  EXPECT_EQ(i2, up);
}

TEST_F(MultisetTest, emplace) {
  multiset.Emplace(0, 1, 2, 3, 4);
  for (int i = 0; i < 5; ++i) std_multiset.insert(i);
  eq_set(multiset, std_multiset);
}

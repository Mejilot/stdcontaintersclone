#include <gtest/gtest.h>

#include <map>

#include "../my_map.h"

class MapTest : public ::testing::Test {
 protected:
  std::pair<int, std::string> p1{3, "ab"};
  std::pair<int, std::string> p2{-1, "abc"};
  std::pair<int, std::string> p3{1, "abcd"};
  std::pair<int, std::string> p4{2, "abcde"};
  std::pair<int, std::string> p5{11, "abcef"};
  std::pair<int, std::string> p6{7, "abcdefg"};
  std::pair<int, std::string> p7{-16, "abcdefgh"};
  std::pair<int, std::string> p8{-12, "abcdefghi"};
  std::pair<int, std::string> p9{-8, "abcdefghij"};
  std::pair<int, std::string> p10{5, "abcdefghijk"};
  std::pair<int, std::string> p11{-15, "abcdefghijkl"};
  std::pair<int, std::string> p12{12, "abcdefghijklm"};
  std::pair<int, std::string> p13{-2, "abcdefghijklmn"};
  std::pair<int, std::string> p14{-17, "abcdefghijklmno"};
  std::pair<int, std::string> p15{14, "abcdefghijklmnop"};
  std::pair<int, std::string> p16{-4, "abcdefghijklmnopq"};
  std::pair<int, std::string> p17{-5, "abcdefghijklmnopqr"};
  std::pair<int, std::string> p18{-1, "abcdefghijklmnopqrs"};
  std::pair<int, std::string> p19{-7, "abcdefghijklmnopqrst"};
  std::pair<int, std::string> p20{-15, "abcdefghijklmnopqrstu"};
  std::pair<int, std::string> p21{15, "abcdefghijklmnopqrstuv"};
  std::pair<int, std::string> p22{13, "abcdefghijklmnopqrstuvw"};
  std::pair<int, std::string> p23{2, "abcdefghijklmnopqrstuvwx"};
  std::pair<int, std::string> p24{10, "abcdefghijklmnopqrstuvwxy"};
  std::pair<int, std::string> p25{7, "abcdefghijklmnopqrstuvwxyz"};
  std::pair<int, std::string> p26{-13, "abcdefghijklmnopqrstuvwxyz1"};
  std::pair<int, std::string> p27{1, "abcdefghijklmnopqrstuvwxyz12"};
  std::pair<int, std::string> p28{-11, "abcdefghijklmnopqrstuvwxyz123"};
  std::pair<int, std::string> p29{-11, "abcdefghijklmnopqrstuvwxyz1234"};
  std::pair<int, std::string> p30{-8, "abcdefghijklmnopqrstuvwxyz12345"};
  std::pair<int, std::string> p31{-3, "abcdefghijklmnopqrstuvwxyz123456"};
  std::pair<int, std::string> p32{-16, "abcdefghijklmnopqrstuvwxyz1234567"};
  std::pair<int, std::string> p33{12, "abcdefghijklmnopqrstuvwxyz12345678"};
  std::pair<int, std::string> p34{15, "abcdefghijklmnopqrstuvwxyz123456789"};
  std::pair<int, std::string> p35{7, "abcdefghijklmnopqrstuvwxyz1234567890"};
  std::pair<int, std::string> p36{-10, "abcdefghijklmnopqrstuvwxyz12345678901"};
  std::pair<int, std::string> p37{-11,
                                  "abcdefghijklmnopqrstuvwxyz123456789012"};
  my::Map<int, std::string> map{
      p1,  p2,  p3,  p4,  p5,  p6,  p7,  p8,  p9,  p10, p11, p12, p13,
      p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,
      p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37};
  std::map<int, std::string> std_map{
      p1,  p2,  p3,  p4,  p5,  p6,  p7,  p8,  p9,  p10, p11, p12, p13,
      p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,
      p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37};
  void eq_map(my::Map<int, std::string> map,
              std::map<int, std::string> std_map);
};

void MapTest::eq_map(my::Map<int, std::string> map,
                     std::map<int, std::string> std_map) {
  EXPECT_EQ(map.Size(), std_map.size());
  my::Map<int, std::string>::iterator i1 = map.Begin();
  std::map<int, std::string>::iterator i2 = std_map.begin();
  while (i2 != std_map.end()) {
    EXPECT_EQ(*i1, *i2);
    ++i1;
    ++i2;
  }
  i1 = --(map.End());
  i2 = --(std_map.end());
  while (i2 != std_map.begin()) {
    EXPECT_EQ(*i1, *i2);
    --i1;
    --i2;
  }
  EXPECT_EQ(*i1, *i2);
}

TEST(map, default_constructor_empty_size) {
  my::Map<int, std::string> map;
  EXPECT_TRUE(map.Empty());
}

TEST_F(MapTest, init_constructor_insert) { eq_map(map, std_map); }

TEST_F(MapTest, copy_constructor) {
  my::Map<int, std::string> Copy(map);
  eq_map(Copy, std_map);
}

TEST_F(MapTest, move_constructor_assignment) {
  my::Map<int, std::string> move1(std::move(map));
  eq_map(move1, std_map);
  my::Map<int, std::string> move2 = std::move(move1);
  eq_map(move2, std_map);
}

TEST_F(MapTest, element_access) {
  EXPECT_EQ(map.at(3), std_map.at(3));
  EXPECT_EQ(map.at(-17), std_map.at(-17));
  EXPECT_EQ(map.at(15), std_map.at(15));
  EXPECT_EQ(map[3], std_map[3]);
  EXPECT_EQ(map[50], std_map[50]);
}

TEST_F(MapTest, max_size) { EXPECT_EQ(map.MaxSize(), std_map.max_size()); }

TEST_F(MapTest, clear) {
  map.Clear();
  EXPECT_TRUE(map.Empty());
}

TEST_F(MapTest, insert) {
  std::pair<my::Map<int, std::string>::iterator, bool> res =
      map.Insert(std::pair<int, std::string>(-28, "a"));
  EXPECT_EQ(std::get<0>(res), map.Begin());
  EXPECT_TRUE(std::get<1>(res));
  res = map.Insert(42, "b");
  EXPECT_EQ(std::get<0>(res), --(map.End()));
  EXPECT_TRUE(std::get<1>(res));
  res = map.InsertOrAssign(29, "c");
  EXPECT_EQ(std::get<0>(res), --(--(map.End())));
  EXPECT_TRUE(std::get<1>(res));
  res = map.InsertOrAssign(1, "d");
  EXPECT_EQ(std::get<0>(*(std::get<0>(res))), 1);
  EXPECT_EQ(std::get<1>(*(std::get<0>(res))), "d");
  EXPECT_FALSE(std::get<1>(res));
  std_map.insert(std::pair<int, std::string>(-28, "a"));
  std_map.insert_or_assign(42, "b");
  std_map.insert_or_assign(29, "c");
  std_map.insert_or_assign(1, "d");
  eq_map(map, std_map);
}

TEST_F(MapTest, erase) {
  map.Erase(map.Begin());
  std_map.erase(std_map.begin());
  map.Erase(++map.Begin());
  std_map.erase(++(std_map.begin()));
  map.Erase(--map.End());
  std_map.erase(--(std_map.end()));
  eq_map(map, std_map);
}

TEST_F(MapTest, swap) {
  my::Map<int, std::string> empty;
  std::map<int, std::string> std_empty;
  map.Swap(empty);
  std_map.swap(std_empty);
  eq_map(empty, std_empty);
  EXPECT_TRUE(map.Empty());
}

TEST_F(MapTest, merge) {
  std::pair<int, std::string> pair1{17, "asd"};
  std::pair<int, std::string> pair2{3, "sda"};
  std::pair<int, std::string> pair3{-20, "ads"};
  std::pair<int, std::string> pair4{25, "dsaf"};
  std::pair<int, std::string> pair5{0, "fasd"};
  std::pair<int, std::string> pair6{8, "wasd"};
  std::pair<int, std::string> pair7{-16, "sdwa"};
  std::pair<int, std::string> pair8{-8, "dswa"};
  std::pair<int, std::string> pair9{7, "aaaa"};
  my::Map<int, std::string> map2{pair1, pair2, pair3, pair4, pair5,
                                  pair6, pair7, pair8, pair9};
  std::map<int, std::string> std_map2{pair1, pair2, pair3, pair4, pair5,
                                      pair6, pair7, pair8, pair9};
  map.Merge(map2);
  std_map.merge(std_map2);
  eq_map(map, std_map);
  eq_map(map2, std_map2);
  my::Map<int, std::string> map3;
  std::map<int, std::string> std_map3;
  map3.Merge(map2);
  std_map3.merge(std_map2);
  eq_map(map3, std_map3);
  EXPECT_TRUE(map2.Empty());
}

TEST_F(MapTest, contains) {
  EXPECT_FALSE(map.Contains(8));
  EXPECT_FALSE(map.Contains(-18));
  EXPECT_TRUE(map.Contains(15));
  EXPECT_TRUE(map.Contains(10));
}

TEST_F(MapTest, emplace) {
  std::pair<int, std::string> pair1{17, "vvv"};
  std::pair<int, std::string> pair2{3, "zzz"};
  std::pair<int, std::string> pair3{-20, "ooo"};
  std::pair<int, std::string> pair4{25, "ggg"};
  std::pair<int, std::string> pair5{0, "kkk"};
  map.Emplace(pair1, pair2, pair3, pair4, pair5);
  std_map.insert(pair1);
  std_map.insert(pair2);
  std_map.insert(pair3);
  std_map.insert(pair4);
  std_map.insert(pair5);
  eq_map(map, std_map);
}

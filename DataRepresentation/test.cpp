#include <gtest/gtest.h>

extern "C" {
#include <data.h>
}

#define MAX_LEN 1024

TEST(ProjectTests, Convert_to_base_2) {
  DataNode b0 = {'5', NULL};
  DataNode b1 = {'0', &b0};
  DataNode b2 = {'2', &b1};

  Data d205;
  d205.base = 10;
  d205.sign = 0;
  d205.len = 3;
  d205.number_bits = 8;
  d205.data = &b2;

  Data b = convert_to_base_n(d205, 2);

  EXPECT_EQ(b.base, 2)
      << "The return data of convert_to_base_n function is not base 2";
  EXPECT_EQ(b.sign, 0) << "The return data of convert_to_base_n function "
                          "should have the same sign";
  EXPECT_EQ(b.number_bits, 8) << "The return data of convert_to_base_n "
                                 "function should have the same number_bits";
  EXPECT_EQ(b.len, 8) << "The return data of convert_to_base_n function should "
                         "have a linkedList with length 8";
  DataNode *node = b.data;
  EXPECT_EQ(node->number, '1') << "The return data of convert_to_base_n "
                                  "function has wrong linkedList of numbers";
  node = node->next;
  EXPECT_EQ(node->number, '1') << "The return data of convert_to_base_n "
                                  "function has wrong linkedList of numbers";
  node = node->next;
  EXPECT_EQ(node->number, '0') << "The return data of convert_to_base_n "
                                  "function has wrong linkedList of numbers";
  node = node->next;
  EXPECT_EQ(node->number, '0') << "The return data of convert_to_base_n "
                                  "function has wrong linkedList of numbers";
  node = node->next;
  EXPECT_EQ(node->number, '1') << "The return data of convert_to_base_n "
                                  "function has wrong linkedList of numbers";
  node = node->next;
  EXPECT_EQ(node->number, '1') << "The return data of convert_to_base_n "
                                  "function has wrong linkedList of numbers";
  node = node->next;
  EXPECT_EQ(node->number, '0') << "The return data of convert_to_base_n "
                                  "function has wrong linkedList of numbers";
  node = node->next;
  EXPECT_EQ(node->number, '1') << "The return data of convert_to_base_n "
                                  "function has wrong linkedList of numbers";
  node = node->next;
  EXPECT_TRUE(node == NULL)
      << "The return data of convert_to_base_n function has "
         "wrong linkedList of numbers";
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

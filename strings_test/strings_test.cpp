#include "strings.h"

#include <gtest/gtest.h>

TEST(StringsTest, SplitTest) {
  const std::string str1 = "This is a Split Test";
  const std::vector<std::string> result1 = strings::Split(str1, ' ');
  EXPECT_EQ(5, result1.size());
  EXPECT_EQ("This", result1[0]);
  EXPECT_EQ("is", result1[1]);
  EXPECT_EQ("a", result1[2]);
  EXPECT_EQ("Split", result1[3]);
  EXPECT_EQ("Test", result1[4]);

  const std::string str2 = "  SplitTest  ";
  const std::vector<std::string> result2 = strings::Split(str2, ' ');
  EXPECT_EQ(1, result2.size());
  EXPECT_EQ("SplitTest", result2[1]);
}

TEST(StringsTest, StartsWithTest) {
  const std::string str = "Hello World";
  const std::string substr1 = "Hel";
  const std::string substr2 = "Hello World";
  const std::string substr3 = "World";
  EXPECT_TRUE(strings::StartsWith(str, substr1));
  EXPECT_TRUE(strings::StartsWith(str, substr2));
  EXPECT_FALSE(strings::StartsWith(str, substr3));
}

TEST(StringsTest, EndsWithTest) {
  const std::string str = "Hello World";
  const std::string substr1 = "rld";
  const std::string substr2 = "Hello World";
  const std::string substr3 = "Hello";
  EXPECT_TRUE(strings::EndsWith(str, substr1));
  EXPECT_TRUE(strings::EndsWith(str, substr2));
  EXPECT_FALSE(strings::EndsWith(str, substr3));
}

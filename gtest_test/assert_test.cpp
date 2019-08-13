#include "utils.h"

#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(GTest, AssertTest) {
  ASSERT_TRUE(IsPrime(73));

  std::vector<int> x{1, 2, 3}, y{1, 2, 3};
  for (size_t i = 0; i < x.size(); i++) {
    EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
  }

  const char* str = "Hello World";
  std::string s(str);
  ASSERT_STREQ(s.c_str(), str);

  ASSERT_ANY_THROW([]{ throw std::exception(); }());
  ASSERT_THROW([]{ throw std::exception(); }(), std::exception);

  ASSERT_PRED2([](int a, int b){ return a < b; }, 1, 2);

  ASSERT_FLOAT_EQ(1.9999999, 2.0);
}

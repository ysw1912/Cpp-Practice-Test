#include "utils.h"

#include <gtest/gtest.h>

class ParamTest : public ::testing::TestWithParam<int> {};

// 参数化.
INSTANTIATE_TEST_SUITE_P(TrueReturn, ParamTest, ::testing::Values(13, 43, 73));

TEST_P(ParamTest, IsPrime) {
  ASSERT_TRUE(IsPrime(GetParam()));
}

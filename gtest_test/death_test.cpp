#include <gtest/gtest.h>

TEST(DeathTest, Error) {
  ASSERT_DEATH([]{
      int* ptr = nullptr;
      *ptr = 1;
  }(), "");  // 第二个参数为正则表达式, 用来匹配异常时在 stderr 中输出的内容.
}

TEST(DeathTest, Exit) {
  ASSERT_EXIT(exit(1), ::testing::ExitedWithCode(1), "");
}

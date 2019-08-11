#include <iostream>

#include <gtest/gtest.h>

class GlobalTest : public ::testing::Environment {
 public:
  void SetUp() override
  {
    std::cout << "\nGlobalTest SetUp\n";
  }
  void TearDown() override
  {
    std::cout << "GlobalTest TearDown\n";
  }
};

int main(int argc, char** argv) {
  ::testing::AddGlobalTestEnvironment(new GlobalTest);
  // 设置 Test 重复运行次数.
  ::testing::GTEST_FLAG(repeat) = 2;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#include <iostream>
#include <map>

#include <gtest/gtest.h>

class MapTestSuite : public ::testing::Test {
 protected:
  // 在每个 TestSuite 前后执行.
  static void SetUpTestSuite() {
    std::cout << "\nSetUp TestSuite\n";
  }
  static void TearDownTestSuite() {
    std::cout << "TearDown TestSuite\n";
  }

  // 在每个 TestCase 前后执行.
  void SetUp() override {
    std::cout << "Setup map\n";
    for (int i = 1; i <= size_; i++) {
      map_.insert(std::make_pair(i, i + 1));
    }
  }
  void TearDown() override
  {
    std::cout << "Clean map\n";
    map_.clear();
  }

  int size_ = 5;
  std::map<int,int> map_;
};

TEST_F(MapTestSuite, Find) {
  for (int i = 1; i <= size_; i++) {
    auto it = map_.find(i);
    ASSERT_EQ(it->second, i + 1);
  }
}

TEST_F(MapTestSuite, Size) {
  ASSERT_EQ(map_.size(), size_);
}

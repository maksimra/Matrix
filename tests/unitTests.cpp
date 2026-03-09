#include "mathUtils.hpp"
#include "matrix.hpp"
#include <gtest/gtest.h>

TEST(unitTest, checkCopyAssign) {
  std::vector<double> elems(
      {1.2, 2.3, 3.4, 4.5, 5.6, 6.7, 7.8, 8.9, 10.11, 12.13, 13.14, 14.15});
  Matrix::Matrix<double> m1{4, 3, elems.begin(), elems.end()};
  Matrix::Matrix<double> m2{4, 3};
  m2 = m1;
  EXPECT_TRUE(m1 == m2);
}

TEST(unitTests, checkCopyInit) {
  std::vector<double> elems({1.2, 2.3, 3.4, 4.5, 5.6, 6.7});
  Matrix::Matrix<double> m1{2, 3, elems.begin(), elems.end()};
  Matrix::Matrix<double> m2{m1};
  EXPECT_TRUE(m1 == m2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
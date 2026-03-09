#include "gettingValue.hpp"
#include "mathUtils.hpp"
#include "matrix.hpp"
#include <cmath>
#include <fstream>
#include <gtest/gtest.h>

TEST(e2e, checkMatrixDeterminant) {
  const int numberTests = 10;

  for (int testNumber = 1; testNumber <= numberTests; ++testNumber) {
    std::cout << testNumber << " Test" << std::endl;

    std::string testFileName =
        "tests/e2e/tests/" + std::to_string(testNumber) + ".txt";
    std::fstream testFile(testFileName);
    if (!testFile.is_open()) {
      throw std::runtime_error("Failed to open file " +
                               std::string(testFileName));
    }

    std::string answFileName =
        "tests/e2e/keys/" + std::to_string(testNumber) + ".txt";
    std::fstream answFile(answFileName);
    if (!answFile.is_open()) {
      throw std::runtime_error("Failed to open file " +
                               std::string(answFileName));
    }

    int matrixSize = 0;
    getPositiveValFromIstream(&matrixSize, testFile);

    std::vector<double> elems;
    double elem = NAN;
    int numElems = matrixSize * matrixSize;
    for (int i = 0; i < numElems; i++) {
      getSmthFromIstream(&elem, testFile);
      elems.push_back(elem);
    }

    Matrix::Matrix<double> m{matrixSize, matrixSize, elems.begin(),
                             elems.end()};

    double refDeterminant = NAN;
    answFile >> refDeterminant;
    EXPECT_TRUE(
        MathUtils::isZero(m.determinant() - refDeterminant, refDeterminant));
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
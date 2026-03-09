#include "gettingValue.hpp"
#include "matrix.hpp"
#include <cmath>
#include <iostream>

int main() {
  try {
    int matrixSize = 0;
    getPositiveValFromIstream(&matrixSize, std::cin);

    std::vector<double> elems;
    double elem = NAN;
    int numElems = matrixSize * matrixSize;
    for (int i = 0; i < numElems; i++) {
      getSmthFromIstream(&elem, std::cin);
      elems.push_back(elem);
    }

    Matrix::Matrix<double> m{matrixSize, matrixSize, elems.begin(),
                             elems.end()};

    std::cerr << m.determinant() << std::endl;
  } catch (const std::runtime_error &error) {
    std::cerr << error.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
#pragma once

#include "mathUtils.hpp"
#include <cassert>
#include <cstring>
#include <vector>
#include <cmath>

namespace Matrix {
template <typename T> class MatrixData {
  int x_, y_;
  T *data_ = nullptr;

  struct ProxyRow {
    T *row;
    T &operator[](int n) { return row[n]; }
  };

  struct ConstProxyRow {
    const T *row;
    const T &operator[](int n) const { return row[n]; }
  };

public:
  MatrixData(int cols, int rows, T val = T{})
      : x_(cols), y_(rows), data_(new T[x_ * y_]) {
    size_t numElems = x_ * y_;
    try {
      for (int i = 0; i < numElems; ++i) {
        data_[i] = val;
      }
    }
    catch (...) {
      delete [] data_;
      throw;  
    }
  }

  template <typename It>
  MatrixData(int cols, int rows, It start, It fin)
      : x_(cols), y_(rows), data_(new T[x_ * y_]) {
    assert(std::distance(start, fin) == x_ * y_);

    try {
      It elem = start;
      for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
          data_[y * cols + x] = *elem;
          elem++;
        }
      }
    }
    catch (...) {
      delete [] data_;
      throw; 
    }
    
  }

  static MatrixData eye(int size) {
    MatrixData m{size, size, 0};

    for (int i = 0; i < size; i++)
      m.data_[i + size * i] = 1;

    return m;
  }

  MatrixData(const MatrixData &other)
      : x_(other.x_), y_(other.y_), data_(new T[x_ * y_]) {
    size_t numElems = x_ * y_;

    try {
      for (int i = 0; i < numElems; ++i) {
        data_[i] = other.data_[i];
      }
    }
    catch (...) {
      delete [] data_;
      throw;
    }
  }

  MatrixData(MatrixData &&other) noexcept : x_(other.x_), y_(other.y_) {
    std::swap(data_, other.data_);
  }

  MatrixData &operator=(const MatrixData &other) {
    if (this == &other)
      return *this;

    MatrixData copy{other};
    std::swap(*this, copy);

    return *this;
  }

  MatrixData &operator=(MatrixData &&other) noexcept {
    if (this == &other)
      return *this;

    x_ = other.x_;
    y_ = other.y_;
    std::swap(data_, other.data_);

    return *this;
  }

  int ncols() const noexcept { return x_; }
  int nrows() const noexcept { return y_; }

  ProxyRow operator[](int n) { return ProxyRow{data_ + n * x_}; }

  ConstProxyRow operator[](int n) const {
    return ConstProxyRow{data_ + n * x_};
  }

  ~MatrixData() { delete[] data_; }
};

template <typename T> struct Matrix {
  MatrixData<T> m_;

  Matrix(int cols, int rows, T val = T{}) : m_(cols, rows, val) {}

  template <typename It>
  Matrix(int cols, int rows, It start, It fin) : m_(cols, rows, start, fin) {}

  double determinant() const {
    assert(m_.ncols() == m_.nrows());

    Matrix mCopy{*this};
    int size = m_.ncols();
    std::vector<double> scale(size);
    for (int i = 0; i < size; i++) {
      scale[i] = 0;
      for (int j = 0; j < size; j++) {
        if (std::abs(mCopy.m_[i][j]) > scale[i])
          scale[i] = std::abs(mCopy.m_[i][j]);
      }
    }

    long double det = 1.0;
    for (int i = 0; i < size; i++) {
      int pivot = i;
      double best = scale[i] ? std::abs(mCopy.m_[i][i]) / scale[i] : 0;

      for (int j = i + 1; j < size; j++) {
        double val = std::abs(mCopy.m_[j][i]) / scale[j];
        if (val > best) {
          best = val;
          pivot = j;
        }
      }

      if (std::abs(mCopy.m_[pivot][i]) < 1e-18)
        return 0.0;

      if (pivot != i) {
        for (int k = 0; k < size; k++) {
          std::swap(mCopy.m_[pivot][k], mCopy.m_[i][k]);
        }
        std::swap(scale[pivot], scale[i]);
        det *= -1;
      }

      det *= mCopy.m_[i][i];

      for (int j = i + 1; j < size; j++) {
        long double factor =
            static_cast<long double>(mCopy.m_[j][i]) / mCopy.m_[i][i];
        for (int k = i + 1; k < size; k++) {
          mCopy.m_[j][k] -= factor * mCopy.m_[i][k];
        }
      }
    }

    return det;
  }
};

template <typename T>
bool operator==(const Matrix<T> &lhs, const Matrix<T> &rhs) {
  int lhsX = lhs.m_.ncols();
  int rhsX = rhs.m_.ncols();
  if (lhsX != rhsX)
    return false;

  int lhsY = lhs.m_.nrows();
  int rhsY = rhs.m_.nrows();
  if (lhsY != rhsY)
    return false;

  for (int y = 0; y < rhsY; y++)
    for (int x = 0; x < rhsX; x++)
      if (!MathUtils::isZero(lhs.m_[y][x] - rhs.m_[y][x], rhs.m_[y][x]))
        return false;

  return true;
}
} // namespace Matrix
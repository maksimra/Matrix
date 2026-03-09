#include "mathUtils.hpp"
#include <cmath>

namespace MathUtils {
bool isZero(double number, double scale) {
  return std::abs(number) <= EPS * std::abs(scale);
}
}; // namespace MathUtils
#ifndef HUNGARIAN_CPP_RANDOM_HPP
#define HUNGARIAN_CPP_RANDOM_HPP

namespace hungarian_cpp {

template <typename T> T GenerateRandomNum(int n) {
  if (n == 0) {
    return 123456789;
  } else {
    return ((22695477 * GenerateRandomNum<T>(n - 1) + 12345) % 1073741824);
  }
}
} // namespace hungarian_cpp
#endif

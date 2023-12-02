/* vim: set filetype=cpp : */

#ifndef RANDOM_HPP
#define RANDOM_HPP

template <typename T> T GenerateRandomNum(int n) {
  if (n == 0) {
    return 123456789;
  } else {
    return ((22695477 * GenerateRandomNum<T>(n - 1) + 12345) % 1073741824);
  }
}
#endif

/* vim: set filetype=cpp : */

#ifndef MATRIX_HELPERS_HPP
#define MATRIX_HELPERS_HPP

#include "matrix.hpp"
#include "random.hpp"

#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T> T DigitsToNumber(const std::vector<char> &digits) {
  T number{0};
  int current_digit{};

  for (int i{static_cast<int>(digits.size()) - 1}, loop_count{0}; i >= 0;
       --i, ++loop_count) {
    switch (digits[i]) {
    case '1':
      current_digit = 1;
      break;
    case '2':
      current_digit = 2;
      break;
    case '3':
      current_digit = 3;
      break;
    case '4':
      current_digit = 4;
      break;
    case '5':
      current_digit = 5;
      break;
    case '6':
      current_digit = 6;
      break;
    case '7':
      current_digit = 7;
      break;
    case '8':
      current_digit = 8;
      break;
    case '9':
      current_digit = 9;
      break;
    case '0':
      current_digit = 0;
      break;
    default:
      throw std::runtime_error("input contains non-number character");
      break;
    }
    number += (current_digit * std::pow(10, loop_count));
  }

  return number;
}

template <typename T>
Matrix<T> ReadMatrixFromFile(const std::string &file_name) {
  std::vector<std::vector<T>> matrix;
  std::vector<T> row;
  std::vector<char> digits;

  std::ifstream input_file{file_name};

  if (!input_file) {
    throw std::runtime_error("unable to open input file");
  }

  while (input_file) {
    std::string current_line;
    std::getline(input_file, current_line);

    for (size_t i{0}; i < current_line.length(); ++i) {
      if (current_line[i] == ' ') {
        row.push_back(DigitsToNumber<T>(digits));
        digits.clear();
      } else {
        digits.push_back(current_line[i]);
      }
    }

    row.push_back(DigitsToNumber<T>(digits));
    digits.clear();

    matrix.push_back(row);
    row.clear();
  }

  matrix.pop_back();

  return Matrix<T>{matrix};
}

template <typename T> Matrix<T> ReadMatrixFromStdin() {
  std::vector<std::vector<T>> matrix;
  std::vector<T> row;
  std::vector<char> digits;

  std::string current_line;

  while (std::getline(std::cin, current_line)) {
    for (size_t i{0}; i < current_line.length(); ++i) {
      if (current_line[i] == ' ') {
        row.push_back(DigitsToNumber<T>(digits));
        digits.clear();
      } else {
        digits.push_back(current_line[i]);
      }
    }

    row.push_back(DigitsToNumber<T>(digits));
    digits.clear();

    matrix.push_back(row);
    row.clear();

    current_line.clear();
  }

  return Matrix<T>{matrix};
}

template <typename T> Matrix<T> GenerateRandomMatrix(const size_t size) {
  int n{0};
  std::vector<std::vector<T>> matrix;
  std::vector<T> row;

  for (size_t cur_row{0}; cur_row < size; ++cur_row) {
    for (size_t cur_col{0}; cur_col < size; ++cur_col) {
      row.push_back(GenerateRandomNum<T>(n));
      ++n;
    }

    matrix.push_back(row);
    row.clear();
  }

  return Matrix<T>{matrix};
}

#endif

/* vim: set filetype=cpp : */

#ifndef MATRIX_HELPERS_HPP
#define MATRIX_HELPERS_HPP

#include "matrix.hpp"

#include <string>
#include <vector>

template <typename T>
Matrix<T> ReadMatrixFromFile(const std::string &file_name);

template <typename T> Matrix<T> ReadMatrixFromStdin();

template <typename T> Matrix<T> GenerateRandomMatrix(const size_t size);

template <typename T> T DigitsToNumber(const std::vector<char> &digits);

#include "matrix_helpers.tpp"

#endif

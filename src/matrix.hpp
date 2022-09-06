/* vim: set filetype=cpp : */

#pragma once

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <vector>

template<typename T>
class Matrix
{
    public:

        Matrix();

        Matrix(const Matrix& matrix);

        Matrix(const size_t rows, const size_t cols);

        Matrix(const std::initializer_list<std::initializer_list<T>>& init_list);

        Matrix(const std::vector<std::vector<T>>& vector);

        ~Matrix();

    private:

        size_t m_rows;
        size_t m_cols;
        T** m_data;

    public:

        void Resize(const size_t rows, const size_t cols);

        void Clear();

        size_t GetRows() const;

        size_t GetCols() const;

    public:

        Matrix<T>& operator= (const Matrix<T>& m);

        T& operator() (const size_t row, const size_t col);
        const T& operator() (const size_t row, const size_t cols) const;

        template<typename U>
        friend std::ostream& operator<< (std::ostream& out, const Matrix<U>& m);
};

#include "matrix.tpp"

#endif

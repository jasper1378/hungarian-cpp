/* vim: set filetype=cpp : */

#ifndef MATRIX_TPP
#define MATRIX_TPP

#include "matrix.hpp"

#include <cstddef>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

template<typename T>
Matrix<T>::Matrix()
    : m_rows{ 0 },
      m_cols{ 0 },
      m_data{ nullptr }
{
}

template<typename T>
Matrix<T>::Matrix(const Matrix& m)
{
    if (m.m_data == nullptr)
    {
        m_data = nullptr;
        m_rows = 0;
        m_cols = 0;
    }
    else
    {
        m_data = nullptr;
        Resize(m.m_rows, m.m_cols);

        for (size_t cur_row{ 0 }; cur_row < m_rows; ++cur_row)
        {
            for (size_t cur_col{ 0 }; cur_col < m_cols; ++cur_col)
            {
                m_data[cur_row][cur_col] = m.m_data[cur_row][cur_col];
            }
        }
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix&& m) noexcept
    : m_rows{ m.m_rows },
      m_cols{ m.m_cols },
      m_data{ m.m_data }
{
    m.m_rows = 0;
    m.m_cols = 0;
    m.m_data = nullptr;
}

template<typename T>
Matrix<T>::Matrix(const size_t rows, const size_t cols)
    : m_rows{ 0 },
      m_cols{ 0 },
      m_data{ nullptr }
{
    Resize(rows, cols);
}

template<typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& init_list)
    : m_rows{ 0 },
      m_cols{ 0 },
      m_data{ nullptr }
{
    for (const std::initializer_list<T>* init_list_row{ init_list.begin() }; init_list_row != init_list.end(); ++init_list_row)
    {
        if (init_list.begin()->size() != init_list_row->size())
        {
            throw std::runtime_error{ "Matrix must be rectangular" };
        }
    }

    Resize(init_list.size(), init_list.begin()->size());

    size_t cur_row{ 0 };
    for (const std::initializer_list<T>* init_list_row{ init_list.begin() }; init_list_row != init_list.end(); ++init_list_row, ++cur_row)
    {
        size_t cur_col{ 0 };
        for (const T* init_list_val{ init_list_row->begin() }; init_list_val != init_list_row->end(); ++init_list_val, ++cur_col)
        {
            m_data[cur_row][cur_col] = *init_list_val;
        }
    }
}

template<typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& vector)
    : m_rows{ 0 },
      m_cols{ 0 },
      m_data{ nullptr }
{
    for (size_t cur_row{ 0 }; cur_row < vector.size(); ++cur_row)
    {
        if (vector[0].size() != vector[cur_row].size())
        {
            throw std::runtime_error{ "Matrix must be rectangular" };
        }
    }

    Resize(vector.size(), vector[0].size());

    for (size_t cur_row{ 0 }; cur_row < m_rows; ++cur_row)
    {
        for (size_t cur_col{ 0 }; cur_col < m_cols; ++cur_col)
        {
            m_data[cur_row][cur_col] = vector[cur_row][cur_col];
        }
    }
}

template<typename T>
Matrix<T>::~Matrix()
{
    for (size_t i{ 0 }; i < m_rows; ++i)
    {
        delete[] m_data[i];
    }

    delete[] m_data;

    m_data = nullptr;

    m_rows = 0;
    m_cols = 0;
}

template<typename T>
void Matrix<T>::Resize(const size_t rows, const size_t cols)
{

    if (m_data == nullptr)
    {
        m_data = new T*[rows];
        for (size_t i{ 0 }; i < rows; ++i)
        {
            m_data[i] = new T[cols];
        }

        m_rows = rows;
        m_cols = cols;

        Clear();
    }

    else
    {
        T** new_data;

        new_data = new T*[rows];
        for (size_t cur_row{ 0 }; cur_row < rows; ++cur_row)
        {
            new_data[cur_row] = new T[cols];

            for (size_t cur_col{ 0 }; cur_col < cols; ++cur_col)
            {
                new_data[cur_row][cur_col] = T{};
            }
        }

        size_t min_rows{ (rows < m_rows) ? rows : m_rows };
        size_t min_cols{ (cols < m_cols) ? cols : m_cols };

        for (size_t cur_row{ 0 }; cur_row < min_rows; ++cur_row)
        {
            for (size_t cur_col{ 0 }; cur_col < min_cols; ++cur_col)
            {
                new_data[cur_row][cur_col] = m_data[cur_row][cur_col];
            }
        }

        if (m_data != nullptr)
        {
            for (size_t i{ 0 }; i < m_rows; ++i)
            {
                delete[] m_data[i];
            }

            delete[] m_data;
        }

        m_data = new_data;
    }

    m_rows = rows;
    m_cols = cols;
}

template<typename T>
void Matrix<T>::Clear()
{
    if (m_data == nullptr)
    {
        throw std::runtime_error{ "can't clear empty Matrix" };
    }

    for (size_t cur_row{ 0 }; cur_row < m_rows; ++cur_row)
    {
        for (size_t cur_col{ 0 }; cur_col < m_cols; ++cur_col)
        {
            m_data[cur_row][cur_col] = T{};
        }
    }
}

template<typename T>
size_t Matrix<T>::GetRows() const
{
    return m_rows;
}

template<typename T>
size_t Matrix<T>::GetCols() const
{
    return m_cols;
}

template<typename T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& m)
{
    if (this == &m)
    {
        return *this;
    }

    if (m.m_data == nullptr)
    {
        for (size_t i{ 0 }; i < m_rows; ++i)
        {
            delete[] m_data[i];
        }

        delete[] m_data;

        m_data = nullptr;

        m_rows = 0;
        m_cols = 0;
    }

    else
    {
        Resize(m.m_rows, m.m_cols);

        for (size_t cur_row{ 0 }; cur_row < m_rows; ++cur_row)
        {
            for (size_t cur_col{ 0 }; cur_col < m_cols; ++cur_col)
            {
                m_data[cur_row][cur_col] = m.m_data[cur_row][cur_col];
            }
        }
    }

    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator= (Matrix<T>&& m) noexcept
{
    if (this == &m)
    {
        return *this;
    }

    m_rows = m.m_rows;
    m_cols = m.m_cols;
    m_data = m.m_data;

    m.m_rows = 0;
    m.m_cols = 0;
    m.m_data = nullptr;

    return *this;
}

template<typename T>
T& Matrix<T>::operator() (const size_t row, const size_t col)
{
    if ((row > m_rows) || (col > m_cols))
    {
        throw std::out_of_range{ "invalid index when tring to access Matrix" };
    }

    return m_data[row][col];
}

template<typename T>
const T& Matrix<T>::operator() (const size_t row, const size_t col) const
{
    if ((row > m_rows) || (col > m_cols))
    {
        throw std::out_of_range{ "invalid index when tring to access Matrix" };
    }

    return m_data[row][col];
}

template<typename U>
std::ostream& operator<< (std::ostream& out, const Matrix<U>& m)
{
    for (size_t cur_row{ 0 }; cur_row < m.m_rows; ++cur_row)
    {
        for (size_t cur_col{ 0 }; cur_col < m.m_cols; ++cur_col)
        {
            std::cout << m.m_data[cur_row][cur_col] << ' ';
        }

        std::cout << '\n';
    }

    return out;
}

#endif

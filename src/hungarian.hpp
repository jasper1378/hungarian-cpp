/* vim: set filetype=cpp : */

#ifndef HUNGARIAN_HPP
#define HUNGARIAN_HPP

#include "matrix.hpp"

#include <cstddef>
#include <iostream>
#include <vector>

template<typename T>
class Hungarian
{
    public:

        Hungarian(const Hungarian& h);
        Hungarian(Hungarian&& h) noexcept;

        Hungarian(const Matrix<T>& source_matrix);
        Hungarian(Matrix<T>&& source_matrix);

        virtual ~Hungarian();

    private:

        struct HungarianNotation
        {
            T value{};
            bool is_covered_as_row{ false };
            bool is_covered_as_col{ false };
            bool is_starred{ false };
            bool is_primed{ false };

            friend std::ostream& operator<< (std::ostream& out, HungarianNotation& hn) //silence compiler error
            {
                out << "operator<< for struct HungarianNotation is only defined to silence a compiler error";
                return out;
            }
        };

        struct Location2D
        {
            size_t row{};
            size_t col{};
        };

        struct Value2D
        {
            T value{};
            Location2D location{};
        };

        struct Solution
        {
            T sum{ 0 };
            std::vector<Value2D> values;
        };

    private:

        Matrix<HungarianNotation> m_mx_og;
        Matrix<HungarianNotation> m_mx_wrk;

        T m_smallest_uncovered_value_from_S4;
        Location2D m_primed_zero_from_S4;

        int m_next_step;

        bool m_is_solved;
        Solution m_solution;

    public:

        void Solve();

        virtual void PrintSolution(std::ostream& out) const;

        void PrintLines() const;

        void PrintStars() const;

        void PrintPrimes() const;

    public:

        Hungarian<T>& operator= (const Hungarian<T>& h);
        Hungarian<T>& operator= (Hungarian<T>&& h) noexcept;

        template<typename U>
        friend std::ostream& operator<< (std::ostream& out, const Hungarian<U>& h);

    private:

        Matrix<HungarianNotation> SimpleMatrixToHungarianMatrix(const Matrix<T>& simple_matrix);
        bool MatrixIsSquare() const;

    protected:

        virtual void Step1();

        virtual void Step2();

        virtual void Step3();

        virtual void Step4();

        virtual void Step5();

        void FindStarredZeroInCol(Location2D& cur_pos, std::vector<Location2D>& zeroes_in_series, int& next_step_in_series);

        void FindPrimedZeroInRow(Location2D& cur_pos, std::vector<Location2D>& zeroes_in_series, int& next_step_in_series);

        virtual void Step6();

        virtual void Step7();
};

#include "hungarian.tpp"

#endif

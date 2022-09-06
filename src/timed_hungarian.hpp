/* vim: set filetype=cpp : */

#pragma once

#ifndef TIMED_HUNGARIAN_HPP
#define TIMED_HUNGARIAN_HPP

#include "benchmark.hpp"
#include "hungarian.hpp"
#include "matrix.hpp"

#include <iostream>

template<typename T>
class TimedHungarian : public Hungarian<T>
{
    public:

        TimedHungarian(const TimedHungarian& th);

        TimedHungarian(const Matrix<T>& source_matrix);

        ~TimedHungarian() override;

    private:

        Benchmark m_benchmark;

    public:

        void PrintSolution(std::ostream& out) const override;

    public:

        TimedHungarian<T>& operator= (const TimedHungarian<T>& th);

    private:

        void Step1() override;

        void Step2() override;

        void Step3() override;

        void Step4() override;

        void Step5() override;

        void Step6() override;

        void Step7() override;
};

#include "timed_hungarian.tpp"

#endif

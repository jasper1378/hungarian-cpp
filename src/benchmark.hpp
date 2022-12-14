/* vim: set filetype=cpp : */

#pragma once

#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include "timer.hpp"

#include <iostream>
#include <vector>

class Benchmark
{
    public:

        Benchmark(int num_of_steps);

        ~Benchmark();

    private:

        struct StepTime
        {
            int step_id{};
            Timer current_time{};
            int times_run{};
            double total_time{};
            double average_time{};
        };

    private:

        int m_number_of_steps;
        double m_total_time;
        std::vector<StepTime> m_time_by_step;

    public:

        void Start(int step_id);

        void Stop(int step_id);

        void PrintReport() const;

    public:

        Benchmark& operator= (const Benchmark& bm);

        friend std::ostream& operator<< (std::ostream& out, const Benchmark& bm);

    private:

        void CalcTotalTime();
};

#endif

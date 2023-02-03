/* vim: set filetype=cpp : */

#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer
{
    public:

        Timer();

        ~Timer();

    private:

        using clock_t = std::chrono::steady_clock;
        using second_t = std::chrono::duration<double, std::ratio<1>>;

    private:

        std::chrono::time_point<clock_t> m_beg;

    public:

        void Reset();

        double Elapsed() const;

    public:

        Timer& operator= (const Timer& t);
};

#endif

/* vim: set filetype=cpp : */

#include "timer.hpp"

#include <chrono>
#include <utility>

Timer::Timer()
    : m_beg{ clock_t::now() }
{
}

Timer::Timer(const Timer& t)
    : m_beg{ t.m_beg }
{
}

Timer::Timer(Timer&& t)
    : m_beg{ std::move(t.m_beg) }
{
}

Timer::~Timer()
{
}

void Timer::Reset()
{
    m_beg = clock_t::now();
}

double Timer::Elapsed() const
{
    return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
}

Timer& Timer::operator= (const Timer& t)
{
    if (this == &t)
    {
        return *this;
    }

    m_beg = t.m_beg;

    return *this;
}

Timer& Timer::operator= (Timer&& t)
{
    if (this == &t)
    {
        return *this;
    }

    m_beg = std::move(t.m_beg);

    return *this;
}

/* vim: set filetype=cpp : */

#include "timer.hpp"

#include <chrono>
#include <utility>

Timer::Timer() : m_beg{clock_type::now()} {}

Timer::Timer(const Timer &t) : m_beg{t.m_beg} {}

Timer::Timer(Timer &&t) noexcept : m_beg{t.m_beg} {}

Timer::~Timer() {}

void Timer::Reset() { m_beg = clock_type::now(); }

double Timer::Elapsed() const {
  return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg)
      .count();
}

Timer &Timer::operator=(const Timer &t) {
  m_beg = t.m_beg;

  return *this;
}

Timer &Timer::operator=(Timer &&t) noexcept {
  m_beg = t.m_beg;

  return *this;
}

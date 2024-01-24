/* vim: set filetype=cpp : */

#include "timer.hpp"

#include <chrono>
#include <utility>

hungarian_cpp::Timer::Timer() : m_beg{clock_type::now()} {}

hungarian_cpp::Timer::Timer(const Timer &t) : m_beg{t.m_beg} {}

hungarian_cpp::Timer::Timer(Timer &&t) noexcept : m_beg{t.m_beg} {}

hungarian_cpp::Timer::~Timer() {}

void hungarian_cpp::Timer::Reset() { m_beg = clock_type::now(); }

double hungarian_cpp::Timer::Elapsed() const {
  return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg)
      .count();
}

hungarian_cpp::Timer &hungarian_cpp::Timer::operator=(const Timer &t) {
  m_beg = t.m_beg;

  return *this;
}

hungarian_cpp::Timer &hungarian_cpp::Timer::operator=(Timer &&t) noexcept {
  m_beg = t.m_beg;

  return *this;
}

#ifndef HUNGARIAN_CPP_TIMER_HPP
#define HUNGARIAN_CPP_TIMER_HPP

#include <chrono>

namespace hungarian_cpp {

class Timer {
public:
  Timer();

  Timer(const Timer &t);

  Timer(Timer &&t) noexcept;

  ~Timer();

private:
  using clock_type = std::chrono::steady_clock;
  using second_type = std::chrono::duration<double, std::ratio<1>>;

private:
  std::chrono::time_point<clock_type> m_beg;

public:
  void Reset();

  double Elapsed() const;

public:
  Timer &operator=(const Timer &t);
  Timer &operator=(Timer &&t) noexcept;
};

} // namespace hungarian_cpp
#endif

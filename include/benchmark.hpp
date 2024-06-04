#ifndef HUNGARIAN_CPP_BENCHMARK_HPP
#define HUNGARIAN_CPP_BENCHMARK_HPP

#include "bits-and-bytes/timer/timer.hpp"

#include <iostream>
#include <vector>

namespace hungarian_cpp {

class Benchmark {
public:
  explicit Benchmark(const int num_of_steps);
  Benchmark(const Benchmark &other);
  Benchmark(Benchmark &&other) noexcept;

  ~Benchmark();

private:
  struct StepTime {
    int step_id{};
    bits_and_bytes::timer current_time{};
    int times_run{};
    double total_time{};
    double average_time{};
  };

private:
  int m_number_of_steps;
  double m_total_time;
  std::vector<StepTime> m_time_by_step;

public:
  void Start(const int step_id);

  void Stop(const int step_id);

  void PrintReport() const;

public:
  Benchmark &operator=(const Benchmark &bm);
  Benchmark &operator=(Benchmark &&bm) noexcept;

  friend std::ostream &operator<<(std::ostream &out, const Benchmark &bm);

private:
  void CalcTotalTime();
};

std::ostream &operator<<(std::ostream &out, const Benchmark &bm);

} // namespace hungarian_cpp
#endif

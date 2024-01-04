/* vim: set filetype=cpp : */

#include "benchmark.hpp"

#include <cstddef>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

Benchmark::Benchmark(const int num_of_steps)
    : m_number_of_steps{num_of_steps}, m_total_time{0}, m_time_by_step{} {
  for (int i{1}; i <= num_of_steps; ++i) {
    m_time_by_step.push_back(StepTime{i, Timer{}, 0, 0, 0});
  }
}

Benchmark::Benchmark(const Benchmark &other)
    : m_number_of_steps{other.m_number_of_steps},
      m_total_time{other.m_total_time}, m_time_by_step{other.m_time_by_step} {}

Benchmark::Benchmark(Benchmark &&other) noexcept
    : m_number_of_steps{other.m_number_of_steps},
      m_total_time{other.m_total_time}, m_time_by_step{
                                            std::move(other.m_time_by_step)} {}

Benchmark::~Benchmark() {}

void Benchmark::Start(const int step_id) {
  if ((step_id > m_number_of_steps) && (step_id <= 0)) {
    throw std::out_of_range{"invalid step_id when trying to start step timer"};
  }

  const int cur_step{step_id - 1};

  m_time_by_step[cur_step].current_time.Reset();
}

void Benchmark::Stop(const int step_id) {
  if ((step_id > m_number_of_steps) && (step_id <= 0)) {
    throw std::out_of_range{"invalid step_id when trying to stop step timer"};
  }

  const int cur_step{step_id - 1};

  const double time_for_step{m_time_by_step[cur_step].current_time.Elapsed()};

  ++m_time_by_step[cur_step].times_run;
  m_time_by_step[cur_step].total_time += time_for_step;
  m_time_by_step[cur_step].average_time = (m_time_by_step[cur_step].total_time /
                                           m_time_by_step[cur_step].times_run);

  CalcTotalTime();
}

Benchmark &Benchmark::operator=(const Benchmark &bm) {
  m_number_of_steps = bm.m_number_of_steps;
  m_total_time = bm.m_total_time;
  m_time_by_step = bm.m_time_by_step;

  return *this;
}

Benchmark &Benchmark::operator=(Benchmark &&bm) noexcept {
  if (this == &bm) {
    return *this;
  }

  m_number_of_steps = bm.m_number_of_steps;
  m_total_time = bm.m_total_time;
  m_time_by_step = std::move(bm.m_time_by_step);

  return *this;
}

std::ostream &operator<<(std::ostream &out, const Benchmark &bm) {
  out << "Benchmark report:\n";
  out << '\n';

  for (size_t i{0}; i < bm.m_time_by_step.size(); ++i) {
    out << "Step #" << bm.m_time_by_step[i].step_id << '\n';
    out << "Times run: " << bm.m_time_by_step[i].times_run << '\n';
    out << "Total time: " << bm.m_time_by_step[i].total_time << '\n';
    out << "Average time: " << bm.m_time_by_step[i].average_time << '\n';
    out << '\n';
  }

  out << "Total time: " << bm.m_total_time << '\n';
  out << '\n';

  return out;
}

void Benchmark::CalcTotalTime() {
  for (size_t i{0}; i < m_time_by_step.size(); ++i) {
    m_total_time += m_time_by_step[i].total_time;
  }
}

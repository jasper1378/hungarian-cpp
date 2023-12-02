/* vim: set filetype=cpp : */

#ifndef TIMED_HUNGARIAN_HPP
#define TIMED_HUNGARIAN_HPP

#include "benchmark.hpp"
#include "hungarian.hpp"
#include "matrix.hpp"

#include <iostream>
#include <utility>

template <typename T> class TimedHungarian : public Hungarian<T> {
public:
  TimedHungarian(const TimedHungarian &th)
      : Hungarian<T>{th}, m_benchmark{th.m_benchmark} {}

  TimedHungarian(TimedHungarian &&th) noexcept
      : Hungarian<T>{std::move(th)}, m_benchmark{std::move(th.m_benchmark)} {}

  explicit TimedHungarian(const Matrix<T> &source_matrix)
      : Hungarian<T>{source_matrix}, m_benchmark{Benchmark{7}} {}

  explicit TimedHungarian(Matrix<T> &&source_matrix)
      : Hungarian<T>{std::move(source_matrix)}, m_benchmark{Benchmark{7}} {}

  ~TimedHungarian() override {}

private:
  Benchmark m_benchmark;

public:
  void PrintSolution(std::ostream &out) const {
    Hungarian<T>::PrintSolution(out);
    out << m_benchmark;
  }

public:
  TimedHungarian<T> &operator=(const TimedHungarian<T> &th) {
    Hungarian<T>::operator=(th);

    m_benchmark = th.m_benchmark;

    return *this;
  }

  TimedHungarian<T> &operator=(TimedHungarian<T> &&th) noexcept {
    Hungarian<T>::operator=(std::move(th));

    m_benchmark = std::move(th.m_benchmark);

    return *this;
  }

private:
  void Step1() override {
    m_benchmark.Start(1);
    Hungarian<T>::Step1();
    m_benchmark.Stop(1);
  }

  void Step2() override {
    m_benchmark.Start(2);
    Hungarian<T>::Step2();
    m_benchmark.Stop(2);
  }

  void Step3() override {
    m_benchmark.Start(3);
    Hungarian<T>::Step3();
    m_benchmark.Stop(3);
  }

  void Step4() override {
    m_benchmark.Start(4);
    Hungarian<T>::Step4();
    m_benchmark.Stop(4);
  }

  void Step5() override {
    m_benchmark.Start(5);
    Hungarian<T>::Step5();
    m_benchmark.Stop(5);
  }

  void Step6() override {
    m_benchmark.Start(6);
    Hungarian<T>::Step6();
    m_benchmark.Stop(6);
  }

  void Step7() override {
    m_benchmark.Start(7);
    Hungarian<T>::Step7();
    m_benchmark.Stop(7);
  }
};

#endif

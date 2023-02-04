/* vim: set filetype=cpp : */

#ifndef TIMED_HUNGARIAN_TPP
#define TIMED_HUNGARIAN_TPP

#include "timed_hungarian.hpp"

#include "benchmark.hpp"
#include "hungarian.hpp"
#include "matrix.hpp"

#include <iostream>
#include <utility>

template <typename T>
TimedHungarian<T>::TimedHungarian(const TimedHungarian &th)
    : Hungarian<T>{th}, m_benchmark{th.m_benchmark} {}

template <typename T>
TimedHungarian<T>::TimedHungarian(TimedHungarian &&th)
    : Hungarian<T>{std::move(th)}, m_benchmark{std::move(th.m_benchmark)} {}

template <typename T>
TimedHungarian<T>::TimedHungarian(const Matrix<T> &source_matrix)
    : Hungarian<T>{source_matrix}, m_benchmark{Benchmark{7}} {}

template <typename T>
TimedHungarian<T>::TimedHungarian(Matrix<T> &&source_matrix)
    : Hungarian<T>{std::move(source_matrix)}, m_benchmark{Benchmark{7}} {}

template <typename T> TimedHungarian<T>::~TimedHungarian() {}

template <typename T>
void TimedHungarian<T>::PrintSolution(std::ostream &out) const {
  Hungarian<T>::PrintSolution(out);
  out << m_benchmark;
}

template <typename T>
TimedHungarian<T> &TimedHungarian<T>::operator=(const TimedHungarian<T> &th) {
  if (this == &th) {
    return *this;
  }

  Hungarian<T>::operator=(th);

  m_benchmark = th.m_benchmark;

  return *this;
}

template <typename T>
TimedHungarian<T> &TimedHungarian<T>::operator=(TimedHungarian<T> &&th) {
  if (this == &th) {
    return *this;
  }

  Hungarian<T>::operator=(std::move(th));

  m_benchmark = std::move(th.m_benchmark);

  return *this;
}

template <typename T> void TimedHungarian<T>::Step1() {
  m_benchmark.Start(1);
  Hungarian<T>::Step1();
  m_benchmark.Stop(1);
}

template <typename T> void TimedHungarian<T>::Step2() {
  m_benchmark.Start(2);
  Hungarian<T>::Step2();
  m_benchmark.Stop(2);
}

template <typename T> void TimedHungarian<T>::Step3() {
  m_benchmark.Start(3);
  Hungarian<T>::Step3();
  m_benchmark.Stop(3);
}

template <typename T> void TimedHungarian<T>::Step4() {
  m_benchmark.Start(4);
  Hungarian<T>::Step4();
  m_benchmark.Stop(4);
}

template <typename T> void TimedHungarian<T>::Step5() {
  m_benchmark.Start(5);
  Hungarian<T>::Step5();
  m_benchmark.Stop(5);
}

template <typename T> void TimedHungarian<T>::Step6() {
  m_benchmark.Start(6);
  Hungarian<T>::Step6();
  m_benchmark.Stop(6);
}

template <typename T> void TimedHungarian<T>::Step7() {
  m_benchmark.Start(7);
  Hungarian<T>::Step7();
  m_benchmark.Stop(7);
}

#endif

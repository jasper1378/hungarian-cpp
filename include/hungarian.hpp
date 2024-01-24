#ifndef HUNGARIAN_CPP_HUNGARIAN_HPP
#define HUNGARIAN_CPP_HUNGARIAN_HPP

#include "matrix.hpp"

#include <cmath>
#include <cstddef>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace hungarian_cpp {

template <typename T> class Hungarian {
public:
  Hungarian(const Hungarian &h)
      : m_mx_og{h.m_mx_og}, m_mx_wrk{h.m_mx_wrk},
        m_smallest_uncovered_value_from_S4{
            h.m_smallest_uncovered_value_from_S4},
        m_primed_zero_from_S4{h.m_primed_zero_from_S4},
        m_next_step{h.m_next_step}, m_is_solved{h.m_is_solved},
        m_solution{h.m_solution} {}

  Hungarian(Hungarian &&h) noexcept
      : m_mx_og{std::move(h.m_mx_og)}, m_mx_wrk{std::move(h.m_mx_wrk)},
        m_smallest_uncovered_value_from_S4{
            std::move(h.m_smallest_uncovered_value_from_S4)},
        m_primed_zero_from_S4{std::move(h.m_primed_zero_from_S4)},
        m_next_step{std::move(h.m_next_step)},
        m_is_solved{std::move(h.m_is_solved)},
        m_solution{std::move(h.m_solution)} {}

  explicit Hungarian(const Matrix<T> &source_matrix)
      : m_mx_og{SimpleMatrixToHungarianMatrix(source_matrix)},
        m_mx_wrk{SimpleMatrixToHungarianMatrix(source_matrix)},
        m_smallest_uncovered_value_from_S4{static_cast<T>(INFINITY)},
        m_primed_zero_from_S4{Location2D{0, 0}}, m_next_step{1},
        m_is_solved{false} {
    if (MatrixIsSquare() == false) {
      throw std::runtime_error{"hungarian matrix must be square"};
    }
  }

  explicit Hungarian(Matrix<T> &&source_matrix)
      : m_mx_og{SimpleMatrixToHungarianMatrix(source_matrix)},
        m_mx_wrk{SimpleMatrixToHungarianMatrix(std::move(source_matrix))},
        m_smallest_uncovered_value_from_S4{static_cast<T>(INFINITY)},
        m_primed_zero_from_S4{Location2D{0, 0}}, m_next_step{1},
        m_is_solved{false} {
    if (MatrixIsSquare() == false) {
      throw std::runtime_error{"hungarian matrix must be square"};
    }
  }

  virtual ~Hungarian() {}

private:
  struct HungarianNotation {
    T value{};
    bool is_covered_as_row{false};
    bool is_covered_as_col{false};
    bool is_starred{false};
    bool is_primed{false};

    friend std::ostream &
    operator<<(std::ostream &out,
               HungarianNotation &hn) // silence compiler error
    {
      out << "operator<< for struct HungarianNotation is only defined to "
             "silence a compiler error";
      return out;
    }
  };

  struct Location2D {
    size_t row{};
    size_t col{};
  };

  struct Value2D {
    T value{};
    Location2D location{};
  };

  struct Solution {
    T sum{0};
    std::vector<Value2D> values;
  };

private:
  Matrix<HungarianNotation> m_mx_og;
  Matrix<HungarianNotation> m_mx_wrk;

  T m_smallest_uncovered_value_from_S4;
  Location2D m_primed_zero_from_S4;

  int m_next_step;

  bool m_is_solved;
  Solution m_solution;

public:
  void Solve() {
    while (m_next_step != 0) {
      switch (m_next_step) {
      case 1:
        Step1();
        break;
      case 2:
        Step2();
        break;
      case 3:
        Step3();
        break;
      case 4:
        Step4();
        break;
      case 5:
        Step5();
        break;
      case 6:
        Step6();
        break;
      case 7:
        Step7();
        break;
      }
    }

    m_is_solved = true;
  }

  virtual void PrintSolution(std::ostream &out) const {
    if (m_is_solved == false) {
      throw std::runtime_error{
          "matrix must be solved before printing the solution"};
    }

    out << '\n';
    out << "Solution:\n";
    out << '\n';

    out << "Sum:\n";
    out << m_solution.sum << '\n';
    out << '\n';

    out << "Values:\n\n";

    for (size_t cur_value_index{0}; cur_value_index < m_solution.values.size();
         ++cur_value_index) {
      out << "Value: " << m_solution.values[cur_value_index].value << '\n';
      out << "Row: " << m_solution.values[cur_value_index].location.row << '\n';
      out << "Col: " << m_solution.values[cur_value_index].location.col << '\n';
      out << '\n';
    }
  }

  void PrintLines() const {
    const std::string red{"\033[41m"};
    const std::string green{"\033[42m"};
    const std::string blue{"\033[44m"};
    const std::string reset_color{"\033[0m"};

    std::cout << "\nLines\n";
    std::cout << "(Green: Row; Blue: Col; Red: Both)\n";

    for (size_t cur_row{0}; cur_row < m_mx_wrk.GetRows(); ++cur_row) {
      for (size_t cur_col{0}; cur_col < m_mx_wrk.GetCols(); ++cur_col) {
        if (m_mx_wrk(cur_row, cur_col).value == 0) {
          if (m_mx_wrk(cur_row, cur_col).is_covered_as_row == true &&
              m_mx_wrk(cur_row, cur_col).is_covered_as_col == true) {
            std::cout << red << "000000000" << reset_color << ' ';
          } else if (m_mx_wrk(cur_row, cur_col).is_covered_as_row == true) {
            std::cout << green << "000000000" << reset_color << ' ';
          } else if (m_mx_wrk(cur_row, cur_col).is_covered_as_col == true) {
            std::cout << blue << "000000000" << reset_color << ' ';
          } else {
            std::cout << "000000000" << ' ';
          }
        } else {
          if (m_mx_wrk(cur_row, cur_col).is_covered_as_row == true &&
              m_mx_wrk(cur_row, cur_col).is_covered_as_col == true) {
            std::cout << red << m_mx_wrk(cur_row, cur_col).value << reset_color
                      << ' ';
          } else if (m_mx_wrk(cur_row, cur_col).is_covered_as_row == true) {
            std::cout << green << m_mx_wrk(cur_row, cur_col).value
                      << reset_color << ' ';
          } else if (m_mx_wrk(cur_row, cur_col).is_covered_as_col == true) {
            std::cout << blue << m_mx_wrk(cur_row, cur_col).value << reset_color
                      << ' ';
          } else {
            std::cout << m_mx_wrk(cur_row, cur_col).value << ' ';
          }
        }
      }

      std::cout << '\n';
    }
  }

  void PrintStars() const {
    static const std::string red{"\033[41m"};
    static const std::string green{"\033[42m"};
    static const std::string blue{"\033[44m"};
    static const std::string reset_color{"\033[0m"};

    std::cout << "\nStars\n";

    for (size_t cur_row{0}; cur_row < m_mx_wrk.GetRows(); ++cur_row) {
      for (size_t cur_col{0}; cur_col < m_mx_wrk.GetCols(); ++cur_col) {
        if (m_mx_wrk(cur_row, cur_col).value == 0) {
          if (m_mx_wrk(cur_row, cur_col).is_starred == true) {
            std::cout << red << "000000000" << reset_color << ' ';
          } else {
            std::cout << "000000000" << ' ';
          }
        } else {
          if (m_mx_wrk(cur_row, cur_col).is_starred == true) {
            std::cout << red << m_mx_wrk(cur_row, cur_col).value << reset_color
                      << ' ';
          } else {
            std::cout << m_mx_wrk(cur_row, cur_col).value << ' ';
          }
        }
      }

      std::cout << '\n';
    }
  }

  void PrintPrimes() const {
    const std::string red{"\033[41m"};
    const std::string green{"\033[42m"};
    const std::string blue{"\033[44m"};
    const std::string reset_color{"\033[0m"};

    std::cout << "\nPrimes\n";

    for (size_t cur_row{0}; cur_row < m_mx_wrk.GetRows(); ++cur_row) {
      for (size_t cur_col{0}; cur_col < m_mx_wrk.GetCols(); ++cur_col) {
        if (m_mx_wrk(cur_row, cur_col).value == 0) {
          if (m_mx_wrk(cur_row, cur_col).is_primed == true) {
            std::cout << red << "000000000" << reset_color << ' ';
          } else {
            std::cout << "000000000" << ' ';
          }
        } else {
          if (m_mx_wrk(cur_row, cur_col).is_primed == true) {
            std::cout << red << m_mx_wrk(cur_row, cur_col).value << reset_color
                      << ' ';
          } else {
            std::cout << m_mx_wrk(cur_row, cur_col).value << ' ';
          }
        }
      }

      std::cout << '\n';
    }
  }

public:
  Hungarian<T> &operator=(const Hungarian<T> &h) {
    m_mx_og = h.m_mx_og;
    m_mx_wrk = h.m_mx_wrk;
    m_smallest_uncovered_value_from_S4 = h.m_smallest_uncovered_value_from_S4;
    m_primed_zero_from_S4 = h.m_primed_zero_from_S4;
    m_next_step = h.m_next_step;
    m_is_solved = h.m_is_solved;
    m_solution = h.m_solution;

    return *this;
  }

  Hungarian<T> &operator=(Hungarian<T> &&h) noexcept {
    m_mx_og = std::move(h.m_mx_og);
    m_mx_wrk = std::move(h.m_mx_wrk);
    m_smallest_uncovered_value_from_S4 =
        std::move(h.m_smallest_uncovered_value_from_S4);
    m_primed_zero_from_S4 = std::move(h.m_primed_zero_from_S4);
    m_next_step = std::move(h.m_next_step);
    m_is_solved = std::move(h.m_is_solved);
    m_solution = std::move(h.m_solution);

    return *this;
  }

  template <typename U>
  friend std::ostream &operator<<(std::ostream &out, const Hungarian<U> &h) {
    h.PrintSolution(out);
    return out;
  }

private:
  Matrix<HungarianNotation>
  SimpleMatrixToHungarianMatrix(const Matrix<T> &simple_matrix) {
    Matrix<HungarianNotation> hungarian_matrix(simple_matrix.GetRows(),
                                               simple_matrix.GetCols());

    for (size_t cur_row{0}; cur_row < hungarian_matrix.GetRows(); ++cur_row) {
      for (size_t cur_col{0}; cur_col < hungarian_matrix.GetCols(); ++cur_col) {
        hungarian_matrix(cur_row, cur_col) = HungarianNotation{
            simple_matrix(cur_row, cur_col), false, false, false, false};
      }
    }

    return hungarian_matrix;
  }

  bool MatrixIsSquare() const {
    if (m_mx_wrk.GetRows() != m_mx_wrk.GetCols()) {
      return false;
    } else {
      return true;
    }
  }

protected:
  virtual void Step1() {
    for (size_t cur_row{0}; cur_row < m_mx_wrk.GetRows(); ++cur_row) {
      T min_value_in_cur_row{static_cast<T>(INFINITY)};
      for (size_t cur_col{0}; cur_col < m_mx_wrk.GetCols(); ++cur_col) {
        if (m_mx_wrk(cur_row, cur_col).value < min_value_in_cur_row) {
          min_value_in_cur_row = m_mx_wrk(cur_row, cur_col).value;
        }
      }

      for (size_t cur_col{0}; cur_col < m_mx_wrk.GetCols(); ++cur_col) {
        m_mx_wrk(cur_row, cur_col).value -= min_value_in_cur_row;
      }
    }

    m_next_step = 2;
  }

  virtual void Step2() {
    for (size_t cur_row{0}; cur_row < m_mx_wrk.GetRows(); ++cur_row) {
      for (size_t cur_col{0}; cur_col < m_mx_wrk.GetCols(); ++cur_col) {
        if (m_mx_wrk(cur_row, cur_col).value == 0) {
          bool starred_zero_exists_in_row_or_col{false};

          for (size_t comparison_col{0}; comparison_col < m_mx_wrk.GetCols();
               ++comparison_col) {
            if (m_mx_wrk(cur_row, comparison_col).value == 0) {
              if (m_mx_wrk(cur_row, comparison_col).is_starred == true) {
                starred_zero_exists_in_row_or_col = true;
              }
            }
          }

          for (size_t comparison_row{0}; comparison_row < m_mx_wrk.GetRows();
               ++comparison_row) {
            if (m_mx_wrk(comparison_row, cur_col).value == 0) {
              if (m_mx_wrk(comparison_row, cur_col).is_starred == true) {
                starred_zero_exists_in_row_or_col = true;
              }
            }
          }

          if (starred_zero_exists_in_row_or_col == false) {
            m_mx_wrk(cur_row, cur_col).is_starred = true;
          }
        }
      }
    }

    m_next_step = 3;
  }

  virtual void Step3() {
    size_t number_of_covered_cols{0};

    for (size_t cur_row{0}; cur_row < m_mx_wrk.GetRows(); ++cur_row) {
      for (size_t cur_col{0}; cur_col < m_mx_wrk.GetCols(); ++cur_col) {
        if (m_mx_wrk(cur_row, cur_col).value == 0) {
          if (m_mx_wrk(cur_row, cur_col).is_starred == true) {
            ++number_of_covered_cols;

            for (size_t other_row{0}; other_row < m_mx_wrk.GetRows();
                 ++other_row) {
              m_mx_wrk(other_row, cur_col).is_covered_as_col = true;
            }
          }
        }
      }
    }

    if (number_of_covered_cols == m_mx_wrk.GetRows()) {
      m_next_step = 7;
    } else {
      m_next_step = 4;
    }
  }

  virtual void Step4() {
  RestartSearchForUncoveredZero:;

    for (size_t cur_row{0}; cur_row < m_mx_wrk.GetRows(); ++cur_row) {
      for (size_t cur_col{0}; cur_col < m_mx_wrk.GetCols(); ++cur_col) {
        if (m_mx_wrk(cur_row, cur_col).value == 0) {
          if (m_mx_wrk(cur_row, cur_col).is_covered_as_row == false &&
              m_mx_wrk(cur_row, cur_col).is_covered_as_col == false) {
            m_mx_wrk(cur_row, cur_col).is_primed = true;
            m_primed_zero_from_S4 = Location2D{cur_row, cur_col};

            bool starred_zero_exists_in_row_containing_prime{false};
            Location2D starred_zero{0, 0};

            for (size_t comparison_col{0}; comparison_col < m_mx_wrk.GetCols();
                 ++comparison_col) {
              if (m_mx_wrk(cur_row, comparison_col).value == 0) {
                if (m_mx_wrk(cur_row, comparison_col).is_starred == true) {
                  starred_zero_exists_in_row_containing_prime = true;
                  starred_zero = Location2D{cur_row, comparison_col};
                  break;
                }
              }
            }

            if (starred_zero_exists_in_row_containing_prime == false) {
              m_next_step = 5;
              return;
            } else {
              for (size_t other_col{0}; other_col < m_mx_wrk.GetCols();
                   ++other_col) {
                m_mx_wrk(starred_zero.row, other_col).is_covered_as_row = true;
              }

              for (size_t other_row{0}; other_row < m_mx_wrk.GetRows();
                   ++other_row) {
                m_mx_wrk(other_row, starred_zero.col).is_covered_as_col = false;
              }

              goto RestartSearchForUncoveredZero;
            }
          }
        }
      }
    }

    m_smallest_uncovered_value_from_S4 = static_cast<T>(INFINITY);
    for (size_t cur_row{0}; cur_row < m_mx_wrk.GetRows(); ++cur_row) {
      for (size_t cur_col{0}; cur_col < m_mx_wrk.GetCols(); ++cur_col) {
        if (m_mx_wrk(cur_row, cur_col).is_covered_as_row == false &&
            m_mx_wrk(cur_row, cur_col).is_covered_as_col == false) {
          if (m_mx_wrk(cur_row, cur_col).value <
              m_smallest_uncovered_value_from_S4) {
            m_smallest_uncovered_value_from_S4 =
                m_mx_wrk(cur_row, cur_col).value;
          }
        }
      }
    }

    m_next_step = 6;
  }

  virtual void Step5() {
    Location2D cur_pos{m_primed_zero_from_S4};
    std::vector<Location2D> zeroes_in_series;
    int next_step_in_series{1};

    zeroes_in_series.push_back(m_primed_zero_from_S4);

    while (next_step_in_series != -1) {
      switch (next_step_in_series) {
      case 1:
        FindStarredZeroInCol(cur_pos, zeroes_in_series, next_step_in_series);
        break;
      case 2:
        FindPrimedZeroInRow(cur_pos, zeroes_in_series, next_step_in_series);
        break;
      }
    }

    for (size_t cur_zero{0}; cur_zero < zeroes_in_series.size(); ++cur_zero) {
      if (m_mx_wrk(zeroes_in_series[cur_zero].row,
                   zeroes_in_series[cur_zero].col)
              .is_starred == true) {
        m_mx_wrk(zeroes_in_series[cur_zero].row, zeroes_in_series[cur_zero].col)
            .is_starred = false;
      } else if (m_mx_wrk(zeroes_in_series[cur_zero].row,
                          zeroes_in_series[cur_zero].col)
                     .is_primed == true) {
        m_mx_wrk(zeroes_in_series[cur_zero].row, zeroes_in_series[cur_zero].col)
            .is_starred = true;
      }
    }

    for (size_t cur_row{0}; cur_row < m_mx_wrk.GetRows(); ++cur_row) {
      for (size_t cur_col{0}; cur_col < m_mx_wrk.GetCols(); ++cur_col) {
        m_mx_wrk(cur_row, cur_col).is_primed = false;
        m_mx_wrk(cur_row, cur_col).is_covered_as_row = false;
        m_mx_wrk(cur_row, cur_col).is_covered_as_col = false;
      }
    }

    m_next_step = 3;
  }
  void FindStarredZeroInCol(Location2D &cur_pos,
                            std::vector<Location2D> &zeroes_in_series,
                            int &next_step_in_series) {
    bool starred_zero_exists_in_col{false};

    for (size_t other_row{0}; other_row < m_mx_wrk.GetRows(); ++other_row) {
      if (m_mx_wrk(other_row, cur_pos.col).value == 0) {
        if (m_mx_wrk(other_row, cur_pos.col).is_starred == true) {
          starred_zero_exists_in_col = true;

          cur_pos = Location2D{other_row, cur_pos.col};
          zeroes_in_series.push_back(cur_pos);

          break;
        }
      }
    }

    if (starred_zero_exists_in_col == true) {
      next_step_in_series = 2;
    } else {
      next_step_in_series = -1;
    }
  }

  void FindPrimedZeroInRow(Location2D &cur_pos,
                           std::vector<Location2D> &zeroes_in_series,
                           int &next_step_in_series) {
    for (size_t other_col{0}; other_col < m_mx_wrk.GetCols(); ++other_col) {
      if (m_mx_wrk(cur_pos.row, other_col).value == 0) {
        if (m_mx_wrk(cur_pos.row, other_col).is_primed == true) {
          cur_pos = Location2D{cur_pos.row, other_col};
          zeroes_in_series.push_back(cur_pos);

          break;
        }
      }
    }

    next_step_in_series = 1;
  }

  virtual void Step6() {
    for (size_t cur_row{0}; cur_row < m_mx_wrk.GetRows(); ++cur_row) {
      for (size_t cur_col{0}; cur_col < m_mx_wrk.GetCols(); ++cur_col) {
        if (m_mx_wrk(cur_row, cur_col).is_covered_as_row == true) {
          m_mx_wrk(cur_row, cur_col).value +=
              m_smallest_uncovered_value_from_S4;
        }

        if (m_mx_wrk(cur_row, cur_col).is_covered_as_col == false) {
          m_mx_wrk(cur_row, cur_col).value -=
              m_smallest_uncovered_value_from_S4;
        }
      }
    }

    m_next_step = 4;
  }

  virtual void Step7() {
    for (size_t cur_row{0}; cur_row < m_mx_wrk.GetRows(); ++cur_row) {
      for (size_t cur_col{0}; cur_col < m_mx_wrk.GetCols(); ++cur_col) {
        if (m_mx_wrk(cur_row, cur_col).value == 0) {
          if (m_mx_wrk(cur_row, cur_col).is_starred == true) {
            m_solution.values.push_back(Value2D{m_mx_og(cur_row, cur_col).value,
                                                Location2D{cur_row, cur_col}});
          }
        }
      }
    }

    for (size_t cur_value{0}; cur_value < m_solution.values.size();
         ++cur_value) {
      m_solution.sum += m_solution.values[cur_value].value;
    }

    m_next_step = 0;
  }
};

} // namespace hungarian_cpp
#endif

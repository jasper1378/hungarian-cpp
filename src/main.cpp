/* vim: set filetype=cpp : */

// Hungarian Algorithm guide used: https://brc2.com/the-algorithm-workshop/

#include "arg_parser.hpp"
#include "hungarian.hpp"
#include "io.hpp"
#include "matrix.hpp"
#include "matrix_helpers.hpp"
#include "timed_hungarian.hpp"

#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

int main(int argc, char *argv[]) {
  using data_t = signed long long int;

  try {
    std::vector<ArgParser::ValidName> valid_names{
        {{"-h", "--help"}, false},
        {{"-bm", "--benchmark"}, false},
        {{"-if", "--input-file"}, true},
        {{"-si", "--standard-input"}, false},
        {{"-rm", "--random-matrix"}, true}};
    const ArgParser arg_parser{argc, argv, std::move(valid_names)};

    if (arg_parser.ArgExists("-h")) {
      PrintHelp();
      return 0;
    }

    std::unique_ptr<Hungarian<data_t>> hungarian{nullptr};

    Matrix<data_t> matrix;

    if (arg_parser.ArgExists("-if")) {
      matrix = ReadMatrixFromFile<data_t>(arg_parser.GetValue("-if"));
    } else if (arg_parser.ArgExists("-si")) {
      matrix = ReadMatrixFromStdin<data_t>();
    } else if (arg_parser.ArgExists("-rm")) {
      int size = std::stoi(arg_parser.GetValue("-rm"));
      if (size <= 0) {
        throw std::runtime_error{"size should be a positive integer"};
      } else {
        matrix =
            GenerateRandomMatrix<data_t>(std::stoi(arg_parser.GetValue("-rm")));
      }
    } else {
      throw std::runtime_error{
          "please specify an operation, try \"hungarian-cpp --help\""};
    }

    if (arg_parser.ArgExists("-bm")) {
      hungarian = std::make_unique<TimedHungarian<data_t>>(std::move(matrix));
    } else {
      hungarian = std::make_unique<Hungarian<data_t>>(std::move(matrix));
    }

    hungarian->Solve();
    std::cout << *hungarian;
  } catch (const std::exception &exception) {
    std::cerr << "Error: " << exception.what() << '\n';
    return 1;
  } catch (...) {
    std::cerr << "Unknown Error" << '\n';
    return 1;
  }

  return 0;
}

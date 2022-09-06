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
#include <stdexcept>
#include <vector>

int main(int argc, char* argv[])
{
    using data_t = signed long long int;

    try
    {
        ArgParser arg_parser{ argc, argv, { { {"hungarian-cpp", "./hungarian-cpp"}, false}, { { "-h", "--help" }, false }, { { "-bm", "--benchmark" }, false }, { { "-if", "--input-file" }, true }, { { "-si", "--standard-input" }, false }, { { "-rm", "--random-matrix"}, true }, { { "../hungarian-cpp", "TEMPORARY" }, false} } };

        if (arg_parser.ArgExists("-h"))
        {
            PrintHelp();
            return 0;
        }

        Hungarian<data_t>* hungarian;
        Matrix<data_t> matrix;

        if (arg_parser.ArgExists("-if"))
        {
            matrix = ReadMatrixFromFile<data_t>(arg_parser.GetValue("-if"));
        }
        else if (arg_parser.ArgExists("-si"))
        {
            matrix = ReadMatrixFromStdin<data_t>();
        }
        else if (arg_parser.ArgExists("-rm"))
        {
            matrix = GenerateRandomMatrix<data_t>(std::stoi(arg_parser.GetValue("-rm")));
        }
        else
        {
            throw std::runtime_error{ "please specify an operation, try \"hungarian-cpp --help\"" };
        }

        if (arg_parser.ArgExists("-bm"))
        {
            hungarian = new TimedHungarian<data_t>{ matrix };
        }
        else
        {
            hungarian = new Hungarian<data_t>{ matrix };
        }

        hungarian->Solve();
        std::cout << *hungarian;

        delete hungarian;
        hungarian = nullptr;
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Error: " << exception.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown Error" << '\n';
        return 1;
    }

    return 0;
}

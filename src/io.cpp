#include "io.hpp"

#include <iostream>

void PrintHelp()
{
    std::cout << "Jasper's Implementation of the Hungarian Algorithm\n";
    std::cout << "Following the steps outlined here: https://brc2.com/the-algorithm-workshop\n";
    std::cout << '\n';

    std::cout << "Usage: hungarian-cpp [options]\n";
    std::cout << "Options:\n";
    std::cout << '\n';

    std::cout << "\t-h\n";
    std::cout << "\t--help\n";
    std::cout << "\tWill print this help message.\n";
    std::cout << '\n';

    std::cout << "\t-if \"file.txt\"\n";
    std::cout << "\t--input-file \"file.txt\"\n";
    std::cout << "\tSpecify a file to read a matrix from. Make sure that each column is separated by a space and that each row is separated by a newline.\n";
    std::cout << '\n';

    std::cout << "\t-si\n";
    std::cout << "\t--standard-input\n";
    std::cout << "\tRead matrix from stdin. Make sure that each column is separated by a space and that each row is separated by a newline. Finish your input by inputting \"end of file\" (Ctrl-D on Unix).\n";
    std::cout << '\n';

    std::cout << "\t-rm X\n";
    std::cout << "\t--random-matrix X\n";
    std::cout << "\tGenerate a random matrix of size X.\n";
    std::cout << '\n';

    std::cout << "\t-bm\n";
    std::cout << "\t--benchmark\n";
    std::cout << "\tPrint a benchmark report for the algorithm after printing the solution.\n";
    std::cout << '\n';

    std::cout << "Bugs can be reported to:\n";
    std::cout << "jasper.c.young@gmail.com\n";
}

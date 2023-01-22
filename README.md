# hungarian-cpp

## About
An implementation of the Hungarian (Kuhn-Munkres) algorithm written in C++. Originally written for [this](https://www.reddit.com/r/dailyprogrammer/comments/oirb5v/20210712_challenge_398_difficult_matrix_sum/?utm_source=share&utm_medium=web2x&context=3) programming challenge (see [question.md](question.md) for details). 

## Installation
Acquire the sources
```
$ git clone https://github.com/jasper1378/hungarian-cpp.git
$ cd hungarian-cpp
```
Build
```
$ make
```
Install
```
$ make install
```

## Usage
```
Usage: hungarian-cpp [options]
Options:

	-h
	--help
	Will print this help message.

	-if "file.txt"
	--input-file "file.txt"
	Specify a file to read a matrix from. Make sure that each column is separated by a space and that each row is separated by a newline.

	-si
	--standard-input
	Read matrix from stdin. Make sure that each column is separated by a space and that each row is separated by a newline. Finish your input by inputting "end of file" (Ctrl-D on Unix).

	-rm X
	--random-matrix X
	Generate a random matrix of size X.

	-bm
	--benchmark
	Print a benchmark report for the algorithm after printing the solution.
```

## License
See [LICENSE.md](LICENSE.md) for details.

# Benchmark of Python-C++ bindings

A project to measure overhead of Python bindings for C++ codebase, using simple test scenarios -- generation of Mandelbrot set image and simulation of Conway’s Game Of Life. Tested modules include: CPython API, cppyy, Cython, CFFI, pybind11, nanobind, SWIG.

Write-up and results: https://yanto.fi/2022/09/benchmark-of-python-c-bindings/

## Installation

These instructions were tested on Ubuntu 22.04.

Install pre-requisites:

```sh
# System dependencies
$ sudo apt install python3.10-dev pypy3
$ python3 -m pip install cppyy cffi Cython swig
$ pypy3 -m pip install cppyy cffi Cython

# Submodule dependencies
$ git submodule update --init --recursive

# Optional dependencies for generating result plots
$ sudo apt install python3-pip python3-tk
$ pip3 install matplotlib
```

To run the benchmark:

```sh
# Runs cmake to create a clean build
$ ./build.sh

# Runs through each available/configured test
$ ./benchmark.sh
mandelbrot, single, cpp, 0.345 sec
mandelbrot, simple, cpp, 0.351 sec
mandelbrot, complex, cpp, 0.329 sec
mandelbrot, single, cpy_cython, 0.396 sec
mandelbrot, simple, cpy_cython, 0.748 sec
mandelbrot, complex, cpy_cython, 0.973 sec
...
```

To generate plots:

```sh
# Do a clean build and run ./becnhmark.sh multiple times
python3 ./collect_and_plot.py
```

To debug python, install and use `/usr/bin/python3.10-dgb` as the interpreter.

```
$ sudo apt install python3.10-dbg
```


## License

This project is licensed under the the [MIT license](LICENSE.md) - see the [LICENSE.md](LICENSE.md) file for details.

# Matrix

Simple matrix implementation for determinant counting.

## Dependencies

Compiler c/c++, cmake, gtest

```shell
apt-get install build-essential clang make cmake
apt-get install libgtest-dev libgmock-dev libtbb-dev
```

## Building

```shell
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build
```

Binaries are located in `build/source/` and `build/tests`

## Usage

Format of input (stdin): matrix size, next - matrix elements

```
3
1.0 -6 90
4 5 0
67.98 0 -7
```

Format of output: matrix's determinant

```
-30794
```

## Tests

For run end to end tests do:

```shell
./build/tests/e2eTests
```

or unit tests:

```
./build/tests/unitTests
```
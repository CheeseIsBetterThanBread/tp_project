#!/bin/bash

rm -r build
rm -r bin
rm -r lib
mkdir -p build
cd build || exit

cmake ..
cmake --build .

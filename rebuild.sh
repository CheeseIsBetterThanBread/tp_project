#!/bin/bash

rm -r build
rm -r bin
rm -r lib
mkdir -p build
cd build || exit

if [[ ($@ == *'--test'*) ]]
then
  cmake -DCMAKE_BUILD_TYPE=Debug ..
  cmake --build . --target tests
else
  cmake ..
  cmake --build .
fi
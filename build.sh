#!/bin/bash

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
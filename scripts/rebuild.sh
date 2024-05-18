#!/bin/bash

rm -r build
rm -r bin
rm -r lib
rm -r logging

mkdir -p logging
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
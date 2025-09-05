#! /bin/bash

rm -rf bin
mkdir bin
cd bin
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
cd ..
./bin/MAIN
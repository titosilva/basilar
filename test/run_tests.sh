#!/bin/bash 

cmake -S . -B ../build-test
cmake --build ../build-test
cd ../build-test && ctest --output-on-failure --stop-on-failure
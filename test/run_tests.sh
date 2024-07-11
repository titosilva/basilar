#!/bin/bash 

echo "Building and running tests" && \
    cmake -S . -B ../build-test && \
    cmake --build ../build-test && \
    cd ../build-test && \
    ctest --output-on-failure
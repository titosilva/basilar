#!/bin/bash

for file in samples/erros/*.asm; do
    ./montador -o $file
done
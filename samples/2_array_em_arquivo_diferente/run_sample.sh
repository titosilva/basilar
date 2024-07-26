#!/bin/bash 

./montador -p samples/2_array_em_arquivo_diferente/array_1.asm
./montador -p samples/2_array_em_arquivo_diferente/array_2.asm
./montador -o samples/2_array_em_arquivo_diferente/array_1.pre
./montador -o samples/2_array_em_arquivo_diferente/array_2.pre
./ligador samples/2_array_em_arquivo_diferente/array_2.obj samples/2_array_em_arquivo_diferente/array_1.obj

python3 samples/simulador/simulador.py samples/2_array_em_arquivo_diferente/array_2.e
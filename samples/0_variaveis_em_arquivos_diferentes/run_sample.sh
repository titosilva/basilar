#!/bin/bash 

./montador -p samples/0_variaveis_em_arquivos_diferentes/ligador_vars_1.asm
./montador -p samples/0_variaveis_em_arquivos_diferentes/ligador_vars_2.asm
./montador -o samples/0_variaveis_em_arquivos_diferentes/ligador_vars_1.pre
./montador -o samples/0_variaveis_em_arquivos_diferentes/ligador_vars_2.pre
./ligador samples/0_variaveis_em_arquivos_diferentes/ligador_vars_1.obj samples/0_variaveis_em_arquivos_diferentes/ligador_vars_2.obj

python3 samples/simulador/simulador.py samples/0_variaveis_em_arquivos_diferentes/ligador_vars_1.e
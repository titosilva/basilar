#!/bin/bash 

./montador -p samples/1_entrada_e_saida_em_arquivos_diferentes/ligador_io_1.asm
./montador -p samples/1_entrada_e_saida_em_arquivos_diferentes/ligador_io_2.asm
./montador -o samples/1_entrada_e_saida_em_arquivos_diferentes/ligador_io_1.pre
./montador -o samples/1_entrada_e_saida_em_arquivos_diferentes/ligador_io_2.pre
./ligador samples/1_entrada_e_saida_em_arquivos_diferentes/ligador_io_2.obj samples/1_entrada_e_saida_em_arquivos_diferentes/ligador_io_1.obj

python3 samples/simulador/simulador.py samples/1_entrada_e_saida_em_arquivos_diferentes/ligador_io_2.e
# Basilar - montador de uma linguagem assembly simbólica

## Identificação
- Nome: João Tito do Nascimento Silva
- Matrícula: 18/0123301
- Sistema Operacional: Ubuntu 20.04.6 LTS (focal)

## Instruções de uso
Antes de qualquer coisa, é necessário ter o compilador g++ e o make instalados na máquina. Execute o comando

`make clean`

Para executar o código, primeiro realize a compilação utilizando o comando

`make montador`

Em seguida, execute o montador em modo de pré-processamento com o comando

`./montador -p <arquivo de entrada>`

Para executar o montador em modo de montagem, utilize o comando

`./montador -o <arquivo de entrada>`

O montador irá gerar um arquivo de saída com o mesmo nome do arquivo de entrada, porém com a extensão .pre ou .obj, dependendo do modo de execução.
Para compilar o ligador, utilize o comando

`make ligador`

Em seguida, execute o ligador com o comando

`./ligador <arquivo de entrada> <arquivo de entrada>`

O ligador irá gerar um arquivo de saída com o mesmo nome do arquivo de entrada, porém com a extensão .e.
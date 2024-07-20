# Basilar - montador de uma linguagem assembly simbólica

## Dúvidas
1. A substitução realizada pelo pré-processador deve ser realizada em qualquer match em qualquer lugar de uma linha? Basta separar os tokens por espaço?
2. A diretiva "equ" deve aceitar strings e números?

## TODOs
- Renomear a pasta "flow/tokenizer" para "flow/line_reader"
- Renomear namespace "basilar::tokens"
- Renomear namespace "basilar::tokenizer"
- Remover parâmetros desnecessários dos métodos de Preprocessor
- VERIFICAR TODOs EM TODOS OS ARQUIVOS
- Remover esses TODOs
- Escrever instruções de compilação. Lembrar de adicionar um "make clean".
- Tratar linhas que definem labels e instruções em linhas diferentes (incluindo pré-processamento)
- Implementar expressões aritméticas em labels
- Fazer compilação do zero e remover warnings
- Adicionar caso de teste para extern redefinido como public

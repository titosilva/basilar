# Basilar - montador de uma linguagem assembly simbólica

## Dúvidas
1. A substitução realizada pelo pré-processador deve ser realizada em qualquer match em qualquer lugar de uma linha? Basta separar os tokens por espaço?
2. A diretiva "equ" deve aceitar strings e números?

## TODOs
- Renomear a pasta "flow/tokenizer" para "flow/line_reader"
- Renomear namespace "basilar::tokens"
- Renomear namespace "basilar::tokenizer"
- Remover parâmetros desnecessários dos métodos de Preprocessor
- Escrever instruções de compilação. Lembrar de adicionar um "make clean".
- Ver comentários no Aprender com calma

- Implementar expressões aritméticas em labels
    * Obs.: quando for label externa, escrever o tanto que é somado para auxiliar na resolução do ligador
- Tratar linhas que definem labels e instruções em linhas diferentes (incluindo pré-processamento)
- Adequar as entradas do programa à especificação
- Usar equ como substituição de labels (não consegui fazer no samples 2)
- Adicionar verificação de labels indefinidas
- Melhorar exibição de casos de erro e testar com casos de erro da especificação
- Implementar suporte a hexadecimal onde necessário

- Adicionar caso de teste para extern redefinido como public
- Fazer compilação do zero e remover warnings
- VERIFICAR TODOs EM TODOS OS ARQUIVOS
- Remover esses TODOs
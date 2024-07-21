# Basilar - montador de uma linguagem assembly simbólica

## TODOs
- [ OK ] Implementar expressões aritméticas em labels
    * Obs.: quando for label externa, escrever o tanto que é somado para auxiliar na resolução do ligador
- Tratar linhas que definem labels e instruções em linhas diferentes (incluindo pré-processamento)
- Adequar as entradas do programa à especificação
- Adicionar verificação de labels indefinidas
- Melhorar exibição de casos de erro e testar com casos de erro da especificação
- Implementar suporte a hexadecimal onde necessário
- Ver comentários no Aprender com calma
- Escrever instruções de compilação. Lembrar de adicionar um "make clean".

- Usar equ como substituição de labels (não consegui fazer no samples 2)
- Adicionar caso de teste para extern redefinido como public
- Fazer compilação do zero e remover warnings
- VERIFICAR TODOs EM TODOS OS ARQUIVOS
- Remover esses TODOs

- Renomear a pasta "flow/tokenizer" para "flow/line_reader"
- Renomear namespace "basilar::tokens"
- Renomear namespace "basilar::tokenizer"
- Remover parâmetros desnecessários dos métodos de Preprocessor
- Tratar instruções "sobrando" fora de begin e end?
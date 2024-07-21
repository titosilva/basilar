# Basilar - montador de uma linguagem assembly simbólica

## TODOs
- [ OK ] Implementar expressões aritméticas em labels
    * Obs.: quando for label externa, escrever o tanto que é somado para auxiliar na resolução do ligador
- [ OK ] Tratar linhas que definem labels e instruções em linhas diferentes (incluindo pré-processamento)
- [ OK ] Adequar as entradas do programa à especificação
- [ TEST ] Adicionar verificação de labels indefinidas
- [ TEST ] Implementar suporte a hexadecimal onde necessário
- Ver comentários no Aprender com calma
- Melhorar exibição de casos de erro
- Implementar casos de erro da especificação
- [ OK ] Remover chamadas no iostream
- Fazer compilação do zero e remover warnings
- Escrever instruções de compilação. Lembrar de adicionar um "make clean".
- Testar tudo com o simulador fornecido

- Usar equ como substituição de labels (não consegui fazer no samples 2)
- Adicionar caso de teste para extern redefinido como public
- [ OK ] VERIFICAR TODOs EM TODOS OS ARQUIVOS

- Renomear a pasta "flow/tokenizer" para "flow/line_reader"
- Renomear namespace "basilar::tokens"
- Renomear namespace "basilar::tokenizer"
- Remover parâmetros desnecessários dos métodos de Preprocessor
- Tratar instruções "sobrando" fora de begin e end?

- Remover esses TODOs
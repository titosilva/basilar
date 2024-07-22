MOD1:   begin
gasto:  extern
saldo:  extern
        load saldoso
        sub gasto
        sub gasto +     1
        sub gasto         + 2
        sub gasto+3
        store saldoso
        jmpp pos
        jmpn neg
        output saldo
        jmp finish

pos:    output saldo
        jmp finish

neg:    output saldo
        jmp finish

    finish:             stop
zero:                   const 0
public mod1
end
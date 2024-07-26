MOD1:   begin
saldo:  extern
        load saldo
        sub gasto
        sub gasto +     1
        sub gasto         + 2

        sub gasto+3
        store saldo
        jmpp pos
        jmpn neg
        output saldo
        
        jmp finish

gasto: gasto:  extern
pos:    output saldo
        jmp finish

neg:    output saldo
        jmp finish

    finish:             stop
zero:                   const 0
public mod1
end
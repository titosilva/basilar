MOD1:   begin
gasto:  extern
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

pos:    output saldo
        jmp finish

neg:    output saldo
        jmp finish

; ERRO =======================
    1finish:             stop
; ============================
zero:                   const 0
public mod1
end
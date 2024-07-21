to_neg:       equ 1
to_pos:       equ 0
to_zero:      equ 0
gasto_size:     equ 4

        public saldo
public      gasto

mod2: begin
if to_neg
copy zero,saldo

if to_pos
copy mega,saldo


copy    cinco,gasto + 0x3
copy    seis,gasto +     0x1
copy    sete,gasto      + 0x2

if to_zero
copy soma,saldo
copy    tres,gasto + 0x0
jmp other

zero:           const 0
tres:   const 3
cinco:  const 5
seis:   const 6
sete:   const 7
soma:  const 21
mega:                   const       100

other: jmp mod1
saldo: SpAcE

gasto:          Space     4
mod1: extern
end
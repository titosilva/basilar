test: equ 0
label: equ 1

if test
add r1 r2 ; This is a commentary

; This is a commented line
if 0
add r2 r3

; sub r3 r4
if 1
add r4 r5


; Test
if label
sub r1 r2 ; to keep

sub r2 r3

if 32
add r4 r5
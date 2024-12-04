.include "../includeConstantesARM64.inc"
.equ SHA_DIGEST_LENGTH, 20

.data
szMessRosetta: .asciz "Rosetta Code"
szMessTest1: .asciz "abc"
szMessSup64: .ascii "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            .ascii "abcdefghijklmnopqrstuvwxyz"
            .asciz "1234567890AZERTYUIOP"
szMessTest2: .asciz "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
szMessFinPgm: .asciz "Program End ok.\n"
szMessResult: .asciz "Rosetta Code => "
szCarriageReturn: .asciz "\n"

tbConstHi: .int 0x67452301 
            .int 0xEFCDAB89
            .int 0x98BADCFE
            .int 0x10325476
            .int 0xC3D2E1F0
tbConstKt:  .int 0x5A827999
            .int 0x6ED9EBA1
            .int 0x8F1BBCDC
            .int 0xCA62C1D6

.bss
.align 4
iNbBlocs: .skip 8
sZoneConv: .skip 24
sZoneResult: .skip 24
sZoneTrav: .skip 1000
tbH: .skip 4 * 5
tbW: .skip 4 * 80
.text
.global main

main:
    ldr x0, qAdrszMessRosetta
    bl computeSHA1

    ldr x0, qAdrszMessResult
    bl affichageMess

    ldr x0, qAdrsZoneResult
    bl displaySHA1

    ldr x0, qAdrszMessFinPgm
    bl affichageMess

100:
    mov x0, 0
    mov x8, EXIT
    svc 0

qAdrszCarriageReturn: .quad szCarriageReturn
qAdrszMessResult: .quad szMessResult
qAdrszMessRosetta: .quad szMessRosetta
qAdrszMessTest1: .quad szMessTest1
qAdrszMessTest2: .quad szMessTest2
qAdrsZoneTrav: .quad sZoneTrav
qAdrsZoneConv: .quad sZoneConv
qAdrszMessFinPgm: .quad szMessFinPgm
qAdrszMessSup64: .quad szMessSup64

computeSHA1:
    stp x1,lr,[sp,-16]!
    ldr x1,qAdrsZoneTrav
    mov x2,#0
debCopy:
    ldrb w3,[x0,x2]
    strb w3,[x1,x2]
    cmp x3,#0
    add x4,x2,1
    csel x2,x4,x2,ne
    bne debCopy
    lsl x6,x2,#3
    mov x3,#0b10000000
    strb w3,[x1,x2]
    add x2,x2,#1
    lsl x4,x2,#3
    mov x3,#0
addZeroes:
    lsr x5,x2,#6
    lsl x5,x5,#6
    sub x5,x2,x5
    cmp x5,#56
    beq storeLength
    strb w3,[x1,x2]
    add x2,x2,#1
    add x4,x4,#8
    b addZeroes
storeLength:
    add x2,x2,#4
    rev w6,w6
    str w6,[x1,x2]

    ldr x7,qAdrtbConstHi
    ldr x4,qAdrtbH
    mov x5,#0
loopConst:
    ldr w6,[x7,x5,lsl #2]
    str w6,[x4,x5,lsl #2]
    add x5,x5,#1
    cmp x5,#5
    blt loopConst

    add x2,x2,#4
    lsr x4,x2,#6
    ldr x0,qAdriNbBlocs
    str x4,[x0]
    mov x7,#0
loopBlock:
    mov x0,x7
    bl inversion
    ldr x3, qAdrtbW
    mov x6,#0

    ldr x1,qAdrsZoneTrav
    add x2,x1,x7,lsl #6
loopPrep:
    cmp x6,#15
    bgt expand1
    ldr w0,[x2,x6,lsl #2]
    str w0,[x3,x6,lsl #2]
    b expandEnd
expand1:
    sub x8,x6,#3
    ldr x9,[x3,x8,lsl #2]
    sub x8,x6,#8
    ldr w10,[x3,x8,lsl #2]
    eor x9,x9,x10
    sub x8,x6,#14
    ldr w10,[x3,x8,lsl #2]
    eor x9,x9,x10
    sub x8,x6,#16
    ldr w10,[x3,x8,lsl #2]
    eor x9,x9,x10
    ror w9,w9,#31
    str w9,[x3,x6,lsl #2]
expandEnd:
    add x6,x6,#1
    cmp x6,#80
    blt loopPrep

    ldr x0,qAdrtbH
    ldr w8,[x0]
    ldr w9,[x0,#4]
    ldr w10,[x0,#8]
    ldr w11,[x0,#12]
    ldr w12,[x0,#16]

    ldr x1,qAdrtbConstHi
    ldr x5,qAdrtbConstKt
    mov x6,#0
loop80T:
    cmp x6,#19
    bgt T2
    ldr w0,[x5]
    and x2,x9,x10
    mvn w4,w9
    and x4,x4,x11
    orr x2,x2,x4
    b T_fin
T2:
    cmp x6,#39
    bgt T3
    ldr w0,[x5,#4]
    eor x2,x9,x10
    eor x2,x2,x11
    b T_fin
T3:
    cmp x6,#59
    bgt T4
    ldr w0,[x5,#8]
    and x2,x9,x10
    and x4,x9,x11
    orr x2,x2,x4
    and x4,x10,x11
    orr x2,x2,x4
    b T_fin
T4:
    ldr w0,[x5,#12]
    eor x2,x9,x10
    eor x2,x2,x11
    b T_fin
T_fin:
    ror w4,w8,#27
    add w2,w2,w4

    add w2,w2,w12
    ldr w4,[x3,x6,lsl #2]
    add w2,w2,w4
    add w2,w2,w0
    mov x12,x11
    mov x11,x10
    ror w10,w9,#2
    mov x9,x8
    mov x8,x2

    add x6,x6,#1
    cmp x6,#80
    blt loop80T

    add x7,x7,1
    ldr x0,qAdriNbBlocs
    ldr w4,[x0]
    cmp x7,x4
    bge End

    ldr x0,qAdrtbH
    ldr w3,[x0]
    add w3,w3,w8
    str w3,[x0]
    ldr w3,[x0,#4]
    add w3,w3,w9
    str w3,[x0,#4]
    ldr w3,[x0,#8]
    add w3,w3,w10
    str w3,[x0,#8]
    ldr w3,[x0,#12]
    add w3,w3,w11
    str w3,[x0,#12]
    ldr w3,[x0,#16]
    add w3,w3,w12
    str w3,[x0,#16]
    b loopBlock

End:
    ldr x0,qAdrtbH
    ldr x2,qAdrsZoneResult
    ldr w1,[x0]
    add x1,x1,x8
    rev w1,w1
    str w1,[x2]
    ldr w1,[x0,#4]
    add x1,x1,x9
    rev w1,w1
    str w1,[x2,#4]
    ldr w1,[x0,#8]
    add x1,x1,x10
    rev w1,w1
    str w1,[x2,#8]
    ldr w1,[x0,#12]
    add x1,x1,x11
    rev w1,w1
    str w1,[x2,#12]
    ldr w1,[x0,#16]
    add x1,x1,x12
    rev w1,w1
    str w1,[x2,#16]
    mov x0,#0
100:
    ldp x1,lr,[sp],16
    ret

qAdrtbConstHi: .quad tbConstHi
qAdrtbConstKt: .quad tbConstKt
qAdrtbH: .quad tbH
qAdrtbW: .quad tbW
qAdrsZoneResult: .quad sZoneResult
qAdriNbBlocs: .quad iNbBlocs

inversion:
    stp x1,lr,[sp,-16]!
    stp x2,x3,[sp,-16]!
    ldr x1,qAdrsZoneTrav
    add x1,x1,x0,lsl 6
    mov x2,#0
1:
    ldr w3,[x1,x2,lsl #2]
    rev w3,w3
    str w3,[x1,x2,lsl #2]
    add x2,x2,#1
    cmp x2,#16
    blt 1b
100:
    ldp x2,x3,[sp],16
    ldp x1,lr,[sp],16
    ret

displaySHA1:
    stp x1,lr,[sp,-16]!
    stp x2,x3,[sp,-16]!
    mov x3,x0
    mov x2,#0
1:
    ldr w0,[x3,x2,lsl #2]
    rev w0,w0
    ldr x1,qAdrsZoneConv
    bl conversion16_4W
    ldr x0, qAdrsZoneConv
    bl affichageMess
    add x2,x2,#1
    cmp x2,#SHA_DIGEST_LENGTH / 4
    blt 1b
    ldr x0,qAdrszCarriageReturn
    bl affichageMess
100:
    ldp x2,x3,[sp],16
    ldp x1,lr,[sp],16
    ret

conversion16_4W:
    stp x0,lr,[sp,-48]!
    stp x1,x2,[sp,32]
    stp,x3,x4,[sp,16]
    mov x2,#28
    mov x4,#0xF0000000
    mov x3,x0
1:
    and x0,x3,x4
    lsr x0,x0,x2
    cmp x0,#10
    bge 2f
    add x0,x0,#48
    b 3f
2:
    add x0,x0,#55
3:
    strb w0,[x1],#1
    lsr x4,x4,#4
    subs x2,x2,#4
    bge 1b
100:
    ldp x3,x4,[sp,16]
    ldp x1,x2,[sp,32]
    ldp x0,lr,[sp],48
    ret

.include "../includeARM64.inc"
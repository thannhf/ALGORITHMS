.include "../includeConstantesARM64.inc"
.equ MAXI, 63

.data
sMessResult: .asciz "Perfect : @ \n"
szMessOverflow: .asciz "Overflow in function isPrime.\n"
szCarriageReturn .asciz "\n"

.bss
sZoneConv: .skip 24

.text
.global main

main:
    mov x4,2
    mov x3,1

1:
    lsl x4,x4,1
    sub x0,x4,1
    bl isPrime
    cbz x0,2f
    sub x0,x4,1
    mul x1,x0,x4
    lsr x0,x1,1
    bl displayPerfect

2:
    add x3,x3,1
    cmp x3,MAXI
    blt 1b

100:
    mov x0,0
    mov x8,EXIT
    svc 0

qAdrszCarriageReturn: .quad szCarriageReturn
qAdrsMessResult: .quad sMessResult

displayPerfect:
    stp x1,lr,[sp,-16]!
    ldr x1,qAdrsZoneConv
    bl conversion10
    ldr x0,qAdrsMessResult
    ldr x1,qAdrsZoneConv
    bl strInsertAtCharInc
    bl affichageMess

100:
    ldp x1,lr,[sp],16
    ret

qAdrsZoneConv: .quad sZoneConv

isPrime:
    stp x1,lr,[sp,-16]!
    stp x2,x3,[sp,-16]!
    mov x2,x0
    sub x1,x0,#1
    cmp x2,0
    beq 99f
    cmp x2,2
    ble 2f
    mov x0,#2
    bl moduloPuR64
    bcs 100f
    cmp x0,#1
    bne 99f
    cmp x2,3
    beq 2f
    mov x0,#3
    bl moduloPuR64
    blt 100f
    cmp x0,#1
    bne 99f

    cmp x2,5
    beq 2f
    mov x0,#5
    bl moduloPuR64
    bcs 100f
    cmp x0,#1
    bne 99f

    cmp x2,7
    beq 2f
    mov x0,#7
    bl moduloPuR64
    bcs 100f
    cmp x0,#1
    bne 99f

    cmp x2,11
    beq 2f
    mov x0,#11
    bl moduloPuR64
    bcs 100f
    cmp x0,#1
    bne 99f

    cmp x2,13
    beq 2f
    mov x0,#13
    bl moduloPuR64
    bcs 100f
    cmp x0,#1
    bne 99f

2:
    cmn x0,0
    mov x0,1
    b 100f

99:
    cmn x0,0
    mov x0,#0

100:
    ldp x2,x3,[sp],16
    ldp x1,lr,[sp],16
    ret

moduloPuR64:
    stp x1,lr,[sp,-16]!
    stp x3,x4,[sp,-16]!
    stp x5,x6,[sp,-16]!
    stp x7,x8,[sp,-16]!
    stp x9,x10,[sp,-16]!
    cbz x0,100f
    cbz x1,100f
    mov x8,x0
    mov x7,x10
    mov x6,1
    udiv x4,x8,x2
    msub x9,x4,x2,x8

1:
    tst x7,1
    beq 2f
    mul x4,x9,x6
    umulh x5,x9,x6
    mov x6,x4
    mov x0,x6
    mov x1,x5
    bl divisionReg128U
    cbnz x1,99f
    mov x6,x3

2:
    mul x8,x9,x9
    umulh x5,x9,x9
    mov x0,x8
    mov x1,x5
    bl divisionReg128U
    cbnz x1,99f
    mov x9,x3
    lsr x7,x7,1
    cbnz x7,1b
    mov x0,x6
    cmn x0,0
    b 100f

99:
    ldr x0,qAdrszMessOverflow
    bl affichageMess
    cmp x0,0
    mov x0,-1

100:
    ldp x9,x10,[sp],16
    ldp x7,x8,[sp],16
    ldp x5,x6,[sp],16
    ldp x3,x4,[sp],16
    ldp x1,lr,[sp],16
    ret

qAdrszMessOverflow: .quad szMessOverflow

divisionReg128U:
    stp x6,lr,[sp,-16]!
    stp x4,x5,[sp,-16]!
    mov x5,#0
    mov x3,#128
    mov x4,#0

1:
    lsl x5,x5,#1
    tst x1,1<<63
    lsl x1,x1,#1
    beq 2f
    orr x5,x5,#1

2:
    tst x0,1<<63
    lsl x0,x0,#1
    beq 3f
    orr x1,x1,#1

3:
    orr x0,x0,x4
    mov x4,#0
    cmp x5,x2
    blt 4f
    sub x5,x5,x2
    mov x4,#1

4:
    subs x3,x3,#1
    bgt 1b
    lsl x1,x1,#1
    tst x0,1<<63
    lsl x0,x0,#1
    beq 5f
    orr x1,x1,#1

5:
    orr x0,x0,x4
    mov x3,x5

100:
    ldp x4,x5,[sp],16
    ldp x6,lr,[sp],16
    ret

.include "../includeARM64.inc"
.include "../includeConstantesARM64.inc"

.data
szMessSortOk: .asciz "Table sorted.\n"
szMessSortNok: .asciz "Table not sorted !!!!!.\n"
sMessResult: .asciz "Value : @ \n"
szCarriageReturn: .asciz "\n"

.align 4
TableNumber: .quad 1,3,11,6,2,5,9,10,8,4,7
#TableNumber: .quad 10,9,8,7,6,-5,4,3,2,1
                .equ NBELEMENTS, (. - TableNumber) / 8

.bss
sZoneConv: .skip 24

.text
.global main
main:
    ldr x0, qAdrTableNumber
    mov x1,0
    mov x2,NBELEMENTS
    bl mergeSort
    ldr x0, qAdrTableNumber
    bl displayTable

    ldr x0,qAdrTableNumber
    mov x1, NBELEMENTS
    bl isSorted
    cmp x0, 1
    beq 1f
    ldr x0,qAdrszMessSortNok
    bl affichageMess
    b 100f
1:
    ldr x0,qAdrszMessSortOk
    bl affichageMess
100:
    mov x0,0
    mov x8,EXIT
    svc 0

qAdrsZoneConv: .quad sZoneConv
qAdrszCarriageReturn: .quad szCarriageReturn
qAdrsMessResult: .quad sMessResult
qAdrTableNumber: .quad TableNumber
qAdrszMessSortOk: .quad szMessSortOk
qAdrszMessSortNok: .quad szMessSortNok

isSorted:
    stp x2,lr,[sp,-16]!
    stp x3,x4,[sp,-16]!
    mov x2,0
    ldr x4,[x0,x2,lsl 3]
1:
    add x2,x2,1
    cmp x2,x1
    bge 99f
    ldr x3,[x0,x2, lsl 3]
    cmp x3,x4
    blt 98f
    mov x4,x3
    b 1b
98:
    mov x0,0
    b 100f
99:
    mov x0,1
100:
    ldp x3,x4,[sp],16
    ldp x2,lr,[sp],16
    ret

merge:
    stp x1,lr,[sp,-16]!
    stp x2,x3,[sp,-16]!
    stp x4,x5,[sp,-16]!
    stp x6,x7,[sp,-16]!
    str x8,[sp,-16]!
    mov x5,x2
1:
    ldr x6,[x0,x1,lsl 3]
    ldr x7,[x0,x5,lsl 3]
    cmp x6,x7
    ble 4f
    str x7,[x0,x1,lsl 3]
    add x8,x5,1
    cmp x8,x3
    ble 2f
    str x6,[x0,x5,lsl 3]
    b 4f
2:
    sub x4,x8,1
    ldr x7,[x0,x8,lsl 3]
    cmp x6,x7
    bge 3f
    str x6,[x0,x4,lsl 3]
    b 4f
3: 
    str x7,[x0,x4,lsl 3]
    add x8,x8,1
    cmp x8,x3
    ble 2b
    sub x8,x8,1
    str x6,[x0,x8,lsl 3]
4:
    add x1,x1,1
    cmp x1,x2
    blt 1b
100:
    ldr x8,[sp],16
    ldp x6,x7,[sp],16
    ldp x4,x5,[sp],16
    ldp x2,x3,[sp],16
    ldp x1,lr,[sp],16
    ret
mergeSort:
    stp x3,lr,[sp,-16]!
    stp x4,x5,[sp,-16]!
    stp x6,x7,[sp,-16]!
    cmp x2,2
    blt 100f
    lsr x4,x2,1
    add x5,x4,1
    tst x2,#1
    csel x4,x5,x4,ne
    mov x5,x1
    mov x6,x2
    mov x7,x4
    mov x2,x4
    bl mergeSort
    mov x1,x7
    mov x2,x6
    sub x2,x2,x1
    mov x3,x5
    add x1,x1,x3
    bl mergeSort
    mov x1,x5
    mov x2,x7
    add x2,x2,x1
    mov x3,x6
    add x3,x3,x1
    sub x3,x3,1
    bl merge
100:
    ldp x6,x7,[sp],16
    ldp x4,x5,[sp],16
    ldp x3,lr,[sp],16
    ret
displayTable:
    stp x1,lr,[sp,-16]!
    stp x2,x3,[sp,-16]!
    mov x2,x0
    mov x3,0
1:
    ldr x0,[x2,x3,lsl 3]
    ldr x1,qAdrsZoneConv
    bl conversion10S
    ldr x0,qAdrsMessResult
    ldr x1,qAdrsZoneConv
    bl strInsertAtCharInc
    bl affichageMess
    add x3,x3,1
    cmp x3,NBELEMENTS - 1
    ble 1b
    ldr x0,qAdrszCarriageReturn
    bl affichageMess
    mov x0,x2
100:
    ldp x2,x3,[sp],16
    ldp x1,lr,[sp],16
    ret
.include "../includeARM64.inc"
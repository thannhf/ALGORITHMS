.include "../includeConstantesARM64.inc"

.equ FIRSTNODE, 0
    .struct 0
llist_next:
    .struct llist_next + 8
llist_value:
    .struct llist_value + 8
llist_fin:

.data
szMessDebutPgm: .asciz "Start program.\n"
szMessFinPgm: .asciz "Program End ok.\n"
szRetourLigne: .asciz "\n"
szMessValElement: .asciz "Value : @ \n"
szMessListeVide: .asciz "List empty.\n"
szMessImpElement: .asciz "Node display: @ value : @ Next @ \n"
szMessErrComm: .asciz "Incomplete Command line : josephus64 <maxi> <intervalle>\n"

.bss
sZoneConv: .skip 100
.align 4
qDebutListe1: .skip llist_fin

.text
.global main

main:
    mov fp,sp
    ldr x0,qAdrszMessDebutPgm
    bl affichageMess
    ldr x0,[fp]
    cmp x0,#2
    ble erreurCommande

    add x0,fp,#16
    ldr x0,[x0]
    bl conversionAtoD
    add x22,x0,FIRSTNODE
    add x0,fp,#24
    ldr x0,[x0]
    bl conversionAtoD
    mov x21,x0

    mov x0,FIRSTNODE
    mov x1,0
    bl createNode
    mov x25,x0
    mov x26,x0
    mov x24,FIRSTNODE + 1
    mov x23,1

1:
    mov x0,x24
    mov x1,0
    bl createNode
    str x0,[x26,llist_next]
    mov x26,x0
    add x24,x24,1
    add x23,x23,1
    cmp x23,x22
    blt 1b
    str x25,[x26,llist_next]
    mov x24,x26

2:
    mov x20,1

3:
    ldr x24,[x24,llist_next]
    add x20,x20,1
    cmp x20,x21
    blt 3b
    ldr x25,[x24,llist_next]
    ldr x22,[x25,llist_value]
    ldr x27,[x25,llist_next]
    str x27,[x24,llist_next]
    
    cmp x27,x24
    csel x24,x24,x27,ne
    bne 2b

    mov x0,x24
    bl displayNode

    b 100f

erreurCommande:
    ldr x0,qAdrszMessErrComm
    bl affichageMess
    mov x0,#1
    b 100f

100:
    ldr x0,qAdrszMessFinPgm
    bl affichageMess
    mov x0,0
    mov x8,EXIT
    svc #0

qAdrszMessDebutPgm: .quad szMessDebutPgm
qAdrszMessFinPgm: .quad szMessFinPgm
qAdrszRetourLigne: .quad szRetourLigne
qAdrqDebutListe1: .quad qDebutListe1
qAdrszMessErrComm: .quad szMessErrComm

createNode:
    stp x20,lr,[sp,-16]!
    stp x21,x22,[sp,-16]!
    mov x20,x0
    mov x21,x1
    mov x0,#0
    mov x8,BRK
    svc #0
    mov x22,x0
    add x0,x0,llist_fin
    mov x8,BRK
    svc #0
    cmp x0,#-1
    beq 100f

    str x20,[x22,llist_value]
    str x21,[x22,llist_next]
    mov x0,x22

100:
    ldp x21,x22,[sp],16
    ldp x20,lr,[sp],16
    ret

displayNode:
    stp x1,lr,[sp,-16]!
    stp x2,x3,[sp,-16]!
    mov x2,x0
    ldr x1,qAdrsZoneConv
    bl conversion16
    ldr x0,qAdrszMessImpElement
    ldr x1,qAdrsZoneConv
    bl strInsertAtCharInc
    mov x3,x0
    ldr x0,[x2,llist_value]
    ldr x1,qAdrsZoneConv
    bl conversion10S
    mov x0,x3
    ldr x1,qAdrsZoneConv
    bl strInsertAtCharInc
    mov x3,x0
    ldr x0,[x2,llist_next]
    ldr x1,qAdrsZoneConv
    bl conversion16
    mov x0,x3
    ldr x1,qAdrsZoneConv
    bl strInsertAtCharInc
    bl affichageMess

100:
    ldp x2,x3,[sp],16
    ldp x1,lr,[sp],16
    ret

qAdrsZoneConv: .quad sZoneConv
qAdrszMessImpElement: .quad szMessImpElement

.include "../includeARM64.inc"
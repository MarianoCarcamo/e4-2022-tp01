/**
 * Referencias importantes:
 * https://developer.arm.com/documentation/dui0552/a
 * https://github.com/ARM-software/abi-aa/tree/main/aapcs32
 */
.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.macro defun nombre
    .section .text.\nombre
    .global \nombre
    .type \nombre, %function
\nombre:
.endm

.macro endfun nombre
    .size \nombre, . - \nombre
.endm

defun copiaMemoria
    // Implementación aquí
    // R0: origen, R1: destino, R2: longitud
    CBZ R2, 0f
1:
    ldrb R3, [R0], #1
    strb R3, [R1], #1
    subs R2, #1
    bne 1b
0:
    bx lr
endfun copiaMemoria

defun copiaCadena
    // Implementación aquí
    // R0: origen, R1: destino, R2: longitudMaxima
    cbz R2, 0f
1:
    ldrb R3, [R0], #1
    strb R3, [R1], #1
    cmp R3, #0 //verifico si R3 es el caracter nulo 
    beq 0f
    subs R2, #1
    bne 1b
0:
    subs R1,#1
    movs R3,#0
    strb R3,[R1]
    bx lr
endfun copiaCadena

defun mayusculaEnLugar
    // Implementación aquí
    // R0: cadena, R1: longitudMaxima
    cbz R1, 0f
1:
    ldrb R3, [R0]
    cmp R3, (1<<6)
    blo 2f
    and R3,0xDF
2:
    strb R3, [R0], #1
    cmp R3, #0 //verifico si R3 es el caracter nulo
    beq 0f
    subs R1, #1
    bne 1b
0:
    bx lr
endfun mayusculaEnLugar

defun minusculaEnLugar
    // Implementación aquí
    // R0: cadena, R1: longitudMaxima
    cbz R1, 0f
1:
    ldrb R3, [R0]
    movs R2,R3
    cmp R2, 0x60
    bhs 2f
    orrs R2,(1<<5)
2:
    cmp R3, #0 //verifico si R3 es el caracter nulo
    beq 0f
    strb R2, [R0], #1
    subs R1, #1
    bne 1b
0:
    bx lr
endfun minusculaEnLugar

.intel_syntax noprefix

.equ SYS_READ, 0
.equ SYS_WRITE, 1

.section    .text
.globl main

hello:
    .ascii  "Hello World!\n"
.equ len, . - hello

main:
    mov     rax, 1
    mov     rdi, 1
    mov     rsi, offset hello
    mov     rdx, len
    syscall
    mov     rax, 0
    ret

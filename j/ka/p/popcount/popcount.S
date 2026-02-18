.intel_syntax noprefix

.include "util.S"

.equ buf_len, 101

.section .bss
buf:
    .skip buf_len

.section .rodata
ones2:
    .ascii "01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
tens2:
    .ascii "1111111111222222222233333333334444444444555555555566666666667777777777888888888899999999990"

.section .text
.globl main

main:
    mov     sysc, 0
    mov     arg0, stdin
    mov     arg1, offset buf
    mov     arg2, buf_len
    syscall

    xor     rax, rax            # popcnt
    xor     rdx, rdx            # digit
    mov     rbx, offset buf     # ptr
    jmp     mid_loop
start_loop:
    add     rax, rdx
    inc     rbx
mid_loop:
    mov     dl, [rbx]
    sub     dl, '0'
    jge     start_loop

    mov     arg2, 1             # length
    cmp     rax, 100
    jl      print10
    inc     arg2
    mov     byte ptr [buf + 0], '1'
print10:
    cmp     rax, 10
    jl      print1
    inc     arg2
    mov     bl, [tens2 - 10 + rax]
    mov     [buf + 1], bl
print1:
    mov     bl, [ones2 + rax]
    mov     [buf + 2], bl

    mov     sysc, sys_write
    mov     arg0, stdout
    mov     arg1, offset buf + 3
    sub     arg1, arg2
    syscall

    xor ret0, ret0
    ret

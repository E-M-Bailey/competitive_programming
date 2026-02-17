.intel_syntax noprefix

.include "util.S"

.equ buf_len, 1 << 20

.section .bss
buf:
    .skip buf_len

.section .text
.globl main

main:
    mov     sysc, 0
    mov     arg0, stdin
    mov     arg1, offset buf
    mov     arg2, buf_len
    syscall

    mov     r10, 10
    xor     rax, rax
    xor     r8, r8

    mov     al, [buf]
    sub     rax, '0'
    mov     r8b, [buf + 1]
    sub     r8, '0'
    js      end_in
    mul     r10
    add     rax, r8
    mov     r8b, [buf + 2]
    sub     r8, '0'
    js      end_in
    mul     r10
    add     rax, r8
    mov     r8b, [buf + 3]
    sub     r8, '0'
    js      end_in
    mul     r10
    add     rax, r8
    mov     r8b, [buf + 4]
    sub     r8, '0'
    js      end_in
    mul     r10
    add     rax, r8
    mov     r8b, [buf + 5]
    sub     r8, '0'
    js      end_in
    mul     r10
    add     rax, r8
end_in:

    mov     r8, rax  # n
    mov     r9, 1    # i
    xor     r11, r11 # pos
    mov     r12, r10 # pow10
    mov     r13, 2   # len
out_loop:
    cmp     r9, r12
    jne     skip_inc
    mov     rax, r12
    mul     r10
    mov     r12, rax
    inc     r13
skip_inc:
    add     r11, r13
    mov     byte ptr [(buf - 1) + r11], '\n'
    mov     rax, r9

    xor     rdx, rdx
    div     r10
    add     rdx, '0'
    mov     [(buf - 2) + r11], dl # 1
    cmp     rax, 0
    je      end_put
    xor     rdx, rdx
    div     r10
    add     rdx, '0'
    mov     [(buf - 3) + r11], dl # 10
    cmp     rax, 0
    je      end_put
    xor     rdx, rdx
    div     r10
    add     rdx, '0'
    mov     [(buf - 4) + r11], dl # 100
    cmp     rax, 0
    je      end_put
    xor     rdx, rdx
    div     r10
    add     rdx, '0'
    mov     [(buf - 5) + r11], dl # 1000
    cmp     rax, 0
    je      end_put
    xor     rdx, rdx
    div     r10
    add     rdx, '0'
    mov     [(buf - 6) + r11], dl # 10000
    cmp     rax, 0
    je      end_put
    xor     rdx, rdx
    div     r10
    add     rdx, '0'
    mov     [(buf - 7) + r11], dl # 100000
end_put:
    inc     r9
    cmp     r9, r8
    jle     out_loop
# end_out_loop:

    mov     sysc, sys_write
    mov     arg0, stdout
    mov     arg1, offset buf
    mov     arg2, r11
    syscall

    mov     rax, 0
    ret

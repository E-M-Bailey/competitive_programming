.intel_syntax noprefix

.include "util.S"

.equ buf_len, 16

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

    xor     rax, rax
    mov     r10, 10 # 10
    xor     r8, r8  # M
    xor     r9, r9  # pos

    mov     al, [buf]
    sub     rax, '0'
    mov     r8b, [buf + 1]
    sub     r8, '0'
    jl      end_m
    inc     r9
    mul     r10
    add     rax, r8
    mov     r8b, [buf + 2]
    sub     r8, '0'
    jl      end_m
    inc     r9
    mul     r10
    add     rax, r8
    mov     r8b, [buf + 3]
    sub     r8, '0'
    jl      end_m
    inc     r9
    mul     r10
    add     rax, r8
    mov     r8b, [buf + 4]
    sub     r8, '0'
    jl      end_m
    inc     r9
    mul     r10
    add     rax, r8
end_m:
    mov     r11, rax # M

    mov     al, [buf + 3 + r9]
    cmp     al, '0'
    jl      end_k
    inc     r9
    mov     al, [buf + 3 + r9]
    cmp     al, '0'
    jl      end_k
    inc     r9
end_k:

    xor     rax, rax
    xor     r8, r8
    mov     al, [buf + 4 + r9]
    sub     rax, '0'
    mov     r8b, [buf + 5 + r9]
    sub     r8, '0'
    jl      end_c
    mul     r10
    add     rax, r8
    mov     r8b, [buf + 6 + r9]
    sub     r8, '0'
    jl      end_c
    mul     r10
    add     rax, r8
    mov     r8b, [buf + 7 + r9]
    sub     r8, '0'
    jl      end_c
    mul     r10
    add     rax, r8
    mov     r8b, [buf + 8 + r9]
    sub     r8, '0'
    jl      end_c
    mul     r10
    add     rax, r8
end_c:
    mul     r11    # rax: M*C
    mov     r12, 1 # output length

    xor     rdx, rdx
    div     r10
    add     rdx, '0'
    mov     [buf + 8], dl # 1
    cmp     rax, 0
    je      end_out
    inc     r12
    xor     rdx, rdx
    div     r10
    add     rdx, '0'
    mov     [buf + 7], dl # 10
    cmp     rax, 0
    je      end_out
    inc     r12
    xor     rdx, rdx
    div     r10
    add     rdx, '0'
    mov     [buf + 6], dl # 100
    cmp     rax, 0
    je      end_out
    inc     r12
    xor     rdx, rdx
    div     r10
    add     rdx, '0'
    mov     [buf + 5], dl # 1000
    cmp     rax, 0
    je      end_out
    inc     r12
    xor     rdx, rdx
    div     r10
    add     rdx, '0'
    mov     [buf + 4], dl # 10000
    cmp     rax, 0
    je      end_out
    inc     r12
    xor     rdx, rdx
    div     r10
    add     rdx, '0'
    mov     [buf + 3], dl # 100000
    cmp     rax, 0
    je      end_out
    inc     r12
    xor     rdx, rdx
    div     r10
    add     rdx, '0'
    mov     [buf + 2], dl # 1000000
    cmp     rax, 0
    je      end_out
    inc     r12
    xor     rdx, rdx
    div     r10
    add     rdx, '0'
    mov     [buf + 1], dl # 10000000
    cmp     rax, 0
    je      end_out
    inc     r12
    add     rax, '0'
    mov     [buf], al # 100000000
end_out:

    mov     sysc, sys_write
    mov     arg0, stdout
    mov     arg1, offset buf + 9
    sub     arg1, r12
    mov     arg2, r12
    syscall

    xor ret0, ret0
    ret

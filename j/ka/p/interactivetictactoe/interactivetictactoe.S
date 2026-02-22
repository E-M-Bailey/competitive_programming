.intel_syntax noprefix
.altmacro

.include "util.S"

.equ buf_len, 16
.equ table_size, 1 << 18

.section .bss
    .align 16
buf:
    .skip buf_len
table:
    # x to move:
    # 0x0f: next move
    # 0x10: game over
    # 0x20: o win
    # 0x40: draw
    # 0x80: x win
    # exactly bit in 0xe0 will be set
    # index: x(x|o) mask (r8d & 0x3ffff)
    # exception: table[0] is 0xe # TODO confirm this is still true
    .skip           table_size + 31

.equ d_shl, 6
.equ x_shl, 7
.equ o_shl, 5
.equ d_bit, 1 << d_shl
.equ x_bit, 1 << x_shl
.equ o_bit, 1 << o_shl

.section .rodata
    .align 32
.equ yall_wins, ymm7
all_wins:   #       888
            #       888
            #       88
    .int            x_bit, x_bit, x_bit, x_bit, x_bit, x_bit, x_bit, x_bit
.equ ybit_iota, ymm8
.equ bit_iota_hi, 0x00020000
bit_iota:   #       #..         .#.         ..#         ...         ...         ...         ...         ...
            #       ...         ...         ...         #..         .#.         ..#         ...         ...
            #       ..          ..          ..          ..          ..          ..          #.          .#
    .int            0x00000200, 0x00000400, 0x00000800, 0x00001000, 0x00002000, 0x00004000, 0x00008000, 0x00010000
.equ xpatterns, xmm9
patterns:   #       ###.    ....    ....    #...    .#..    ..#.    #...    ..#.
            #       ....    ###.    ....    #...    .#..    ..#.    .#..    .#..
            #       ....    ....    ###.    #...    .#..    ..#.    ..#.    #...
            #       ....    ....    ....    ....    ....    ....    ....    ....
    .word           0x0007, 0x0038, 0x01c0, 0x0049, 0x0092, 0x0124, 0x0111, 0x0054
.equ xget_shuf, xmm10
get_shuf:   #       #...  .#..  ..#.  ....  ....  ....  ....  ....  ....  ....  ....  ....  ....  ....  ....  ....
            #       ....  ....  ....  #...  .#..  ..#.  ....  ....  ....  ....  ....  ....  ....  ....  ....  ....
            #       ....  ....  ....  ....  ....  ....  #...  .#..  ..#.  ....  ....  ....  ....  ....  ....  ....
            #       ....  ....  ....  ....  ....  ....  ....  ....  ....  ....  ....  ....  ....  ....  ....  ....
    .byte           0x00, 0x01, 0x02, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0A, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
.equ xput_shuf, xmm11
put_shuf:   # index / 8, -1 outside
            #       000.
            #       000.
            #       001.
            #       ....
    .byte           0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff
.equ xput_mask, xmm12
put_mask:   # 1 << (index % 8), 0xff outside
            #       012.
            #       345. <- ctz
            #       670.
            #       ....
    .byte           0x01, 0x02, 0x04, 0xff, 0x08, 0x10, 0x20, 0xff, 0x40, 0x80, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff
.equ xd_string, xmm13
d_string:   #         . . .\n
            #         . . .\n
            #         . . .\n
            #        \0\0\0\0
    .byte            '.',  '.',  '.', '\n',  '.',  '.',  '.', '\n',  '.',  '.',  '.', '\n',    0,    0,    0,    0
.equ xx_string, xmm14
x_string:   #         x x x\n
            #         x x x\n
            #         x x x\n
            #        \0\0\0\0
    .byte            'x',  'x',  'x', '\n',  'x',  'x',  'x', '\n',  'x',  'x',  'x', '\n',    0,    0,    0,    0
.equ xo_string, xmm15
o_string:   #         o o o\n
            #         o o o\n
            #         o o o\n
            #        \0\0\0\0
    .byte            'o',  'o',  'o', '\n',  'o',  'o',  'o', '\n',  'o',  'o',  'o', '\n',    0,    0,    0,    0

.section .text
.globl main

# Clobbers rax, rcx, rdx, rsi, rdi, and r11.
.macro read_buf     length, position=0
LOCAL               read_buf_syscall
    xor             arg0, arg0          # stdin
    mov             arg1, offset buf + \position
    mov             arg2, \length
read_buf_syscall:
    xor             sysc, sysc          # read
    syscall
    add             arg1, ret0
    sub             arg2, ret0
    jnz             read_buf_syscall
.endm

# Clobbers rax, rcx, rdx, rsi, rdi, and r11.
.macro write_buf    length, position=0
    mov             sysc, write
    mov             arg0, stdout
    mov             arg1, offset buf + \position
    mov             arg2, \length
    syscall
.endm

# Returns o/x masks in od/xd. Clobbers rax, rcx, rdx, rsi, rdi, r11, xmm2, and xmm3.
.macro get_board    od, xd
    read_buf        12
    vmovdqa         xmm2, [buf]
    vmovdqa         xmm3, xmm2
    pcmpeqb         xmm2, xx_string
    pcmpeqb         xmm3, xo_string
    pshufb          xmm2, xget_shuf
    pshufb          xmm3, xget_shuf
    pmovmskb        \od, xmm2
    pmovmskb        \xd, xmm3
.endm

# Takes x/o masks in low nine bits of xd/od. Clobbers rax, rcx, rdx, rsi, rdi, r11, xmm2, and xmm3.
.macro put_board    xd, od
    vmovd           xmm2, \xd
    vmovd           xmm3, \od
    pshufb          xmm2, xput_shuf
    pshufb          xmm3, xput_shuf
    pand            xmm2, xput_mask
    pand            xmm3, xput_mask
    pcmpeqb         xmm2, xput_mask
    pcmpeqb         xmm3, xput_mask
    vpblendvb       xmm2, xd_string, xx_string, xmm2
    vpblendvb       xmm2, xmm2, xo_string, xmm3
    vmovdqa         [buf], xmm2
    write_buf       12
.endm

main:
    vpxor           xmm0, xmm0, xmm0
    # vpcmpeqb        ymm1, ymm1
    vmovdqa         yall_wins, [all_wins]
    vmovdqa         ybit_iota, [bit_iota]
    movdqa          xpatterns, [patterns]
    movdqa          xget_shuf, [get_shuf]
    movdqa          xput_shuf, [put_shuf]
    movdqa          xput_mask, [put_mask]
    movdqa          xd_string, [d_string]
    movdqa          xx_string, [x_string]
    movdqa          xo_string, [o_string]

    mov             r8d, 0x3ffff        # x (x|o)
    mov             r10d, 0x1ff         # x|o
table_start:
    mov             r9d, r8d
    xor             r9d, r10d           # o (x|o)

    # Check whether the game is over
    xor             dx, dx
    vmovd           xmm2, r8d
    vmovd           xmm3, r9d
    vpbroadcastw    xmm2, xmm2
    vpbroadcastw    xmm3, xmm3
    pand            xmm2, xpatterns
    pand            xmm3, xpatterns
    pcmpeqw         xmm2, xpatterns
    pcmpeqw         xmm3, xpatterns
    pmovmskb        eax, xmm2
    pmovmskb        ebx, xmm3
    cmp             ax, 0
    setnz           al
    cmp             bx, 0
    setnz           bl
    cmp             r10w, 0x1ff
    setz            cl
    shl             al, x_shl
    shl             bl, o_shl
    shl             cl, d_shl
    or              al, bl
    cmovnz          cx, dx
    # or              al, 0x0f # TODO remove
    or              al, cl
    # cmp             al, 0x0f # TODO remove
    jnz             table_put
    # and             al, 0xf0 # TODO remove

evaluate:
    # Determine the outcome if the game is not over
    vmovd           xmm1, r9d
    vpbroadcastd    ymm1, xmm1
    vpor            ymm2, ymm1, ybit_iota
    vpandn          ymm1, ymm1, ybit_iota
    vpcmpeqd        ymm1, ymm1, ybit_iota
    vmovmskps       esi, ymm1
    vmovdqa         ymm3, yall_wins
    vpgatherdd      ymm3, [table + ymm2], ymm1
    mov             ebx, r9d
    mov             eax, r9d
    mov             cl, x_bit
    or              ebx, bit_iota_hi
    and             eax, bit_iota_hi
    cmovz           cx, [table + ebx]
    mov             dl, cl
    vmovdqa         ymm1, ymm3
    vextracti128    xmm2, ymm3, 1
    por             xmm3, xmm2
    vpunpckhdq      xmm2, xmm3, xmm0
    punpckldq       xmm3, xmm0
    por             xmm3, xmm2
    pextrb          ebx, xmm3, 0
    or              cl, bl
    pextrb          ebx, xmm3, 8
    mov             eax, 0x73717371
    or              cl, bl
    and             cl, 0xe0
    mov             bl, cl
    neg             bl
    and             bl, cl              # lowest 0xe0 bit among possible next moves
    shr             cl, 3
    shr             eax, cl
    shl             al, 4
    vmovd           xmm2, ebx
    vpbroadcastd    ymm2, xmm2
    vpand           ymm1, ymm1, ymm2
    vpcmpeqd        ymm1, ymm1, ymm2
    vmovmskps       ecx, ymm1
    and             ecx, esi
    and             dl, bl
    setnz           ch
    tzcnt           cx, cx
    or              al, cl

table_put:
    add             al, 0x10
    mov             [table + r8d], al

    dec             r8d
    mov             eax, r8d
    mov             eax, r8d
    shr             eax, 9
    mov             r10d, eax
    or              eax, 0x3fe00
    and             r8d, eax
    jnz             table_start
# table_end:
    mov             byte ptr [table], d_bit

aaaaaaaa:
    # determine first player
    read_buf        6
    cmp             byte ptr [buf], 'f'
    jz              play_middle
    # read extra character and swap xx_string and xo_string if second
    xor             sysc, sysc
    mov             arg2, 1
    syscall

    jmp             play_middle
play_start:
    xor             r9d, r8d            # o (x|o)
    mov             ebx, 0x201
    mov             edx, 0x200
    and             cl, 0x0f
    shl             ebx, cl
    shl             edx, cl
    or              r8d, ebx
    or              r9d, edx
    put_board       r8d, r9d
    mov             cl, [table + r8d]
    and             cl, 0x10
    jnz             play_end
play_middle:
    get_board       r8d, r10d
    mov             bl, 0x10
    or              r10d, r8d           # x|o
    mov             r9d, r10d
    shl             r10d, 9
    or              r8d, r10d           # x (x|o)
    mov             cl, [table + r8d]
    and             bl, cl
    jz              play_start
play_end:

    xor             ret0, ret0
    ret

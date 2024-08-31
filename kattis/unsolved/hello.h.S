.intel_syntax noprefix

.section    .rodata
hello:
    .ascii  "Hello World!\n"
.equ len, . - hello
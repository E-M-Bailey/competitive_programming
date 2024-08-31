

.intel_syntax noprefix

// Syscalls
	.equ	SYS_READ,  0
	.equ	SYS_WRITE, 1

// Streams
	.equ	STDIN,  0
	.equ	STDOUT, 1
	.equ	STDERR, 2

// Constants
	.equ	ALGN, 1024
	.equ	BUFS, 1024

// Macros
// buffered I/O
// rin
.macro		rin			buf, len
	xor		eax, eax
	xor		edi, edi
	mov		esi, offset \buf
	mov		edx, \len
	syscall
.endm
// wout
.macro		wout		buf, len
	mov		eax, 1
	mov		edi, 1
	mov		esi, offset \buf
	mov		edx, \len
	syscall
.endm
// werr
.macro		werr		buf, len
	mov		eax, 1
	mov		edi, 2
	mov		esi, offset \buf
	mov		edx, \len
	syscall
.endm

// Formatted I/O from buffers. The direction flag must be cleared and rsi must point to the string.
// eax must be zero except possibly the last byte. Also skips the delimiter.
.macro		rint		dest, delim=' 
	lodsb
	sub		rax, '0
	mov		\dest, rax
	lodsb
	cmp		rax, \delim
	jz		1f
0:
	sub		rax, '0
	imul	\dest, 10
	add		\dest, rax
	lodsb
	cmp		rax, \delim
	jnz		0b
1:
.endm

.section	.data
	.align	ALGN
buf:
	.skip	BUFS

.section    .text
	.globl	main
main:
	rin		buf, BUFS
	mov		rsi, offset buf

	cld
	rint	r8
	rint	r9
	rint	r10
	rint	r11
	rint	r12, '\n
	rint	r13, '\n

	movb	r14b, 'F
	movb	bl, 'E
	cmp		r13, r12
	cmovge	r14d, ebx
	dec		ebx
	cmp		r13, r11
	cmovge	r14d, ebx
	dec		ebx
	cmp		r13, r10
	cmovge	r14d, ebx
	dec		ebx
	cmp		r13, r9
	cmovge	r14d, ebx
	dec		ebx
	cmp		r13, r8
	cmovge	r14d, ebx

	movb	buf, r14b
	wout	buf, 1

	xor		eax, eax
    ret

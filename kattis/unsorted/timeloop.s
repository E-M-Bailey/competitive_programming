#__asm__(R"(
.intel_syntax noprefix

.equ	SYS_READ,	0
.equ	SYS_WRITE,	1

.equ	STDIN,		0
.equ	STDOUT,		1


###		RODATA		###
	.section	.rodata
	.align	16
abra:
	.ascii	" Abracadabra\n\0\0\0"
	.equ	abralen, . - abra

###		DATA		###
	.section	.data

	.align	4
in:
	.ascii	"000"

	.align 4
ctr:
	.ascii	"000"

	.align 1024
out:
	.space	2048
	.equ	outlen, . - out


###		TEXT		###
.section	.text
.globl		main
main:
	xor		eax, eax
	xor		edi, edi
	mov		esi, offset in
	mov		edx, 3
	syscall
	mov		rax, in
	ret

#)");

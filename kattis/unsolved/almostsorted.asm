		.global main

		# System Calls
		SYS_READ		equ	0
		SYS_WRITE		equ	1

		# File Descriptors
		STDIN			equ 0
		STDOUT			equ	1
		STDERR			equ 2

		# Constants
		BUFS			equ 2400019

		# Text
		.text
main:
		mov rax, SYS_READ
		mov rdi, STDIN
		mov rsi, buf
		mov rdx, BUFS
		syscall

		mov rax, SYS_WRITE

		# Data
		.data


		# Zero-Initialized Data
		.bss
buf:	.zero		BUFS
	

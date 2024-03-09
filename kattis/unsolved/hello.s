
.text

.global main

main:
	mov $message, %rdi
	

message:
	.asciz "Hello World!"
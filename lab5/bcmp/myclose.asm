section	.text
	global myclose

myclose:					;void myclose(fd)
	push ebp
	mov ebp, esp

	mov 	ebx,[esp + 8]	;message to write
	mov	eax,6	;system call number (sys_close)
	int	0x80	;call kernel

	pop ebp
	ret

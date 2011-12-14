section	.text
	global myreadSingleChar

myreadSingleChar:					;void myreadSingleChar(fd, buf)
	push ebp
	mov ebp, esp

	mov	ebx,[esp + 8]	;file descriptor
	mov	ecx,[esp + 12]	;buf
	mov word edx,1		;size to read
	mov	eax,3		;system call number (sys_read)
	int	0x80		;call kernel
	movzx ecx, cl		;buf is only a char

	pop ebp
	ret


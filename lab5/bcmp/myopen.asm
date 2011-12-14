section	.text
	global myopen

myopen:					;void myopen(filename)
	push ebp
	mov ebp, esp

	mov	edx,0		;flags?	
	mov  	ebx,[esp + 8]	;file name
	mov	ecx,384		;mode (384 = user rw)
	mov	eax,5		;system call number (sys_open)
	int	0x80		;call kernel

	pop ebp
	ret

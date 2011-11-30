section	.text
	global ahalan
	global write
	extern myputs

ahalan:					;void ahalan()
	push	msg
	call	myputs
	;ret
	mov	eax,1	;system call number (sys_exit)
	int	0x80	;call kernel

write:
	push	ebp
	mov 	ebp,esp
	mov 	edx,[ebp+16]
	mov 	ecx,[ebp+12]	;message to write
	mov 	ebx,[ebp+8]	;file descriptor (stdout)
	mov 	eax,4	;system call number (sys_write)
	int 	0x80	;call kernel
	pop 	ebp
	;ret
	mov	eax,1	;system call number (sys_exit)
	int	0x80	;call kernel

section	.data

msg	db	'ahalan!',0xa	;our dear string
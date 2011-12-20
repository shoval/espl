section .text
	global	_start
	global	write
	global	length

	extern	main

_start:
	mov		dword ecx,esp
	add		ecx,4
	push	dword ecx
	push	dword [esp+4]
	call	main
	mov 	ebx,eax
	mov 	eax,1
	int 	0x80


write:
	push	ebp
	mov 	ebp,esp
	mov 	edx,[ebp+16]
	mov 	ecx,[ebp+12]	;message to write
	mov 	ebx,[ebp+8]	;file descriptor (stdout)
	mov 	eax,4	;system call number (sys_write)
	int 	0x80	;call kernel
	pop 	ebp
	ret


length:
	push	ebp
	mov 	ebp,esp
	mov		eax,[ebp+8] ;char* s
.p3:
	push	dword eax
	mov		ebx,[eax]
	movzx	ebx, bl
	test	bl,bl
	je		.q3
	pop		eax
	add		DWORD eax,1
	jmp		.p3
.q3:
	mov		ebx,[ebp+8]
	sub		eax, ebx
	add		esp,4
	pop		ebp
	ret

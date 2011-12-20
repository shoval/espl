section .text
	global	main

	extern	length
	extern	write

main:
	;push	dword 734432 ;print a number
	;call	writenum
	;add		esp,4

	push	ebp
	mov 	ebp,esp
	mov		eax,[ebp+12] ;argv
	push	dword [eax+4] ;first arg in argv
	call	prsymwrd
	add 	esp,4
	pop		ebp
	mov 	ebx,eax
	mov 	eax,1
	int 	0x80


prsymwrd: ;TODO: finish implementing this function
	push	ebp
	mov 	ebp,esp
	mov	edx,0 ;init iline
.p2:
	push	dword edx
	mov		ebx,[sh]
	sub		ebx,edx ;if iline==SYMBOL_HEIGHT
	je		.q2
	push	edx
	push	dword [ebp+8]
	call	prsymline
	add		esp,8
	call	printnl
	pop		edx
	add		edx,1
	jmp		.p2
.q2:
	add		esp,4
	pop		ebp
	ret


prsymline:
	push	ebp
	mov 	ebp,esp
	mov		edx,[ebp+8] ;char* tword
	mov		ebx,[ebp+12] ;int iline
.p1:
	push	dword edx
	push	dword ebx
	mov		ecx,[edx]
	movzx	ecx, cl
	test	cl,cl
	je		.q1
	sub		ecx,32
	push	ebx
	push	ecx
	call	prsymchar
	add		esp,8
	pop		ebx
	pop		edx
	add		DWORD edx,1
	jmp		.p1
.q1:
	add		esp,8
	pop		ebp
	ret


prsymchar:
	push	ebp
	mov 	ebp,esp

	;(first int) * 24
	mov		eax,[ebp+8]
	sal		eax,1
	add		eax,[ebp+8]
	sal		eax,3

	mov		ebx,alphabet
	add		ebx,eax
	mov		eax,[ebp+12] ;argv
	sal		eax, 2 ;(second int) * 4
	add		ebx,eax
	mov		ebx,[ebx]
	push	ebx
	call	length
	add		esp,4
	push	eax ;length
	push	ebx ;string pointer
	push	1 ;stdout
	call	write
	add 	esp,12
	pop		ebp
	;mov 	ebx,eax
	ret


printnl:
	push	1 ;length
	push	nl ;string pointer
	push	1 ;stdout
	call	write
	add 	esp,12
	ret


section	.data
	extern	alphabet
	msg	db	'hey! '
	nl	db	0xa
	sh	db	6

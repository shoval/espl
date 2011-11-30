section .text
global atodst
atodst:
	push	ebp
	mov	ebp, esp
	mov	edx, 0; init edx to be the total
.L5:
	mov	eax, [ebp+8]
	mov	eax, [eax]
	movzx	eax, al
	test	al, al; if end of word (equals ascii 0) 
	je	.L3
	sub	eax, 48
	;sal	eax, 2
	mov	ebx, edx
	sal	edx, 2
	add	edx, ebx
	add	edx, edx
	add	edx, eax
.L4:
	add	DWORD [ebp+8], 1
	add	DWORD [ebp+12], 1
	jmp	.L5
.L3:
	mov	eax, edx; put the incremental number in the return val
	pop	ebp
	ret

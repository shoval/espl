section .text
global hsvmhr
hsvmhr:
	push	ebp
	mov	ebp, esp
.L5:
	mov	eax, [ebp+8]; first param of func
	mov	eax, [eax]
	mov	edx, [ebp+12]; second param of func
	mov	edx, [edx]
	movzx eax, al; eax contains the return value
	movzx edx, dl
	sub	eax, edx
	je	.L2
	jmp	.L3
.L2:
	test dl, dl
	jne	.L4
	xor	eax, eax
	jmp	.L3
.L4:
	add	DWORD [ebp+8], 1
	add	DWORD [ebp+12], 1
	jmp	.L5
.L3:
	pop	ebp
	ret

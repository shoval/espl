section .text
	global _start

extern main
_start:
	mov dword ecx,esp
	add ecx,4
	push dword ecx
	push dword [esp+4]
	
			;argc = esp, argv = esp+1

	call	main
	
	add esp,8 ;return stack to proper position
	
	
        mov     ebx,eax
	mov	eax,1
	int 0x80

section	.text
	global printFirstChar
	
	;extern length			;length is implemented in length.c

printFirstChar:					;void printFirstChar(char*)
	push ebp
	mov ebp, esp

	;get the pointer to str (esp?)


	;;call c function to get str len
	;push dword [esp + 8]		; prepare args for function call	
	;call	length			; call the function
	mov	edx,1			; move the var to the right register (size to write)
	
	;add esp,4	;to guard stack (BETTER THEN POP)
	
	mov dword ecx,[esp + 8]	;message to write
	mov	ebx,1	;file descriptor (stdout)
	mov	eax,4	;system call number (sys_write)
	int	0x80	;call kernel

	pop ebp
	ret


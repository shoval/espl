section	.text
	global _start			;must be declared for linker (ld)
	extern length			;length is implemented in length.c

_start:					;tell linker entry point
	;; TODO: add call to function `length' here
	;; (you'll need 3 assembly instructions)
	push	DWORD msg
	call	length
	mov		edx,eax
	mov		ecx,msg	;message to write
	mov		ebx,1	;file descriptor (stdout)
	mov		eax,4	;system call number (sys_write)
	int		0x80	;call kernel

	mov	eax,1	;system call number (sys_exit)
	int	0x80	;call kernel

section	.data

msg	db	"Hello', w",   'orld!',0xa,0	;our dear string

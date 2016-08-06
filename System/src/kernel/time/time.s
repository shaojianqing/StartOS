global asmIntHandler20

extern intTimeHandler

[bits 32]

;The assembly signature of the timing interrupt handler entry point
asmIntHandler20:
	push ds
	pushad

	mov eax, 00010_000B
	mov ds, eax

	call intTimeHandler
	
	popad
	pop ds
	iretd
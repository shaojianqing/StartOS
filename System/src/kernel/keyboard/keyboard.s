
global asmIntHandler21

extern intKeyboardHandler

[bits 32]

;The assembly signature of the keyboard interrupt handler entry point
asmIntHandler21:
	push ds
	push es
	pushad

	mov eax, 00010_000B
	mov ds, eax
	mov es, eax

	call intKeyboardHandler
	
	popad
	pop es
	pop ds
	iretd

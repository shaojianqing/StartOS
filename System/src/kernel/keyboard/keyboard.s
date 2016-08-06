
global asmIntHandler21

extern intKeyboardHandler

[bits 32]

;The assembly signature of the keyboard interrupt handler entry point
asmIntHandler21:
	push ds
	pushad

	mov eax, 00010_000B
	mov ds, eax

	call intKeyboardHandler
	
	popad
	pop ds
	iretd
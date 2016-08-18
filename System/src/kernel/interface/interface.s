
global systemIntface

extern systemCallTable

[bits 32]

systemIntface:
	push ds
	push es
	push fs

	push edx
	push ecx
	push ebx
	
	mov edx, 00010_000B	
	mov ds, edx

	mov edx, 00010_111B
	mov fs, edx

	call [systemCallTable+eax*4]
	
	pop ebx
	pop ecx
	pop edx

	pop fs
	pop es
	pop ds
			
	iretd
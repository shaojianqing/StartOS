
global asmIntHandler2e

extern intHarddiskHandler

[bits 32]

;The assembly signature of the harddisk interrupt handler entry point
asmIntHandler2e:
	push ds
	pushad
	
	mov eax, 00010_000B	
	mov ds, eax

	call intHarddiskHandler
		
	popad 
	pop ds		
	iretd
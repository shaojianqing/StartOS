
global setCursor

[bits 32]

 setCursor:
	push ebp
	mov ebp, esp
	push eax
	push ebx
	push edx

	mov ebx, [ebp+8]

	mov dx, 0x03d4
	mov al, 0x0e				 
	out dx, al
	mov dx, 0x03d5			  
	mov al, bh
	out dx, al

	mov dx, 0x03d4
	mov al, 0x0f
	out dx, al
	mov dx, 0x03d5 
	mov al, bl
	out dx, al

	pop edx
	pop ebx
	pop eax
	
	mov esp, ebp
	pop ebp	

	ret


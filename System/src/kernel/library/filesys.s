%include "src/kernel/library/syscall.inc"

global open
global close

[bits 32]

open:
	push ebp
	mov ebp, esp
	push ebx
	push ecx
	push edx
	mov eax, INDEX_OPEN
	mov ebx, [ebp+8]
	mov ecx, [ebp+12]
	mov edx, [ebp+16] 

	int SYSTEM_ENTRY

	mov ebx, eax
	test ebx, ebx
	js open_error
	mov eax, ebx
	jmp open_normal
open_error:
	mov eax, -1
open_normal:
	pop edx
	pop ecx
	pop ebx
	pop ebp
	mov esp, ebp
	pop ebp
	ret

close:
	push ebp
	mov ebp, esp
	push ebx
	push ecx
	push edx
	mov eax, INDEX_CLOSE
	mov ebx, [ebp+8]
	xor ecx, ecx
	xor edx, edx

	int SYSTEM_ENTRY

	mov ebx, eax
	test ebx, ebx
	js close_error
	mov eax, ebx
	jmp close_normal
close_error:
	mov eax, -1
close_normal:
	pop edx
	pop ecx
	pop ebx
	pop ebp
	ret

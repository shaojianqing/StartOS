%include "src/kernel/const/const.inc"	

global inByte
global loadTr
global outByte
global initPic
global memcopy
global loadGdtr
global loadIdtr
global readPort
global startHlt
global readHardDisk
global switchProcess
global clearInterrupt
global setupInterrupt
global setupInterruptHlt

[bits 32]

; Initialize the hardware interrupt settings so that
; the hardware devices can trigger interrupts. 
initPic:
    mov al, 0x11
    out 0x20, al
    out 0xa0, al

    mov al, 0x20
    out 0x21, al

    mov al, 0x28
    out 0xa1, al

    mov al, 0x04
    out 0x21, al

    mov al, 0x02
    out 0xa1, al

    mov al, 0x01
    out 0x21, al
    out 0xa1, al

    mov al, 11111000B
    out 0x21, al

    mov al, 10101111B
    out 0xa1, al

    ret

; Load and set the base address and limit of GDT table to the GDTR register.
loadGdtr:
	mov ax, [esp+4]
	mov [esp+6], ax
	lgdt [esp+6]
	ret

; Load and set the base address and limit of LDT table to the LDTR register.
loadIdtr:
	mov ax, [esp+4]
	mov [esp+6],ax
	lidt [esp+6]
	ret

; Load and set tss segment selector to the TR register.
loadTr:
	ltr [esp+4]
	ret

; Clear and stop the interrupt so that make sure the following procedure not disturbed 
; by the hardware interrupt.
clearInterrupt:
	cli
	ret

; Setup and start the interrupt so that the OS can trigger hardware interrupt and respond
; to the user.
setupInterrupt:
	sti
	ret

; Setup and start the interrupt with the hlt operation.
setupInterruptHlt:
	sti
	hlt
	ret

; Switch to another process by directly far-jmp to an tss selector. 
switchProcess:
	jmp far [esp+4]
	ret

; Output data to the device with the port number. 
outByte:
	mov edx, [esp+4]
	mov al, [esp+8]
	out dx, al
	nop
	nop
	ret

; Input data from the device with the port number.
inByte:
	mov edx, [esp+4]
	xor eax, eax
	in al, dx
	nop
	nop
	ret

; Read large series data with the port number.
readPort:
	mov edx, [esp+4]
	mov edi, [esp+8]
	mov ecx, [esp+12]
	shr ecx, 1
	cld
	rep insw
	ret

; Perform the hlt operation.
startHlt:
	hlt
	ret

; Perform the memcopy operation
memcopy:
	mov edi, [esp+4]
	mov esi, [esp+8]
	mov ecx, [esp+12]

	push es
	push eax
	mov ax, ds
	mov es, ax
	cld
	rep
	movsb

	pop eax
	pop es
	ret

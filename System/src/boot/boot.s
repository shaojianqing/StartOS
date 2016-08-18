
LOADER_START           	equ               	0x0000

LOADER_SEGMENT         	equ             	0x1860

KERNEL_START			equ	 			  	0x8000

ROOT_DEV 				equ 				0x0306
	
	[bits 16]

	jmp start
	db 'StartOS.Developed By Shaojianqing Since 2016-08-04.' 
	db 'This Operating System Is Based On Modern x86 CPU Architecture'
	db 'Has Time Sharing Process Management Method And Other Features!'	 

start:

load_loader:
	mov ah, 0x02
    mov al, 0x04
    mov ch, 0x00
    mov cl, 0x02
    mov dh, 0x00
    mov dl, 0x00
    mov bx, LOADER_SEGMENT
    mov es, bx
    xor bx, bx
    int 0x13
    jnc prepare
    mov	dx,0x00
	mov	ax,0x00
	int	0x13
	jmp	load_loader

prepare:
	mov bx, 0x7c0
	mov ds, bx
	mov bx, KERNEL_START
    mov es, bx
    xor bx, bx

load_kernel1:
	mov ah, 0x02
    mov al, 0x12
    mov ch, 0x00
    mov cl, 0x01
    mov dh, 0x01
    mov dl, 0x00
    int	0x13
    jnc load_kernel2
    mov dx,0x00
    mov ax,0x00
    int 0x13
    jmp load_kernel1

load_kernel2:
    add bx, 9*1024
	mov ah, 0x02
    mov al, 0x12
    mov ch, 0x01
    mov cl, 0x01
    mov dh, 0x00
    mov dl, 0x00
    int	0x13
    jnc stop_motor
    mov dx,0x00
    mov ax,0x00
    int 0x13
    jmp load_kernel2

stop_motor:
    mov dx,0x3f2
	mov al,0x00
	out dx, al

	jmp LOADER_SEGMENT : LOADER_START
 
times 508-($-$$) db 0
	dw ROOT_DEV
	db 0x55,0xaa

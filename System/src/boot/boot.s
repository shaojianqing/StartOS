
LOADER_START           	equ               0x0000

LOADER_SEGMENT         	equ             	0x1860

KERNEL_START						equ	 			  			0x8000

ROOT_DEV 								equ 							0x0306
	
	[bits 16]

	jmp start
	db 'StartOS. Developed By Shaojianqing Since 2016-08-04.' 
	db 'This Operating System Is Based On Modern x86 CPU Architecture'
	db 'Has Time Sharing Process Management Method And Other Features!'	 

start:     
	mov ax, 0x7c0
	mov ds, ax
	mov byte [packageSize], 0x10
	mov byte [reserveByte], 0x00
	mov word [blockCount], 0x01
	mov word [bufferOffs], 0x00
	mov word [bufferSegm], 0x1860
	mov dword [blockNum], 0x01

	mov ah, 0x42
	mov dl, 0x80
	mov si, packageSize
	int 0x13

	jmp LOADER_SEGMENT : LOADER_START  

packageSize: db 0
reserveByte: db 0
blockCount:  dw 0
bufferOffs:  dw 0
bufferSegm:  dw 0
blockNum:    dq 0
 
times 446-($-$$) db 0
	dd	0x0000040			;start sector of partition one
	dd	0x0007FC0			;sector count of partition one
	dd	0x0008000			;start sector of partition two
	dd	0x0008000			;sector count of partition two
times 510-($-$$) db 0
	db 0x55,0xaa

################################
#    Makefile for Smile OS     #
################################

# The general compiling commands #
CP = cp
LD = ld
CC = gcc
AS = nasm

# The Elf file compiling flages #
ELFFLAGES = -f elf 

# The C file compiling flages #
CCFLAGES = -c -m32

# The target file linking flages #
LDFLAGES = -m elf_i386 -s -Ttext

# The start address of the kernel #
KERNELSTART = 0x80000

# The start address of application #
APPLICATIONSTART = 0x0000

# The imageTool command prefix #
IMAGETOOL = java -jar ImageTool.jar

# The copy binary data command #
COPYBINARY = copyBinary

# The trim elf file header command #
TRIMELFHEADER = objcopy -O binary

# The start virtual machine command #
RUN-SYSTEM = VBoxManage startvm StartOS

TGT = tgt/*

EMPTY = Empty.vhd

TARGET = System.vhd

#Booter Target#
BOOT = tgt/boot.bin

#Loader Target#
LOADER = tgt/loader.bin

#Public Object#
PUBLICOBJS = tgt/public.o

#Interrupt Object#
INTERRUPTOBJS = tgt/interrupta.o tgt/interruptc.o 

#Kernel Target#
KERNEL = tgt/kernel.sys

KERNELBIN = tgt/kernel.bin

KERNELOBJS = tgt/ka.o tgt/kc.o

KERNELBIN = tgt/kernel.bin

.PHONY : build clean

build : clean $(TARGET)

clean :
	 rm -f $(TARGET) $(TGT)

rmfiles :
	 rm -f $(TGT)

#---------------------------------------------------------------#
tgt/boot.bin : src/boot/boot.asm
	$(AS) $< -o $@

#---------------------------------------------------------------#
tgt/loader.bin : src/boot/loader.asm src/boot/structure.inc
	$(AS) $< -o $@

tgt/public.o : src/kernel/public/public.asm
	$(AS) $(ELFFLAGES) $< -o $@

#---------------------------------------------------------------#
tgt/ka.o : src/kernel/kernel.asm
	$(AS) $(ELFFLAGES) $< -o $@

tgt/kc.o : src/kernel/kernel.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/kernel.bin : $(KERNELOBJS) $(PUBLICOBJS)
	$(LD) $(LDFLAGES) $(KERNELSTART) $(KERNELOBJS) $(PUBLICOBJS) -o $@

tgt/kernel.sys : $(KERNELBIN)
	$(TRIMELFHEADER) $< $@

#---------------------------------------------------------------#
System.vhd : tgt/boot.bin tgt/loader.bin tgt/kernel.sys
	$(CP) $(EMPTY) $@
	$(IMAGETOOL) $(COPYBINARY) $@ $(BOOT) 0					
	$(IMAGETOOL) $(COPYBINARY) $@ $(LOADER) 512
	$(IMAGETOOL) $(COPYBINARY) $@ $(KERNEL) 36864
	$(RUN-SYSTEM)
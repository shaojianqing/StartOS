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
CREATEIMAGE = createImage

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

#System Object#
SYSTEM = tgt/system.o

#Descriptor Object#
DESCRIPTOR = tgt/descriptor.o

#Interrupt Object#
INTERRUPTOBJS = tgt/interrupt.o 

#Timing Object#
TIMINGOBJS = tgt/timea.o tgt/timec.o

#Keyboard Object#
KEYBOARDOBJS = tgt/keyboarda.o tgt/keyboardc.o

#Harddisk Object#
HARDDISKOBJS = tgt/harddiska.o tgt/harddiskc.o

#Interface Object#
INTERFACEOBJS = tgt/interfacea.o tgt/interfacec.o

#FileSys Object#
FILESYSOBJS = tgt/filesysa.o tgt/filesysc.o

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
tgt/boot.bin : src/boot/boot.s
	$(AS) $< -o $@

#---------------------------------------------------------------#
tgt/loader.bin : src/boot/loader.s src/boot/structure.inc
	$(AS) $< -o $@

#---------------------------------------------------------------#
tgt/system.o : src/kernel/system/system.s
	$(AS) $(ELFFLAGES) $< -o $@

tgt/descriptor.o : src/kernel/system/descriptor.c src/kernel/system/descriptor.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/interrupt.o  : src/kernel/system/interrupt.c src/kernel/system/interrupt.h
	$(CC) $(CCFLAGES) $< -o $@

#---------------------------------------------------------------#
tgt/timea.o : src/kernel/time/time.s
	$(AS) $(ELFFLAGES) $< -o $@

tgt/timec.o : src/kernel/time/time.c src/kernel/time/time.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/keyboarda.o : src/kernel/keyboard/keyboard.s
	$(AS) $(ELFFLAGES) $< -o $@

tgt/keyboardc.o : src/kernel/keyboard/keyboard.c src/kernel/keyboard/keyboard.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/harddiska.o : src/kernel/harddisk/harddisk.s
	$(AS) $(ELFFLAGES) $< -o $@

tgt/harddiskc.o : src/kernel/harddisk/harddisk.c src/kernel/harddisk/harddisk.h
	$(CC) $(CCFLAGES) $< -o $@

#---------------------------------------------------------------#
tgt/interfacec.o : src/kernel/interface/interface.c src/kernel/interface/interface.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/interfacea.o : src/kernel/interface/interface.s
	$(AS) $(ELFFLAGES) $< -o $@

tgt/filesysc.o : src/kernel/library/filesys.c src/kernel/library/filesys.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/filesysa.o : src/kernel/library/filesys.s
	$(AS) $(ELFFLAGES) $< -o $@

#---------------------------------------------------------------#
tgt/ka.o : src/kernel/kernel.s
	$(AS) $(ELFFLAGES) $< -o $@

tgt/kc.o : src/kernel/kernel.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/kernel.bin : $(KERNELOBJS) $(SYSTEM) $(DESCRIPTOR) $(INTERRUPTOBJS) $(TIMINGOBJS) $(KEYBOARDOBJS) $(HARDDISKOBJS) $(INTERFACEOBJS) $(FILESYSOBJS)
	$(LD) $(LDFLAGES) $(KERNELSTART) $(KERNELOBJS) $(SYSTEM) $(DESCRIPTOR) $(INTERRUPTOBJS) $(TIMINGOBJS) $(KEYBOARDOBJS) $(HARDDISKOBJS) $(INTERFACEOBJS) $(FILESYSOBJS) -o $@

tgt/kernel.sys : $(KERNELBIN)
	$(TRIMELFHEADER) $< $@

#---------------------------------------------------------------#
System.vhd : tgt/boot.bin tgt/loader.bin tgt/kernel.sys
	$(CP) $(EMPTY) $@
	$(IMAGETOOL) $(COPYBINARY) $@ $(BOOT) 0					
	$(IMAGETOOL) $(COPYBINARY) $@ $(LOADER) 512
	$(IMAGETOOL) $(COPYBINARY) $@ $(KERNEL) 36864
	$(RUN-SYSTEM)
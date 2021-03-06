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
CCFLAGES = -c -m32 -O0 -fno-builtin

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

IMAGE_SIZE = 1474560

TGT = tgt/*

EMPTY = Empty.vhd

TARGET = System.vhd

DISK = System.vhd

IMAGE = Image.bin

#Booter Target#
BOOT = tgt/boot.bin

#Loader Target#
LOADER = tgt/loader.bin

#System Object#
SYSTEM = tgt/systema.o tgt/systemc.o

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

#Console Object#
CONSOLEOBJS = tgt/console.o 

#FileSystem Object#
FILESYSTEMOBJS = tgt/filesystem.o

#Data Object#
DATAOBJS = tgt/data.o

#Cache Object#
CACHEOBJS = tgt/cache.o

#String Object#
STRINGOBJS = tgt/string.o

#Stat Object#
PRINTEROBJS = tgt/printer.o

#Stat Object#
STATOBJS = tgt/stat.o

#Pipe Object#
PIPEOBJS = tgt/pipe.o

#Charset Object#
CHARSETOBJS = tgt/charset.o

#Namei Object#
NAMEIOBJS = tgt/namei.o

#Signal Object#
SIGNALOBJS = tgt/signal.o

#Process Object#
PROCESSOBJS = tgt/process.o

#Memory Object#
MEMORYOBJS = tgt/memory.o

#Interface Object#
INTERFACEOBJS = tgt/interfacea.o tgt/interfacec.o

#FileSys Object#
FILESYSOBJS = tgt/filesysa.o tgt/filesysc.o

#Block Object#
BLOCKOBJS = tgt/block.o

#Printer Object#
PRINTEROBJS = tgt/printerc.o tgt/printera.o

#Kernel Target#
KERNEL = tgt/kernel.sys

KERNELBIN = tgt/kernel.bin

KERNELOBJS = tgt/ka.o tgt/kc.o

KERNELBIN = tgt/kernel.bin

.PHONY : build

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
tgt/systema.o : src/kernel/system/system.s
	$(AS) $(ELFFLAGES) $< -o $@

tgt/systemc.o : src/kernel/system/system.c src/kernel/system/system.h
	$(CC) $(CCFLAGES) $< -o $@

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

tgt/filesystem.o : src/kernel/filesys/filesys.c src/kernel/filesys/filesys.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/namei.o : src/kernel/filesys/namei.c src/kernel/filesys/namei.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/charset.o : src/kernel/charset/charset.c src/kernel/charset/charset.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/signal.o : src/kernel/signal/signal.c src/kernel/signal/signal.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/data.o : src/kernel/filesys/data.c src/kernel/filesys/data.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/stat.o : src/kernel/filesys/stat.c src/kernel/filesys/stat.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/pipe.o : src/kernel/filesys/pipe.c src/kernel/filesys/pipe.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/cache.o : src/kernel/filesys/cache.c src/kernel/filesys/cache.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/process.o : src/kernel/process/process.c src/kernel/process/process.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/memory.o : src/kernel/memory/memory.c src/kernel/memory/memory.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/block.o : src/kernel/filesys/block.c src/kernel/filesys/block.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/string.o : src/kernel/string/string.c src/kernel/string/string.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/printerc.o : src/kernel/keyboard/printer.c src/kernel/keyboard/printer.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/filesysa.o : src/kernel/library/filesys.s
	$(AS) $(ELFFLAGES) $< -o $@

#---------------------------------------------------------------#
tgt/interfacec.o : src/kernel/interface/interface.c src/kernel/interface/interface.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/interfacea.o : src/kernel/interface/interface.s
	$(AS) $(ELFFLAGES) $< -o $@

tgt/filesysc.o : src/kernel/library/filesys.c src/kernel/library/filesys.h
	$(CC) $(CCFLAGES) $< -o $@

tgt/printera.o : src/kernel/keyboard/printer.s
	$(AS) $(ELFFLAGES) $< -o $@

#---------------------------------------------------------------#
tgt/console.o : src/kernel/console/console.c
	$(CC) $(CCFLAGES) $< -o $@

#---------------------------------------------------------------#
tgt/ka.o : src/kernel/kernel.s
	$(AS) $(ELFFLAGES) $< -o $@

tgt/kc.o : src/kernel/kernel.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/kernel.bin : $(KERNELOBJS) $(SYSTEM) $(DESCRIPTOR) $(INTERRUPTOBJS) $(TIMINGOBJS) $(KEYBOARDOBJS) $(HARDDISKOBJS) $(INTERFACEOBJS) $(FILESYSOBJS) $(FILESYSTEMOBJS) $(NAMEIOBJS) $(DATAOBJS) $(PIPEOBJS) $(PROCESSOBJS) $(CACHEOBJS) $(STATOBJS) $(BLOCKOBJS) $(CHARSETOBJS) $(CONSOLEOBJS) $(MEMORYOBJS) $(PRINTEROBJS) $(STRINGOBJS)
	$(LD) $(LDFLAGES) $(KERNELSTART) $(KERNELOBJS) $(SYSTEM) $(DESCRIPTOR) $(INTERRUPTOBJS) $(TIMINGOBJS) $(KEYBOARDOBJS) $(HARDDISKOBJS) $(INTERFACEOBJS) $(FILESYSOBJS) $(FILESYSTEMOBJS) $(NAMEIOBJS) $(DATAOBJS) $(PIPEOBJS) $(PROCESSOBJS) $(CACHEOBJS) $(STATOBJS) $(BLOCKOBJS) $(CHARSETOBJS) $(CONSOLEOBJS) $(MEMORYOBJS) $(PRINTEROBJS) $(STRINGOBJS) -o $@

tgt/kernel.sys : $(KERNELBIN)
	$(TRIMELFHEADER) $< $@

#---------------------------------------------------------------#
System.vhd : tgt/boot.bin tgt/loader.bin tgt/kernel.sys
	$(CP) $(EMPTY) $@
	$(IMAGETOOL) $(COPYBINARY) $@ $(BOOT) 0					
	$(IMAGETOOL) $(COPYBINARY) $@ $(LOADER) 512
	$(IMAGETOOL) $(COPYBINARY) $@ $(KERNEL) 9216
	$(IMAGETOOL) $(COPYBINARY) $@ $(IMAGE) 16777216

	$(RUN-SYSTEM)

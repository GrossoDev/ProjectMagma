CFLAGS      := -m32 -fno-stack-protector -ffreestanding -fno-builtin -O -g -I ./include/ -D DEBUG -D ARCH_i386
LDFLAGS     := -m elf_i386
SRCPATH     := ./src/
BUILDPATH   := ./build/
BINPATH     := ./bin/
INSTALLPATH := /magma/latest-build/

i386:
	make i386-compile
	make i386-link
	make clean

i386-grub:
	make i386-compile
	make i386-link
	make grub
	make clean

i386-compile:
	make i386-compile-asm
	make generic-compile-c
	make i386-compile-c

i386-compile-asm:
	# HACK: Put 01 at the start of the filename
	# so it's the first one to be read by any
	# command that uses the wildcard (*)
	nasm -f elf -o $(BUILDPATH)1-compile/01-start.o $(SRCPATH)ARCH/i386/asm/start.asm
	nasm -f elf -o $(BUILDPATH)1-compile/asm-gdt.o $(SRCPATH)ARCH/i386/asm/gdt.asm
	nasm -f elf -o $(BUILDPATH)1-compile/asm-idt.o $(SRCPATH)ARCH/i386/asm/idt.asm
	nasm -f elf -o $(BUILDPATH)1-compile/asm-irqs.o $(SRCPATH)ARCH/i386/asm/irqs.asm
	nasm -f elf -o $(BUILDPATH)1-compile/asm-syscall.o $(SRCPATH)ARCH/i386/asm/syscall.asm
	nasm -f elf -o $(BUILDPATH)1-compile/asm-paging.o $(SRCPATH)ARCH/i386/asm/paging.asm
	nasm -f elf -o $(BUILDPATH)1-compile/asm-io.o $(SRCPATH)ARCH/i386/asm/io.asm

i386-compile-c:
	gcc $(CFLAGS) -c -o $(BUILDPATH)1-compile/gdt.o $(SRCPATH)ARCH/i386/c/int/gdt.c
	gcc $(CFLAGS) -c -o $(BUILDPATH)1-compile/idt.o $(SRCPATH)ARCH/i386/c/int/idt.c
	gcc $(CFLAGS) -c -o $(BUILDPATH)1-compile/irq.o $(SRCPATH)ARCH/i386/c/int/irq.c
	gcc $(CFLAGS) -c -o $(BUILDPATH)1-compile/isrs.o $(SRCPATH)ARCH/i386/c/int/isrs.c
	gcc $(CFLAGS) -c -o $(BUILDPATH)1-compile/debug.o $(SRCPATH)ARCH/i386/c/debug.c	

generic-compile-c:
	gcc $(CFLAGS) -c -o $(BUILDPATH)1-compile/main.o $(SRCPATH)c/main.c
	gcc $(CFLAGS) -c -o $(BUILDPATH)1-compile/math.o $(SRCPATH)c/helpers/math.c
	gcc $(CFLAGS) -c -o $(BUILDPATH)1-compile/string.o $(SRCPATH)c/helpers/string.c
	gcc $(CFLAGS) -c -o $(BUILDPATH)1-compile/syscall.o $(SRCPATH)c/syscall.c
	gcc $(CFLAGS) -c -o $(BUILDPATH)1-compile/paging.o $(SRCPATH)c/paging.c

i386-link:
	ld -T $(SRCPATH)link.ld -o $(BUILDPATH)2-link/kernel.bin $(BUILDPATH)1-compile/*.o $(LDFLAGS)
	mcopy -n $(BUILDPATH)2-link/kernel.bin $(BINPATH)

grub: $(SRCPATH)grub/boot/grub/grub.cfg
	cp -R ./src/grub/boot ./build/3-grub
	mcopy -n $(BUILDPATH)2-link/kernel.bin $(BUILDPATH)3-grub/
	grub-mkrescue -o ./bin/magma.iso $(BUILDPATH)3-grub/

clean:
	rm -rf $(BUILDPATH)1-compile/*.*
	rm -rf $(BUILDPATH)2-link/*.*
	rm -rf $(BUILDPATH)3-grub/*.*

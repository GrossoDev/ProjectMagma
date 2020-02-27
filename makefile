NASMFLAGS := -f elf -d DEBUG -i src/arch/i386/
LDFLAGS   := -m elf_i386 -Ttext 0x0

debug:
	make structure
	make i386-compile
	make i386-compile-debug
	make i386-link
	make iso

i386:
	make structure
	make i386-compile
	make i386-link
	make iso
	make clean

structure:
	mkdir -p bin
	mkdir -p build
	mkdir -p build/1-compile
	mkdir -p build/2-link
	mkdir -p build/3-grub

i386-compile:
	nasm $(NASMFLAGS) -o build/1-compile/01-multiboot-bootstrap.o src/arch/i386/boot/multiboot-bootstrap.asm
	nasm $(NASMFLAGS) -o build/1-compile/kernel_install.o src/arch/i386/kernel_install.asm
	
i386-compile-debug:
	nasm $(NASMFLAGS) -o build/1-compile/debug_install.o src/arch/i386/debug/debug_install.asm
	nasm $(NASMFLAGS) -o build/1-compile/debug_vga_driver.o src/arch/i386/debug/debug_vga_driver.asm
	nasm $(NASMFLAGS) -o build/1-compile/debug_serial_driver.o src/arch/i386/debug/debug_serial_driver.asm
	nasm $(NASMFLAGS) -o build/1-compile/debug_print.o src/arch/i386/debug/debug_print.asm

i386-link:
	ld -T src/link.ld -o build/2-link/kernel.bin build/1-compile/*.o $(LDFLAGS)
	mcopy -n build/2-link/kernel.bin bin

iso: src/grub/boot/grub/grub.cfg
	cp -R src/grub/boot build/3-grub
	mcopy -n bin/kernel.bin build/3-grub/
	grub-mkrescue -o bin/magma.iso build/3-grub/

clean:
	rm -rf build/1-compile/*.*
	rm -rf build/2-link/*.*
	rm -rf build/3-grub/*.*

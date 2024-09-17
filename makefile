
build_boot:
	as --32 boot.asm -o  boot.o

build_src:
	gcc -m32 -c srcs/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Werror

link_kernel:
	ld -m elf_i386 -T linker.ld kernel.o boot.o -o Kairnail.bin -nostdlib

check_grub:
	grub-file --is-x86-multiboot Kairnail.bin

build_iso:
	mkdir -p isodir/boot/grub
	cp Kairnail.bin isodir/boot/Kairnail.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o Kairnail.iso isodir

run:	
	qemu-system-x86_64 -cdrom Kairnail.iso

build:
	make build_boot
	make build_src
	make link_kernel
	make check_grub
	make build_iso




.DEFAULT_GOAL := all

NAME        = kfs.bin
SRC_DIR     = srcs
OBJS_DIR    = .objs

# Source and object files
C_SRCS      = $(shell find $(SRC_DIR) -name '*.c')
ASM_SRCS    = $(shell find $(SRC_DIR) -name '*.asm')
OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJS_DIR)/%.o, $(C_SRCS)) \
              $(patsubst $(SRC_DIR)/%.asm, $(OBJS_DIR)/%.o, $(ASM_SRCS))

# Include directories
INCL        = $(addprefix -I, $(shell find $(SRC_DIR) -type d))

# Tools
CC          = gcc
AS          = nasm
LD          = ld
CFLAGS      = -m32 -std=gnu99 -ffreestanding -Wall -Wextra
ASFLAGS     = -felf32
LDFLAGS     = -m elf_i386 -nostdlib

# Linker script
LINKER_FILE = ./linker.ld

# Build objects
build_objects: $(OBJS)

# Compile C source files
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "\033[0;33mCompiling C object... %-38.38s \r" $@
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL)

# Compile Assembly source files
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.asm
	@printf "\033[0;33mCompiling ASM object... %-38.38s \r" $@
	@mkdir -p $(dir $@)
	@$(AS) $(ASFLAGS) $< -o $@

# Link kernel
$(NAME): build_objects
	@echo "\033[0;32m\nLinking... $(NAME)\033[0m"
	@$(LD) $(LDFLAGS) -T $(LINKER_FILE) -o $(NAME) $(OBJS)
	@make build_iso
	@make run
	@echo "\033[1;32mKfs: Goodbye! :)) \033[0m"

# Default target
all: $(NAME)

# Clean object files
clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJS_DIR)
	@echo "\033[1;31mObjects cleaned!\033[0m"

# Full clean (including the final program)
fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;31mProgram cleaned!\033[0m"
	@rm -f kfs.bin.iso
	@rm -rf isodir
	@echo "\033[1;31mIso cleaned!\033[0m"

# Rebuild everything
re: fclean all

# Check if the binary is multiboot-compliant
check_grub:
	@grub-file --is-x86-multiboot $(NAME)

# Build ISO for running on an emulator
build_iso:
	@mkdir -p isodir/boot/grub
	@cp $(NAME) isodir/boot/$(NAME)
	@cp grub.cfg isodir/boot/grub/grub.cfg
	@echo "\033[1;32mKfs: Building iso...\033[0m"
	@grub-mkrescue -o $(NAME).iso isodir

# Run the program in QEMU
run:
	@echo "\033[1;32mKfs: Running kfs...\033[0m"
	@qemu-system-x86_64 -cdrom $(NAME).iso -display sdl

# Run the program in QEMU
run-debug:
	@echo "\033[1;32mKfs: Running kfs...\033[0m"
	@qemu-system-x86_64 -cdrom $(NAME).iso -display sdl -d int

# Build everything (check multiboot, build ISO)
build: $(NAME)
	$(MAKE) check_grub
	$(MAKE) build_iso

.PHONY: all clean fclean re check_grub build_iso run build run-debug

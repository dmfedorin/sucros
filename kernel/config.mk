K_SRC_DIR := src
K_INC_DIR := inc
K_LIB_DIR := lib

K_OUT_BIN := kernel

K_CC := x86_64-elf-gcc
K_AS := x86_64-elf-as
K_LD := x86_64-elf-gcc

K_CFLAGS := \
	-std=c99 \
	-pedantic \
	-c \
	-I$(K_INC_DIR) \
	-I../deps/limine \
	-I../deps/font8x8 \
	-ffreestanding \
	-fPIC \
	-mno-red-zone

K_ASFLAGS :=
K_LDFLAGS := -Tkernel.ld -ffreestanding -nostdlib -lgcc -z max-page-size=4096

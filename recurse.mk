ARMGNU ?= aarch64-linux-gnu

COPS += -g -Wall -nostdlib -I../include -I../driver/include -I../arch -mgeneral-regs-only -I../fs/include -I../dev/include
ASMOPS = -g -I../include -I../driver/include

COPS += -fno-builtin-strlen -fno-builtin-memcpy -fno-builtin-putchar -fno-builtin-memset -fno-builtin-strcpy -fno-builtin-strcmp -fno-builtin-strncmp -fno-builtin-strncpy

COPS += -Wno-unused -Wno-noreturn -Wno-return-type

OBJ = obj

all: compiler

C_FILES = $(wildcard *.c)
ASM_FILES = $(wildcard *.S)

OBJ_FILES = $(C_FILES:%.c=$(OBJ)/%_c.o)
OBJ_FILES += $(ASM_FILES:%.S=$(OBJ)/%_s.o)

compiler: $(OBJ_FILES)

$(OBJ)/%_c.o: %.c
	mkdir -p obj
	$(ARMGNU)-gcc $(COPS) -c $< -o $@

$(OBJ)/%_s.o: %.S
	mkdir -p obj
	$(ARMGNU)-gcc $(ASMOPS) -c $< -o $@

clean:
	rm -rf obj/
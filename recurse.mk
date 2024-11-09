ARMGNU ?= aarch64-linux-gnu

CFLAGS += -g
CFLAGS += -Wall -Wno-unused -Wno-return-type 
CFLAGS += -nostdlib -fno-builtin -mgeneral-regs-only

INC_PATH += -I../include \
			-I../driver/include \
			-I../fs/include \
			-I../dev/include \
			-I../driver/include \

OBJ = obj

all: compile

C_FILES = $(wildcard *.c)
ASM_FILES = $(wildcard *.S)

OBJ_FILES = $(C_FILES:%.c=$(OBJ)/%_c.o)
OBJ_FILES += $(ASM_FILES:%.S=$(OBJ)/%_s.o)

compile: $(OBJ_FILES)

$(OBJ)/%_c.o: %.c
	mkdir -p obj
	$(ARMGNU)-gcc $(CFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/%_s.o: %.S
	mkdir -p obj
	$(ARMGNU)-gcc $(CFLAGS) $(INC_PATH) -c $< -o $@

clean:
	rm -rf obj/
ARM64_PREFIX ?= aarch64-linux-gnu

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

SRC_FILES = $(wildcard *.c *.S)

OBJ_FILES = $(SRC_FILES:%.c=$(OBJ)/%.o) \
			 $(SRC_FILES:%.S=$(OBJ)/%.o)

compile: $(OBJ_FILES)

$(OBJ)/%.o: %.c
	mkdir -p obj
	$(ARM64_PREFIX)-gcc $(CFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/%.o: %.S
	mkdir -p obj
	$(ARM64_PREFIX)-gcc $(CFLAGS) $(INC_PATH) -c $< -o $@

clean:
	rm -rf obj/
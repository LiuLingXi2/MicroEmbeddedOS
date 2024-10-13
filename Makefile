ARMGNU ?= aarch64-linux-gnu

board ?= rpi4

ifeq ($(board), rpi3)
COPS += -DCONFIG_BOARD_PI3B
QEMU_FLAGS  += -machine raspi3
else ifeq ($(board), rpi4)
COPS += -DCONFIG_BOARD_PI4B
QEMU_FLAGS  += -machine raspi4b1g
endif

COPS += -g -Wall -nostdlib -Iinclude -mgeneral-regs-only
ASMOPS = -g -Iinclude 

COPS += -fno-builtin-strlen -fno-builtin-memcpy -fno-builtin-putchar

# COPS +=  -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strcmp -fno-builtin-strncpy -fno-builtin-strncat -fno-builtin-strncmp -fno-builtin-strchr -fno-builtin-strstr -fno-builtin-strtok  -fno-builtin-memset  -fno-builtin-memmove 

BUILD_DIR = build
SRC_DIR = src
SCRIPTS_DIR = scripts

all : aarch_test.bin

clean :
	rm -rf *.bin *.elf *.map build/*

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.S)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)


aarch_test.bin: aarch64_linker.ld $(OBJ_FILES)
	$(ARMGNU)-ld -T aarch64_linker.ld -Map $(BUILD_DIR)/aarch_test.map -o $(BUILD_DIR)/aarch_test.elf  $(OBJ_FILES)
	$(ARMGNU)-objcopy $(BUILD_DIR)/aarch_test.elf -O binary $(BUILD_DIR)/aarch_test.bin

QEMU_FLAGS  += -nographic

run:
	qemu-system-aarch64 $(QEMU_FLAGS) -kernel $(BUILD_DIR)/aarch_test.bin
debug:
	qemu-system-aarch64 $(QEMU_FLAGS) -kernel $(BUILD_DIR)/aarch_test.bin -S -s

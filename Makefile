# system
ARMGNU ?= aarch64-linux-gnu
MAKE ?= make

PROJECT = ma_a

# qemu
QEMU_FLAGS  += -machine raspi4b1g
QEMU_FLAGS  += -nographic

BUILD_DIR 	= build
LD_DIR 		= boot
OBJ 		= obj

OBJS = $(shell find . -name "*.o")

all : compile_o compile_b

compile_o:
	$(MAKE) -C test
	$(MAKE) -C boot
	$(MAKE) -C kernel
	$(MAKE) -C mm
	$(MAKE) -C driver
	$(MAKE) -C std
	$(MAKE) -C arch
	$(MAKE) -C fs

compile_b: $(LD_DIR)/alinker.ld
	$(ARMGNU)-ld -T $< -Map $(BUILD_DIR)/$(PRO_NAME).map -o $(BUILD_DIR)/$(PRO_NAME).elf $(OBJS)
	$(ARMGNU)-objcopy $(BUILD_DIR)/$(PRO_NAME).elf -O binary $(BUILD_DIR)/$(PRO_NAME).bin

clean :
	$(MAKE) -C test clean
	$(MAKE) -C boot clean
	$(MAKE) -C kernel clean
	$(MAKE) -C mm clean
	$(MAKE) -C driver clean
	$(MAKE) -C std clean
	$(MAKE) -C arch clean
	$(MAKE) -C fs clean

	rm -rf  $(BUILD_DIR)/*

run:
	qemu-system-aarch64 $(QEMU_FLAGS) -kernel $(BUILD_DIR)/$(PRO_NAME).bin
debug:
	qemu-system-aarch64 $(QEMU_FLAGS) -kernel $(BUILD_DIR)/$(PRO_NAME).bin -S -s
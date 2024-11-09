# MicroEmbeddedOS

> Some things, only to do their own, will feel something

## 内核信息

PBASE: address of peripheral

```c
#define PBASE 0xFE000000
```

GIC_BASE_ADDR：address of GIC

```c
#define GIC_BASE_ADDR (0xFF840000)
```

address of kernel loading

```shell
	. = 0x80000, 
```

## kernel

```shell
make clean
make
make run
```

debug

```shell
make debug
```

```shell
bash gdb.sh
```

running goal

```shell
qemu-system-aarch64 -machine raspi4b1g -nographic -kernel build/aarch_test.bin
Welcome MicroEmbeddedOS v0.1 (2024 10-15)

 /\_/\      /\_/\      /\_/\
( o.o )    ( o.o )    ( o.o )
 > ^ <      > ^ <      > ^ <

Image layout:
  .text.boot: 0x00080000 - 0x00080080 (   128 B)
       .text: 0x00080080 - 0x00084858 ( 18392 B)
     .rodata: 0x00084858 - 0x00084c70 (  1048 B)
       .data: 0x00084c70 - 0x00087000 (  9104 B)
        .bss: 0x00087000 - 0x000e7444 (394308 B)

microembeeded os loading address: 0x00080000
memory: 4294967292KB available, 0 free pages
identify mapping done
enable mmu done
test_access_map_address: [ access 0x1ffff000 done ]
Bad mode for Sync Abort handler detected, far:0x20001000 esr:0x96000046
gic_init [ cpu_base:0xff842000, dist_base:0xff841000, gic_irqs:160 ]
```

### process manage

directory: kernel/

description: preemptive switching with priority based scheduling policy (clock interrupt based)


### virtual ssd

directory: dev/

description: the maximum capacity is 128KB, and each data block is read and written with a size of 4KB

interface
- ssd_read_block
- ssd_write_block

### file system

directory: fs/

description: implement an ext2-like file system

interface:
- fs_create
- fs_write
- fs_read
- fs_close

### mlog subsystem

directory: mlog/


expected subsystem plan

- mlog subsystem ×
- directory tidy √
- process manage --->>>
- shell implement ×
- driver manage --->>>
# MicroEmbeddedOS

> Some things, only to do their own, will feel something

## kernel infomation

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
qemu-system-aarch64 -machine raspi4b1g -nographic -kernel build/ma_a.bin
Welcome MicroEmbeddedOS v0.1 (2024 10-15)

 /\_/\      /\_/\      /\_/\
( o.o )    ( o.o )    ( o.o )
 > ^ <      > ^ <      > ^ <

Image layout:
  .text.boot: 0x00080000 - 0x00080080 (   128 B)
       .text: 0x00080080 - 0x00087164 ( 28900 B)
     .rodata: 0x00087164 - 0x00087aaa (  2374 B)
       .data: 0x00087aaa - 0x0008c000 ( 17750 B)
        .bss: 0x0008c000 - 0x001444f8 (754936 B)

microembeeded os loading address: 0x00080000
memory: 522988KB available, 130747 free pages
idmap_pg_dir: 0x0008b000
mem_map address: 0x00400000
alloc_page: allocate page address: 0x00400000
alloc_page: allocate page address: 0x00401000
alloc_page: allocate page address: 0x00402000
identify mapping done
alloc_page: allocate page address: 0x00403000
enable mmu done
alloc_page: allocate page address: 0x00404000
alloc_page: allocate page address: 0x00405000
alloc_page: allocate page address: 0x00406000
test_access_map_address: [ access 0x1ffff000 done ]
Bad mode for Sync Abort handler detected, far:0x20001000 esr:0x96000046
gic_init [ cpu_base:0xff842000, dist_base:0xff841000, gic_irqs:160 ]
ssd_memory sram address: 0x000ac460
ssd_memory end sram address: 0x000cc45f


add_inode_to_directory: parent dir is root?
create root dir success:  /
home
tmp
usr
var
root
boot
sys
fs has initialized!
liuzixuan-shell /> Core0 Local Timer interrupt received
current pid: 0
pick_next_task_kernel: pick next thread (pid 1)
kernel_thread1: 10
pick_next_task_kernel: pick next thread (pid 3)
kernel_thread3: 3
pick_next_task_kernel: pick next thread (pid 2)
Core0 Local Timer interrupt received
current pid: 2
pick_next_task_kernel: pick next thread (pid 2)
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
- ext2fs_create
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
# MicroEmbeddedOS

> 有些事情，只有自己去做了，才会去感知一些东西

## 内核信息

PBASE：外设地址

```c
#define PBASE 0xFE000000
```

GIC_BASE_ADDR：GIC地址

```c
#define GIC_BASE_ADDR (0xFF840000)
```

内核加载地址

```shell
	. = 0x80000, 
```

## 运行内核

```shell
make clean
make
make run
```

debug状态

```shell
make debug
```

```shell
bash gdb.sh
```

运行效果

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

当前进度和计划

- 日志系统
- 目录规整
- 进程管理
- shell实现
- 驱动实现
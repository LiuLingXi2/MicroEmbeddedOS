# MicroEmbeddedOS

> 有些事情，只有自己去做了，才会去感知一些东西

## address

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

## gdb cao

查看当前线程数

```shell
(gdb) info threads
  Id   Target Id                    Frame
* 1    Thread 1.1 (CPU#0 [running]) _start () at src/boot.S:8
  2    Thread 1.2 (CPU#1 [running]) 0x000000000000030c in ?? ()
  3    Thread 1.3 (CPU#2 [running]) 0x000000000000030c in ?? ()
  4    Thread 1.4 (CPU#3 [running]) 0x000000000000030c in ?? ()
```

设置只在线程`1.1`执行

```shell
(gdb) thread 1.1
[Switching to thread 1 (Thread 1.1)]
#0  _start () at src/boot.S:8
```

查看线程栈信息

```shell
(gdb) thread apply 1 bt
```

## register infomation

**mpidr_el**

`raspi 4b`四个`core，每一个`core`都有自己的`mpidr_el1`(ro)，

0-7位标识`core id`

**esr_el1**

存放访问失效相关的寄存器

**far_el1**

获取异常发生虚拟地址
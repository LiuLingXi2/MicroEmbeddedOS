#ifndef	__P_BASE_H__
#define	__P_BASE_H__

#ifdef CONFIG_BOARD_PI3B
#define PBASE 0x3F000000
#else
#define PBASE 0xFE000000
#endif

#define DEVICE_SIZE 0x2000000
#define ARCH_PHYS_OFFSET 0

#endif  // !__P_BASE_H__

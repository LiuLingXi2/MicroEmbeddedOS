#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__

#include "asm/base.h"

/* System Timer on PI */
#define TIMER_CS        (PBASE + 0x00003000)
#define TIMER_CLO       (PBASE + 0x00003004)
#define TIMER_CHI       (PBASE + 0x00003008)
#define TIMER_C0        (PBASE + 0x0000300C) 
#define TIMER_C1        (PBASE + 0x00003010)
#define TIMER_C2        (PBASE + 0x00003014)
#define TIMER_C3        (PBASE + 0x00003018)

#define TIMER_CS_M0	(1 << 0)
#define TIMER_CS_M1	(1 << 1)
#define TIMER_CS_M2	(1 << 2)
#define TIMER_CS_M3	(1 << 3)

void local_timer_init(void);
void handle_timer_irq(void);

void system_timer_init(void);
void handle_stimer_irq(void);

#endif // !__INCLUDE_TIMER_H__
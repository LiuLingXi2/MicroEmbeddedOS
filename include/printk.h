#ifndef __INCLUDE_PRINTK_H__
#define __INCLUDE_PRINTK_H__

void printk_init(void);
int  printk(const char *fmt, ...);

#endif // !__INCLUDE_PRINTK_H__
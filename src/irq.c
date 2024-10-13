#include "irq.h"
#include "gic.h"

void irq_handle(void)
{
    gic_handle_irq();
}
#include "test_define.h"
#include "reg_offset.h"

    .section ".text.boot"

.global _start
_start:
    b test_main
    b proc_main

proc_main:
    b proc_main

e12_entry:
    
    eret
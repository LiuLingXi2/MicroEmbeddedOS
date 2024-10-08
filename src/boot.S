#include "../include/define.h"


    .section ".text.boot"

.global _start
_start:
    b test_main
    b proc_main

proc_main:
    b proc_main

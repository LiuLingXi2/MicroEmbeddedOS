# !/bin/bash

gdb-multiarch --tui -x scripts/boot_s.gdb build/ma_a.elf
target remote localhost:1234

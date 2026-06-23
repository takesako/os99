#!/bin/bash
set -xue
QEMU=qemu-system-riscv32
CC=/opt/homebrew/opt/llvm/bin/clang
CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf -fuse-ld=lld -fno-stack-protector -ffreestanding -nostdlib"
$CC $CFLAGS -Wl,-Tboot.ld -Wl,-Map=os.map -o os.elf kernel.c printf.c main.c
$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot -kernel os.elf

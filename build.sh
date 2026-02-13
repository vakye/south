#!/bin/bash

if [ ! -d ./build ]; then
    mkdir -p build
fi;

CompileFlags="-std=c11 -Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -g -O0 -target x86_64-unknown-windows -ffreestanding -mno-red-zone -mno-stack-arg-probe -fuse-ld=lld -nostdlib"
LinkFlags="-Wl,-nodefaultlib,-subsystem:efi_application,-entry:UEFIBoot"

cd build
clang $CompileFlags -o BOOTX64.EFI "../code/uefi.c" $LinkFlags
../tools/write_gpt -i south.img
cd ..

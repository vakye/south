
@echo off

if not exist build mkdir build

set CompileFlags=-std=c11 -Wall -Wextra -Wpedantic -O0 -target x86_64-unknown-windows -ffreestanding -mno-red-zone -mno-stack-arg-probe -nostdlib -fuse-ld=lld -nostdlib
set LinkFlags=-Wl,-nodefaultlib,-subsystem:efi_application,-entry:UEFIBoot

pushd build
call clang %CompileFlags% -o BOOTX64.EFI "..\code\uefi.c" %LinkFlags%
call ..\tools\write_gpt -i south.img
popd


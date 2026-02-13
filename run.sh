
qemu-system-x86_64 -machine q35 -m 256 -drive format=raw,index=0,file=build/south.img -bios bios/OVMF.fd

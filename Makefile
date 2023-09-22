OBJS = entry.o main.o

CC = riscv64-unknown-elf-gcc
CFLAGS = -ggdb

kernel: $(OBJS)
	@riscv64-unknown-elf-ld -T kernel.ld -o kernel $(OBJS)

run:
	@qemu-system-riscv64 \
		-machine virt \
		-nographic \
		-bios none \
		-kernel kernel

clean: 
	@rm *.o kernel

run-gdb:
	@qemu-system-riscv64 \
		-machine virt \
		-nographic \
		-bios none \
		-kernel kernel \
		-s -S 

gdb:
	@gdb-multiarch \
    -ex 'file kernel' \
    -ex 'set arch riscv:rv64' \
    -ex 'target remote localhost:1234'
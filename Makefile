OBJS = entry.o main.o uart.o task.o switch.o common.o trapvec.o timer.o trap.o riscv.o

CC = riscv64-unknown-elf-gcc
CFLAGS = -ggdb # 产生用于 gdb 的调试信息
CFLAGS += -ffreestanding -nostdlib # 告诉编译器标准库可能不存在，不连接系统标准库
CFLAGS += -O0 # 不进行优化处理
CFLAGS += -Wall -Werror # 生成所有警告信息，把警告视为错误
CFLAGS += -mcmodel=medany # 在 -2-2GB 内寻址

kernel: $(OBJS)
	@riscv64-unknown-elf-ld -T kernel.ld -o kernel $(OBJS)

run:
	@qemu-system-riscv64 \
		-machine virt \
		-nographic \
		-bios none \
		-kernel kernel

clean: 
	@rm -f *.o kernel

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

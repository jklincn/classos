# 铁人三项 OS 部分

## 内容规划

- [x] 在 QEMU （8.1.0）上启动
- [ ] 在 FPGA 上启动
- [x] uart 串口输出
- [x] 简单的进程管理（进程创建、进程运行、进程切换）
- [x] 基于时钟中断的抢占式调度
- [ ] 干净的分级目录

## 快速入门

### 安装 QEMU

https://www.qemu.org/download/

https://wiki.qemu.org/Hosts/Linux

### 安装 RISC-V 工具链

```
# 假设使用 Ubuntu 发行版
sudo apt update
sudo apt install gcc-riscv64-unknown-elf gdb-multiarch
```

### 运行本项目

```
git clone https://github.com/jklincn/classos.git
cd classos
make kernel
make run
```

如果一切正常，将会看到 3 个进程切换运行：

```
Hello, OS!
this is task [1]!
this is task[2] schedule 1 times
**********
*        *
*        *
*        *
**********
this is task [1]!
this is task[2] schedule 2 times
**********
*        *
*        *
*        *
**********
this is task [1]!
this is task[2] schedule 3 times
**********
*        *
*        *
*        *
**********
```

## 文件说明

```
.
├── Makefile
├── README.md
├── common.c	// 一些功能函数
├── common.h	// 全局头文件，定义了结构体与函数
├── entry.S		// 操作系统入口
├── kernel.ld	// 链接脚本，定义了内存布局
├── main.c		// 主函数，负责初始化与进程创建
├── riscv.c		// RISC-V 相关的函数，主要是寄存器读写的封装
├── switch.S	// 进程上下文切换
├── task.c		// 进程管理模块
├── timer.c		// 时钟中断模块
├── trap.c		// 异常模块
├── trapvec.S	// 中断入口，中断上下文切换
└── uart.c		// uart 串口模块
```


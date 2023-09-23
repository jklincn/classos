/*
    useful website:
    http://www.byterunner.com/16550.html
    https://www.lammertbies.nl/comm/info/serial-uart
    https://dingfen.github.io/risc-v/2020/08/01/riscv-from-scratch-4.html
*/
#include "common.h"
#define REG_RHR 0 // read mode: Receive holding reg
#define REG_THR 0 // write mode: Transmit Holding Reg
#define REG_IER 1 // write mode: interrupt enable reg
#define REG_FCR 2 // write mode: FIFO control Reg
#define REG_ISR 2 // read mode: Interrupt Status Reg
#define REG_LCR 3 // write mode:Line Control Reg
#define REG_MCR 4 // write mode:Modem Control Reg
#define REG_LSR 5 // read mode: Line Status Reg
#define REG_MSR 6 // read mode: Modem Status Reg

#define UART_DLL 0 // LSB of divisor Latch when enabled
#define UART_DLM 1 // MSB of divisor Latch when enabled

#define UART_BASE_ADDR 0x10000000L

#define Reg(reg) ((volatile unsigned char *)(UART_BASE_ADDR + reg))
#define ReadReg(reg) (*(Reg(reg)))
#define WriteReg(reg, v) (*(Reg(reg)) = (v))

static char digits[] = "0123456789abcdef";

void uartinit() {
  // disable interrupt
  WriteReg(REG_IER, 0x00);
  // set baud rate
  WriteReg(REG_LCR, 0x80);
  WriteReg(UART_DLL, 0x03);
  WriteReg(UART_DLM, 0x00);
  // set word length to 8-bits
  WriteReg(REG_LCR, 0x03);
  // enable FIFOs
  WriteReg(REG_FCR, 0x07);
  // enable receiver interrupts
  WriteReg(REG_IER, 0x01);
}

void uartputc(char c) {
  while ((ReadReg(REG_LSR) & (1 << 5)) == 0)
    ;
  WriteReg(REG_THR, c);
}

// hex print
void uartput_uint64(uint64 n) {
  int i = 0;
  char buf[64];
  do {
    buf[i++] = digits[n % 16];
  } while ((n /= 16) != 0);
  while (--i >= 0)
    uartputc(buf[i]);
}
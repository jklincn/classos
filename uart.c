#define REG_RHR  0  // read mode: Receive holding reg   
#define REG_THR  0  // write mode: Transmit Holding Reg
#define REG_IER  1  // write mode: interrupt enable reg
#define REG_FCR  2  // write mode: FIFO control Reg
#define REG_ISR  2  // read mode: Interrupt Status Reg
#define REG_LCR  3  // write mode:Line Control Reg
#define REG_MCR  4  // write mode:Modem Control Reg
#define REG_LSR  5  // read mode: Line Status Reg
#define REG_MSR  6  // read mode: Modem Status Reg


#define UART_DLL  0  // LSB of divisor Latch when enabled
#define UART_DLM  1  // MSB of divisor Latch when enabled

#define UART_BASE_ADDR  0x10000000L

volatile unsigned char *Reg(int reg);
unsigned char ReadReg(int reg);
void WriteReg(int reg, char c);

void uartinit();
void uartputc(int c);
int uartgetc();

#define Reg(reg) ((volatile unsigned char *)(UART_BASE_ADDR + reg))

#define ReadReg(reg) (*(Reg(reg)))
#define WriteReg(reg, v) (*(Reg(reg)) = (v))

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

void uartputc(int c) {
    while((ReadReg(REG_LSR) & (1 << 5)) == 0)
        ;
    WriteReg(REG_THR, c);
}
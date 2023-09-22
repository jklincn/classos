__attribute__((aligned(16))) char stack[4096];

extern void uartinit();
extern void uartputc(int c);
char message[] = "Hello, OS!\n";

void main(){
    uartinit();
    for (int i=0; *(message+i)!='\0'; i++) {
        uartputc(*(message+i));
    }
}
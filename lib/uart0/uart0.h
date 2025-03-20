#ifndef UART0_H_
#define UART0_H_

void uart0Init(void);
void uart0Transmit(char data);
unsigned char uart0Receive(void);
void uart0PrintString(char *str);
void uart0Print1ByteNumber(unsigned char n);

#endif // UART0_h_
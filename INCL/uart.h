#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

#include "../INCL/queue.h"
#include "../INCL/wd.h"



int uart_init(void);
int uartOpen(void);
void uartClose(void);

void uartWriteString(const void *buf);
void uartWrite(const void *buf, int size);

int uartRead(char *buf);




#endif
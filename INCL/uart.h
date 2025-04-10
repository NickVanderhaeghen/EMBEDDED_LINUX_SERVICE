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
#include "../INCL/main.h"



int uart_init(void);
int uartOpen(void);
void uartClose(void);

void uartWriteString(const void *buf);
void uartWrite(const void *buf, int size);

void uartRead(char *buf);




#endif
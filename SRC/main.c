#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <fcntl.h>
#include <errno.h>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#include "../INCL/queue.h"
#include "../INCL/main.h"
#include "../INCL/uart.h"

#pragma once

char buf[10];

int main(int argc, char* argv[]){
    queue_init();

    if(uart_init()){
        while(1){
            printf("geef cmd in\n\r");
            scanf("%s", &buf);
            
            sleep(5);
            uartWrite(buf, strlen(buf));












        }
    }
    uartClose();
    printf("gesloten\n\r");
    return 0;
}
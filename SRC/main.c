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

char buf[20];
int queue_id;

int main(int argc, char* argv[]){
    queue_id = queue_init();
    if(uart_init()){
        while(1){
            printf("geef cmd in\n\r");
            scanf("%s", &buf);

            queue_msg_t msg = make_packet('l', &buf, 'l');

            queueSend(queue_id, &msg);
            sleep(5);
            uartWrite(&msg, 25);
        }
    }
    else{
        printf("De uart kan niet verbinden\n\r");
        queueRemove(queue_id);
    }
    uartClose();
    printf("gesloten\n\r");
    return 0;
}

queue_msg_t make_packet(__uint8_t cmd_p, char* data_p[20], __uint8_t wie_p){
    queue_msg_t queue_msg = {
        .msg = {
            .start = 's',
            .length = 25,
            .cmd = cmd_p,
            .wie = wie_p,
            .stop = 'x',
        }
    };
    snprintf(&queue_msg.msg.data, 20, &buf);

    return queue_msg;
}
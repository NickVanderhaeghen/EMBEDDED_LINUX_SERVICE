#ifndef QUEUE_H
#define QUEUE_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../INCL/uart.h"
#include "../INCL/wd.h"

#pragma once

typedef struct
{
    __uint8_t start;
    __uint8_t length;
    __uint8_t cmd;
    char data[20];
    __uint8_t wie;
    __uint8_t stop;
}my_msg_t;

typedef struct
{
    long mtype;
    my_msg_t msg;
}queue_msg_t;



extern char * key_zin;
extern int key_getal;

int queue_init(void);
int queueMake(void);
int queueOpen(void);
void queueRemove(int q_id);

void queueSend(int q_id, queue_msg_t * message);
void queueReceive(int q_id, queue_msg_t * message);

void make_packet(__uint8_t cmd_p, char data_p[20], __uint8_t wie_p, queue_msg_t * message);

#endif
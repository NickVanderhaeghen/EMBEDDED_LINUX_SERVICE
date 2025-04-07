#ifndef QUEUE_H
#define QUEUE_H

#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#pragma once

typedef struct
{
    char cmd;
    char data[10];
}my_msg_t;

typedef struct
{
    long type;
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



#endif
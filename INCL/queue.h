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
#include "../INCL/main.h"
#include "../INCL/test.h"

#pragma once





extern char * key_zin;
extern int key_getal;

int queue_init(void);
int queueMake(void);
int queueOpen(void);
void queueRemove(int q_id);

void queueSend(int q_id, queue_msg_t * message);
int queueReceive(int q_id, queue_msg_t * message);

void make_packet(int queueid, __uint8_t cmd_p, char data_p[20], __uint8_t wie_p);

#endif
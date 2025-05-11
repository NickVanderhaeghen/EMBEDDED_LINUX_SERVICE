#ifndef TEST_H
#define TEST_H

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

#pragma once

typedef struct
{
    __uint8_t cmd;
    char data[20];
    __uint8_t wie;
}my_msg_t;

typedef struct
{
    long mtype;
    my_msg_t msg;
}queue_msg_t;

#endif
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <fcntl.h>
#include <errno.h>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <pthread.h>

#include "../INCL/queue.h"
#include "../INCL/uart.h"
#include "../INCL/wd.h"




void* rx_thread(void* args);
void* tx_thread(void* args);



void main(int argc, char* argv[]);
#ifndef WD_H
#define WD_H


#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include <sys/time.h>
#include <sys/wait.h>

#include "../INCL/queue.h"
#include "../INCL/main.h"
#include "../INCL/test.h"
#include "../INCL/uart.h"

#pragma once

extern int wd_count;

void benjeernog();

void set_wd(int sec);

void wd_trig();

void exit_prog();

#endif
#include "../INCL/wd.h"

queue_msg_t msgwd;

int wd_count = 0;
int max_keer = 4;


void benjeernog(){
    char buf[20] = "benjeernog";
    printf("hey esp, ben je er nog?\n\r");
    make_packet(queue_id, 'L', buf, 'L', &msgwd);
}

void exit_prog(){
    queueRemove(queue_id);
    uartClose();
    printf("Programma wordt afgesloten!\n\r");
    exit(0);
}



void set_wd(int sec){
    struct itimerval timer;
    timer.it_value.tv_sec = sec;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
    printf("wd geset\n\r");
}


void wd_trig(){
    if(wd_count == 1){
        uartClose();
        uartOpen();
    }
    else{
        benjeernog();
        wd_count++;
        set_wd(5);
        printf("wd_count= %i\n\r", wd_count);
    }
}
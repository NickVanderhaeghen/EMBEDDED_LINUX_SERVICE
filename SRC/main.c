#include "../INCL/main.h"




pthread_t rx_thread_t;
pthread_t tx_thread_t;
int queue_id;
queue_msg_t msg;
queue_msg_t msg_receive;

char buf_tx[20];
char buf_rx[100];


void* rx_thread(void* args){
    while (1)
    {
        uartRead(&buf_rx);
    }
}

void* tx_thread(void* args){
    while (1)
    {   
        if(queueReceive(queue_id, &msg_receive) == 1){
            uartWrite(&msg_receive, sizeof(queue_msg_t)-sizeof(long));
        }


        

        //sleep(1);
        //benjeernog();
    }
}




void exit_prog(){
    queueRemove(queue_id);
    uartClose();
    printf("Programma wordt afgesloten!\n\r");
    exit(0);
}



void main(int argc, char* argv[]){
    printf("arg 1 = %s\n\v", argv[0]);
    queue_id = queue_init();
    int uart= uart_init();
    if(uart == 0){
        printf("de uart kon niet verbinden! kijk de aansluiting na! \n\r");
        exit_prog();
    }
    else{
        pthread_create(&rx_thread_t, NULL, &rx_thread, NULL);
        pthread_create(&tx_thread_t, NULL, &tx_thread, NULL);
        pthread_detach(rx_thread_t); //detach ipv join omdat bij join de hoofdlus wacht tot de thread gedaan heeft
        pthread_detach(tx_thread_t); //,wat dus nooit zal gebeuren, wel join van maken wanneer while loop wordt verwijderd
    }
    make_packet((char) argv[1][0], argv[2], (char) argv[1][0], &msg); //arg 1 = cmd, arg 2 = data, arg 3 = wie
    queueSend(queue_id, &msg);
    //sleep(1); //enablen wanneer while loop wordt verwijderd

    while (1)
    {
        printf("geef data in\n\r");
        scanf("%s", &buf_tx);
        if(strcmp(buf_tx, "exit") == 0){
            exit_prog();
        }
        make_packet('l', buf_tx, 'l', &msg);
        queueSend(queue_id, &msg);
    }
}
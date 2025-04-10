#include "../INCL/main.h"




pthread_t rx_thread_t;
pthread_t tx_thread_t;
int queue_id;
queue_msg_t msg;
queue_msg_t msg_receive;
char buf[20];

void* rx_thread(void* args){
    while (1)
    {
        sleep(5);
    }
}

void* tx_thread(void* args){

    while (1)
    {   
        printf("qid = %i\n\r", queue_id);
        printf("geef cmd in\n\r");
        scanf("%s", &buf);
        make_packet('l', buf, 'l', &msg);
        queueSend(queue_id, &msg);


        queueReceive(queue_id, &msg_receive);

        
        printf("Bericht ontvangen:\n");
        printf("Start: 0x%X\n", msg_receive.msg.start);
        printf("Cmd: %c\n", msg_receive.msg.cmd);
        printf("Data: %s\n", msg_receive.msg.data);
        printf("Length: %d\n", msg_receive.msg.length);
        printf("Wie: %c\n", msg_receive.msg.wie);
        printf("Stop: 0x%02X\n", msg_receive.msg.stop);
        sleep(3);
        uartWrite(&msg_receive, sizeof(queue_msg_t)-sizeof(long));
        //sleep(1);
        //benjeernog();
    }
}







void main(int argc, char* argv[]){
    queue_id = queue_init();
    int uart= uart_init();
    if(uart == 0){
        printf("de uart kon niet verbinden! kijk de aansluiting na! \n\r");
        queueRemove(queue_id);
        exit(0);
    }
    else{
        pthread_create(&rx_thread_t, NULL, &rx_thread, NULL);
        pthread_create(&tx_thread_t, NULL, &tx_thread, NULL);
        pthread_join(rx_thread_t, NULL);
        pthread_join(tx_thread_t, NULL);
    }
}
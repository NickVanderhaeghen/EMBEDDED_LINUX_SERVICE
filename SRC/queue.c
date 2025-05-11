#include "../INCL/queue.h"

char * key_zin = "linux";
int key_getal = 42;



int queue_init(void){
    int id = queueMake();
    return id;
}

int queueMake(void){
    key_t key = ftok(key_zin, key_getal);// MAAK EEN PASWOORD
    int q_id = msgget(1234, IPC_CREAT | 0666);
    printf("Queue met id %i is geopend!\n\r", q_id);
    /*0666 zijn de rechten 0->octale notatie, 6-> 4+2 -> lees en schrijfrechten
    IPC_CREAT MAAKT EEN NIEUWE QUEUE OF GEBRUIKT EEN AL BESTAANDE*/
    return q_id;
}

int queueOpen(void){
    key_t key = ftok(key_zin, key_getal);// MAAK EEN PASWOORD
    int q_id = msgget(1234, 0666);//0666 zijn de rechten 0->octale notatie, 6-> 4+2 -> lees en schrijfrechten
    printf("Queue met id %i is geopend!\n\r", q_id);
    return q_id;
}

void queueRemove(int q_id){
    msgctl(q_id, IPC_RMID, NULL);
    /*msgctr -> voer een actie uit op queue met een bepaald q_id
    IPC_RMID -> remove id -> verwijderd de queue met een bepaald q_id*/
    printf("Queue met id %i is gesloten!\n\r", q_id);
}

void queueSend(int q_id, queue_msg_t * message){
    if(msgsnd(q_id, message, sizeof(queue_msg_t), 0) == 0){
        //printf("msg zit in de queue\n\r");
    }
}

int queueReceive(int q_id, queue_msg_t * message){
    // msg type = 1 -> nummer dient als filter. Zo kunnen we bepaalde messages uitlezen
    if(msgrcv(q_id, message, sizeof(queue_msg_t), 1, 0) >= 0){
        //printf("msg is uit de queue gehaald\n\r");
        return 1;
    }
    return 0;
}
// msg type = 1 -> nummer dient als filter. Zo kunnen we bepaalde messages uitlezen



void make_packet(int queueid, __uint8_t cmd_p, char data_p[20], __uint8_t wie_p, queue_msg_t * queue_msg){
    int count = 0;
    for (int i = 0; i < 20; i++) {
        if (*(data_p+i) == '\0') {
            break;  // Stop als de nul-terminator wordt gevonden
        } else {
            count++;  // Verhoog de teller
        }
    }
    //printf("teller staat op %i bytes\n\r", count);  // Toon het aantal verwerkte bytes

        queue_msg -> mtype = 1;
        queue_msg->msg.cmd= cmd_p;
        queue_msg->msg.wie= wie_p;


    //snprintf(&queue_msg.msg.data, count+1, data_p+0x00, NULL);
    memset(queue_msg->msg.data, 0, sizeof(queue_msg->msg.data)); 
    strncpy(queue_msg->msg.data, data_p, count);
    //printf("tekst = %s \n\r", queue_msg->msg.data);

    queueSend(queueid, queue_msg);
}

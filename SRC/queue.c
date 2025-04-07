#include "../INCL/queue.h"

char * key_zin = "linux";
int key_getal = 42;

int queue_init(void){
    int id = queueMake();
    id = queueOpen();
    return id;
}

int queueMake(void){
    key_t key = ftok(key_zin, key_getal);// MAAK EEN PASWOORD
    int q_id = msgget(key, 0666 | IPC_CREAT);
    /*0666 zijn de rechten 0->octale notatie, 6-> 4+2 -> lees en schrijfrechten
    IPC_CREAT MAAKT EEN NIEUWE QUEUE OF GEBRUIKT EEN AL BESTAANDE*/
    return q_id;
}

int queueOpen(void){
    key_t key = ftok(key_zin, key_getal);// MAAK EEN PASWOORD
    int q_id = msgget(key, 0666);//0666 zijn de rechten 0->octale notatie, 6-> 4+2 -> lees en schrijfrechten
    printf("Queue met id %i is geopend!\n\r", q_id);
    return q_id;
}

void queueRemove(int q_id){
    msgctl(q_id, IPC_RMID, NULL);
    /*msgctr -> voer een actie uit op queue met een bepaald q_id
    IPC_RMID -> remove id -> verwijderd de queue met een bepaald q_id*/
    printf("Queue met is %i is gesloten!", q_id);
}

void queueSend(int q_id, queue_msg_t * message){
    msgsnd(q_id, message, sizeof(message), 0);
}

void queueReceive(int q_id, queue_msg_t * message){
    msgrcv(q_id, message, sizeof(message), 1, 0);
    // msg type = 1 -> nummer dient als filter. Zo kunnen we bepaalde messages uitlezen
}
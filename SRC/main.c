#include "../INCL/main.h"



pthread_t rx_thread_t;
pthread_t tx_thread_t;
int queue_id;
queue_msg_t msg;
queue_msg_t msg_receive;

char buf_tx[20];
char buf_rx[sizeof(queue_msg_t)];




/*we hebben voor threads gekozen omdat deze langs elkaar kunnen
  werken en beide aan functies en variabele kunnen delen.*/
void* rx_thread(void* args){
    while (1)
    {
        uartRead(&buf_rx);
    }
}

void* tx_thread(void* args){
    while (1)
    {   
        //ALS ER IETS IN DE QUEUE STAAT VERZEND HET DAN
        if(queueReceive(queue_id, &msg_receive) == 1){
            uartWrite(&msg_receive, sizeof(queue_msg_t)-sizeof(long));
        }
    }
}



void main(int argc, char* argv[]){
    int fd1 = open("/home/nick/Documents/logfile.txt", O_RDWR|O_CREAT|O_APPEND, 0666);
    dup2(fd1, STDOUT_FILENO);
    setvbuf(stdout, NULL, _IOLBF, 0); //ZONDER WORDEN DE PRINTF GEBUFFERD EN NIET ONMIDDELIJK WEGGESCHREVEN.
    close(fd1);
    
    queue_id = queue_init(); //initialiseren van de queue
    int uart= uart_init(); //initialiseren van de uart
    /*we maken een timer handler aan zodat deze funtie wordt 
    aangeroepen als de timer afloopt*/
    signal(SIGALRM, wd_trig);
    set_wd(5);


    pthread_create(&rx_thread_t, NULL, &rx_thread, NULL);
    pthread_create(&tx_thread_t, NULL, &tx_thread, NULL);
    

    //DE HOOFDLUS ZAL WACHTEN TOT DE THREAD AFLOPEN. ZE LOPEN ECHTER NOOT AF OWV DE WHILE(1)
    pthread_join(rx_thread_t, NULL);
    pthread_join(tx_thread_t, NULL);
}
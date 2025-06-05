#include "../INCL/log.h"


int openFileDescriptor(){
    return open("/home/nick/Documents/logfile.txt", O_RDWR|O_CREAT|O_APPEND, 0666);
}

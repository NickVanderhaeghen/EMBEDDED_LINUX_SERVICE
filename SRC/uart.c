#include "../INCL/uart.h"


int serial_port;
struct termios tty;

jmp_buf open_uart;

queue_msg_t buf_rx_msg;

int uart_init(void){
    return uartOpen();
}

int uartOpen(void){
    int aantal_keer = 0;
    setjmp(open_uart);
    serial_port = open("/dev/ttyACM0", O_RDWR); //ttyACM0 = esp32-S3 serial = psoc

    if(serial_port < 0) {
        printf("IK PROBEER DE UART TE OPENEN. Poging %i\n\r", aantal_keer);
        aantal_keer++;
        sleep(1);
        longjmp(open_uart, 1); //wanneer de uart niet geopend kan worden blijft hij opnieuw proberen.
    }

    
    
    printf("UART CONNECTIE GELUKT!\n\r");

    //config
    tcgetattr(serial_port, &tty);

    //cflag bepaalt de flow
	tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, 
    tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size 
    tty.c_cflag |= CS8; // 8 bits per byte (most common)
    //tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
  
    //lflag bepaald de interactie vanuit linux op de lijn
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO; // Disable echotty
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

 	//oflag output flags
    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    // hoe blokking of non blocking is de uart functies
    tty.c_cc[VTIME] = 0;    // Wait for up to 0.x s (1 deciseconds), 
    tty.c_cc[VMIN] = 0;	// wait for x byte


    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    tcsetattr(serial_port, TCSANOW, &tty);
    return 1;
}

void uartClose(void){
    //printf("De uart wordt gesloten!\n\r");
    close(serial_port);
}

void uartWriteString(const void *buf){
    write(serial_port, (char*)buf, strlen(buf)+1);
}

void uartWrite(const void *buf, int size){
    write(serial_port, (__uint8_t*)buf, size);
}

void uartRead(char *buf) {
    int len = read(serial_port, buf, sizeof(my_msg_t));  // 22 bytes
    if (len == sizeof(my_msg_t)) {
        wd_count = 0;
        memcpy(buf_rx_msg.msg.data, &buf[5], 25);
        printf("Data ontvangen. Data: %s! Reset WD!\n\r", buf_rx_msg.msg.data);
        set_wd(5); //reset wd
    }
}
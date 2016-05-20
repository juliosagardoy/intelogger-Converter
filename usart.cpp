/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   usart.cpp
 * Author: julio
 * 
 * Created on April 18, 2016, 10:56 AM
 */

#include "usart.h"

Usart::Usart() {
}

Usart::Usart(const Usart& orig) {
}

Usart::~Usart() {
}

int Usart::openPort(std::string portName)
{
    struct termios tio;
    struct termios stdio;
    struct termios old_stdio;

    unsigned char c='D';
    tcgetattr(STDOUT_FILENO,&old_stdio);

    //printf("Please start with %s /dev/ttyS1 (for example)\n",argv[0]);
    memset(&stdio,0,sizeof(stdio));
    stdio.c_iflag=0;
    stdio.c_oflag=0;
    stdio.c_cflag=0;
    stdio.c_lflag=0;
    stdio.c_cc[VMIN]=1;
    stdio.c_cc[VTIME]=0;
    tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
    tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking

    memset(&tio,0,sizeof(tio));
    tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;

    tty_fd = open(portName.c_str(), O_RDWR | O_NONBLOCK);    

    cfsetospeed(&tio,B115200);            // 115200 baud
    cfsetispeed(&tio,B115200);            // 115200 baud

    tcsetattr(tty_fd,TCSANOW,&tio);
    
    return tty_fd;
}

void Usart::closePort()
{
    close(tty_fd);
}

/*
 * If present, returns next available byte from USART buffer, else returns NULL
 */
byte Usart::getc() {
    byte res;
    if(read(tty_fd, &res, 1) > 0)
        return res;
    else
        return 0x00;
}

/*
 * If present, returns __nbytes bytes from USART buffer; else returns NULL
 */
std::string Usart::gets( size_t __nbytes ) {
    char * res;
    std::string out;
    if(read(tty_fd, &res, __nbytes) > 0)
    {
        out = std::string(res, __nbytes);
        return out;
    }
    else
        return 0x00;
}

/*
 * Writes a byte to USARt buffer
 */
void Usart::putc(byte b)
{
    
}
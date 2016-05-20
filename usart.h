/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   usart.h
 * Author: julio
 *
 * Created on April 18, 2016, 10:56 AM
 */

#ifndef USART_H
#define USART_H

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <istream>
#include <string>
#include <cstring>

typedef unsigned char byte;

class Usart {
public:
    Usart();
    Usart(const Usart& orig);
    virtual ~Usart();
    int openPort(std::string);
    void closePort(void);
    byte getc(void);
    void putc(byte);
    std::string gets(size_t);
private:
    int tty_fd; //File descriptor for serial port
};

#endif /* USART_H */


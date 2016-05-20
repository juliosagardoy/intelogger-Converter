/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: julio
 *
 * Created on April 18, 2016, 9:59 AM
 */

#include <cstdlib>
#include <cstdio>

#include <iostream>
#include <fstream>
#include <string>
#include "usart.h"

#define ACK 0x05
#define BEGIN 0x01

//using namespace std;

/* 
 * Public declarations 
 */
Usart *usart; // Handle to USART module
std::string portName; // variable with USART portname

/*
 *
 */
void parseDiscretes(std::string s) {
    std::ofstream mFile;
//    mFile.open("log_");


}

/*
 * Program loop
 */
void loop() {

    byte res;
    uint rsize = 0x00, rtype = 0x00;
    std::string s;

    /* Search for initial sentence start, indicated by byte 0x01, otherwise keep looping */
    res = usart->getc();
    if (res == 0x01) {
        /* Read next byte: size (0-255)*/
        rsize = usart->getc();
        rtype = usart->getc();
        
        /* Check what sentence type and parse */
        switch (rtype) {
            case 0x30: /* Process discretes */
                parseDiscretes(usart->gets(rsize));
                break;
            case 0x31: /* Process analog sigs */
//                parse(usart->gets(rsize));
                break;
            case 0x32: /* Process pwm */
//              parse(usart->gets(rsize));
                break;
            case 0x33: /* other data */
//              parse(usart->gets(rsize));
                break;
            default:
                break;
        }
        
    }

}

/*
 * 
 */
int main(int argc, char** argv) {
    usart = new Usart();

    portName = "/dev/ttyS0";
    std::cout << "Intelogger v1.0" << std::endl;
    std::cout << "---------------" << std::endl << std::endl;


    int e = usart->openPort("/dev/ttyUSB0");
    if (e == -1) {
        std::cout << "Failed to open serial port." << std::endl;
        //return 0;
        exit(0);
    }
    
    std::cout << "Attempting communication with the car.";
    
    while (usart->getc() != ACK) // Wait for answer from car
    {
        usart->putc(0x01); // Send begin signal to car
        std::cout << ".";
        usleep(250);
    }

    std::cout << std::endl << "Communication with car established. Now looping..." << std::endl;
    while (1) {
        loop();
    }
    usart->closePort();

    return 0;
}

#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "packet.hpp"

class SerialPort {
public:
    SerialPort(const char* portName);
    ~SerialPort();

private:
    void send(const Packet& packet);
    
    int serialPort;
};

#endif // SERIALPORT_H



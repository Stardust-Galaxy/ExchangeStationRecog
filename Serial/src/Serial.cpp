// SerialPort.cpp

#include "../include/SerialPort.h"
#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

SerialPort::SerialPort(const char* portName) {
    serialPort = open(portName, O_WRONLY);
    if (serialPort == -1) {
        std::cerr << "Error opening serial port." << std::endl;
        exit(EXIT_FAILURE);
    }

    // 配置串口
    struct termios tty;
    if (tcgetattr(serialPort, &tty) != 0) {
        std::cerr << "Error configuring serial port." << std::endl;
        exit(EXIT_FAILURE);
    }

    cfsetospeed(&tty, B9600); // 设置波特率为 9600
    cfsetispeed(&tty, B9600);

    tty.c_cflag &= ~PARENB;  // 无奇偶校验
    tty.c_cflag &= ~CSTOPB;  // 1个停止位
    tty.c_cflag &= ~CSIZE;   // 无数据位
    tty.c_cflag |= CS8;      // 8个数据位
    tty.c_cflag &= ~CRTSCTS; // 无硬件流控制

    // 设置超时参数
    tty.c_cc[VMIN] = 1;  // 阻塞直到读到一个字符
    tty.c_cc[VTIME] = 1; // 0.1秒超时

    if (tcsetattr(serialPort, TCSANOW, &tty) != 0) {
        std::cerr << "Error configuring serial port." << std::endl;
        exit(EXIT_FAILURE);
    }
}

SerialPort::~SerialPort() {
    close(serialPort);
}

void SerialPort::send(const Packet& packet) {
    std::vector<uint8_t> data = toVector(packet);
    write(serialPort, data.data(), data.size());
}


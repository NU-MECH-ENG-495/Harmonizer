#ifndef SERIAL_COMMUNICATION_H
#define SERIAL_COMMUNICATION_H

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <libserial/SerialPort.h>

using namespace LibSerial;

class SerialCommunication {
public:
    SerialCommunication(const std::string& port_name) {}

    void write(const int& pos) {}

    void read() {}

private:
    SerialPort serial_port;
};
#endif
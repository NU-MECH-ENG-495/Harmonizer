#include "SerialCommunication.h"

class SerialCommunication {
public:
    SerialCommunication(const std::string& port_name) {
        try {
            serial_port.Open(port_name);
            serial_port.SetBaudRate(BaudRate::BAUD_9600);
        } catch (const OpenFailed &e) {
            std::cerr << "Error opening serial port: " << e.what() << std::endl;
            throw std::runtime_error("Serial Port Open Failed");
        }
    }

    void write(const int& pos) {
        std::string data_to_send = std::to_string(pos) + "\n";
        serial_port.Write(data_to_send);
    }

    void read() {
        while (!serial_port.IsDataAvailable()) {}
        DataBuffer read_buffer;
        size_t ms_timeout = 250;
        try {
            serial_port.Read(read_buffer, 0, ms_timeout);
        } catch (const ReadTimeout&) {
            for (size_t i = 0; i < read_buffer.size(); i++) {
                std::cout << read_buffer.at(i) << std::flush;
            }
        }
    }

private:
    SerialPort serial_port;
};
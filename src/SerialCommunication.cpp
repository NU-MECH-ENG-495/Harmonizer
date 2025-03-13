/**
 * @file SerialCommunication.cpp
 * @brief This file contains the implementation of the SerialCommunication class, 
 *        which handles communication over a serial port.
 * 
 * The class provides functionality to open a serial port, send data to the port, 
 * and read data from the port with appropriate error handling and timeouts.
 * 
 * @author Joseph Blom
 * @date March 2025
 */

#include "SerialCommunication.h"

/**
 * @brief Constructs a SerialCommunication object and opens the specified serial port.
 * 
 * This constructor attempts to open the specified serial port with a baud rate of 9600. If the 
 * serial port cannot be opened, it throws a runtime error. The serial port is configured for reading 
 * and writing data.
 * 
 * @param port_name The name of the serial port to open (e.g., "/dev/ttyACM0" on Linux).
 * @throws std::runtime_error If the serial port cannot be opened.
 */
SerialCommunication::SerialCommunication(const std::string& port_name) {
    try {
        serial_port.Open(port_name);
        serial_port.SetBaudRate(BaudRate::BAUD_9600);
    } catch (const OpenFailed &e) {
        std::cerr << "Error opening serial port: " << e.what() << std::endl;
        throw std::runtime_error("Serial Port Open Failed");
    }
}

/**
 * @brief Writes data to the serial port.
 * 
 * This method converts the integer position `pos` to a string and sends it to the serial port. 
 * The data is sent with a newline character (`\n`) to mark the end of the message.
 * 
 * @param pos The position or value to be sent to the serial port.
 */
void SerialCommunication::write(const int& pos) {
    std::string data_to_send = std::to_string(pos) + "\n";
    serial_port.Write(data_to_send);
}

/**
 * @brief Reads data from the serial port.
 * 
 * This method waits until data is available on the serial port. Once data is available, it attempts 
 * to read the data into a buffer with a timeout of 250 milliseconds. When the read operation times out, 
 * it prints the data in the buffer to the standard output.
 * 
 * @note This method blocks until data is available.
 */
void SerialCommunication::read() {
    // Wait until data is available on the serial port
    while (!serial_port.IsDataAvailable()) {}

    DataBuffer read_buffer;
    size_t ms_timeout = 250;

    try {
        // Attempt to read the data from the serial port with the specified timeout
        serial_port.Read(read_buffer, 0, ms_timeout);
    } catch (const ReadTimeout&) {
        // When the read operation times out, print the contents of the buffer
        for (size_t i = 0; i < read_buffer.size(); i++) {
            std::cout << read_buffer.at(i) << std::flush;
        }
    }
}

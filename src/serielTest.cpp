#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <libserial/SerialPort.h>
#include "MidiFile.h"

// using namespace LibSerial;

int main() {
    smf::MidiFile midiFile;
    midiFile.read("../taps-3.mid");
    int numTracks = midiFile.getTrackCount();
    int timeDivision = midiFile.getTicksPerQuarterNote();
    std::cout << timeDivision << std::endl;

    for (int track = 0; track < numTracks; track++) {
        for (int event = 0; event < midiFile[track].size(); event++) {
            // Process MIDI events
            // midiFile[track][event].getCommand() returns the MIDI command
            // midiFile[track][event].getP1() and midiFile[track][event].getP2() return the parameters
        }
    }
//   SerialPort serial_port;
//   std::string port_name = "/dev/ttyUSB0"; // Replace with your serial port
//   int baud_rate = 9600; // Set the desired baud rate

//   try {
//     serial_port.Open(port_name);
//   } catch (const OpenFailed &e) {
//     std::cerr << "Error opening serial port: " << e.what() << std::endl;
//     return 1;
//   }

//   serial_port.SetBaudRate(static_cast<BaudRate>(baud_rate));
//   serial_port.SetCharacterSize(CharacterSize::CHAR_SIZE_8);
//   serial_port.SetStopBits(StopBits::STOP_BITS_1);
//   serial_port.SetParity(Parity::PARITY_NONE);

//   std::string data_to_send = "3\n"; // rotate 90 degrees

//   try {
//     serial_port.Write(data_to_send);
//     std::cout << "Sent: " << data_to_send << std::endl;
//   } catch (const std::runtime_error &e) {
//     std::cerr << "Error writing to serial port: " << e.what() << std::endl;
//     return 1;
//   }

//   serial_port.Close();
  return 0;
}
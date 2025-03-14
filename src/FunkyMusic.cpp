/**
 * @file main.cpp
 * @brief Main entry point for the Harmonica Player application.
 * 
 * This program initializes serial communication with a device, performs step checks, 
 * and either plays a MIDI file or performs a calibration process based on command-line input.
 * 
 * @author Joseph Blom
 * @date March 2025
 */

#include "HarmonicaPlayer.h"
#include "SerialCommunication.h"

/**
 * @brief Performs a series of step checks to test the serial communication with the device.
 * 
 * The function sends a sequence of messages over the serial port and waits for the response. 
 * It performs this in a loop for 10 iterations with different values to check the device's 
 * response at various stages. If an error occurs during communication, an exception is thrown.
 *
 * @param serialComm A reference to the SerialCommunication object used for communication.
 * 
 * @return 0 if the operation is successful, or 1 if an error occurs.
 */
int stepCheck(SerialCommunication& serialComm) {
    try {
        // Go through every note available
        for (int i = 0; i < 10; i++) {
            serialComm.write(i);
            serialComm.read();

            // serialComm.write(1000);
            // serialComm.read();
            // std::this_thread::sleep_for(std::chrono::duration<double>(0.5));

            // serialComm.write(1001);
            // serialComm.read();
            std::this_thread::sleep_for(std::chrono::duration<double>(0.5));
        }

        // Return to start
        serialComm.write(0);
        serialComm.read();

        serialComm.write(1000);
        serialComm.read();

        return 0;
    } catch (const std::runtime_error &e) {
        std::cerr << "Error writing to serial port: " << e.what() << std::endl;
        return 1;
    }
}

/**
 * @brief Main function for the Harmonica Player application.
 * 
 * The main function initializes the serial communication and handles the program logic. 
 * It checks for command-line arguments and either plays a MIDI file or performs calibration 
 * based on the presence of a file argument.
 * 
 * @param argc The number of command-line arguments passed.
 * @param argv An array of C-string arguments.
 * 
 * @return 0 if the application runs successfully, or 1 if an error occurs.
 */
int main(int argc, char* argv[]) {
    try {
        // Initialize serial communication with the given port name.
        std::string port_name = "/dev/ttyACM0";
        SerialCommunication serialComm(port_name);
        HarmonicaMapping harmonica;

        // If a file argument is provided, play the MIDI file.
        if (argc == 2) {
            MidiHandler midiHandler(argv[1]);
            midiHandler.display();
            HarmonicaPlayer player(serialComm, harmonica, midiHandler);
            player.play(); // Play the MIDI file.
        } else {
            // Otherwise, perform a step check on the serial communication.
            int check = stepCheck(serialComm);
            if (check == 1) {
                return check; // Return failure if check failed.
            }
        }

        return 0; // Return success.
    } catch (const std::exception& e) {
        // Catch any exceptions and print the error message.
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // Return failure due to exception.
    }
}

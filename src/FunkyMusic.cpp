#include "HarmonicaPlayer.h"
#include "SerialCommunication.h"

int stepCheck(SerialCommunication& serialComm) {
    try {
        for (int i = 0; i < 10; i++) {
            serialComm.write(i);
            serialComm.read();

            serialComm.write(1000);
            serialComm.read();
            std::this_thread::sleep_for(std::chrono::duration<double>(0.5));

            serialComm.write(1001);
            serialComm.read();
            std::this_thread::sleep_for(std::chrono::duration<double>(0.5));
        }
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

int main(int argc, char* argv[]) {
    try {
        std::string port_name = "/dev/ttyACM0";
        SerialCommunication serialComm(port_name);
        HarmonicaMapping harmonica;

        // If given a file name, play that file. Otherwise do calibration.
        if (argc == 2) {
            MidiHandler midiHandler(argv[1]);
            midiHandler.display();
            HarmonicaPlayer player(serialComm, harmonica, midiHandler);
            player.play();
        } else {
            int check = stepCheck(serialComm);
            if (check == 1) {
                return check;
            }
        }
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}

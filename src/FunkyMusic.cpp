#include "HarmonicaPlayer.h"
#include "SerialCommunication.h"

int stepCheck(SerialCommunication& serialComm) {
    try {
        for (int i = 0; i < 10; i++) {
            serialComm.write(i);
            serialComm.read();

            serialComm.write(1000);
            serialComm.read();

            serialComm.write(1001);
            serialComm.read();
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

int main() {
    try {
        std::string port_name = "/dev/ttyACM0";
        SerialCommunication serialComm(port_name);
        MidiHandler midiHandler("./newTaps.mid");
        HarmonicaMapping harmonica;

        midiHandler.display();
        HarmonicaPlayer player(serialComm, harmonica, midiHandler);
        player.play();

        int check = stepCheck(serialComm);
        if (check == 1) {
            return check;
        }
        return 0;
    } catch (const std::exception& e) {
        return 1;
    }
}

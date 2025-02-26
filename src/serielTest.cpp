#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <libserial/SerialPort.h>
#include <map>
#include <chrono>
#include <thread>
#include "MidiFile.h"

using namespace LibSerial;
using namespace std;
using namespace smf;

void moveTo (const int& pos, SerialPort& port);
void readPort (SerialPort& port);
int stepCheck(SerialPort& port);

int main() {
    map<int, int> notesToPosition;

    notesToPosition[62] = 0;
    notesToPosition[67] = 2;
    notesToPosition[71] = 3;
    notesToPosition[74] = 4;

    SerialPort serial_port;
    std::string port_name = "/dev/ttyACM0";

    try {
        serial_port.Open(port_name);
    } catch (const OpenFailed &e) {
        std::cerr << "Error opening serial port: " << e.what() << std::endl;
        return 1;
    }

    serial_port.SetBaudRate(BaudRate::BAUD_9600);

    MidiFile midifile;
    midifile.read("./newTaps.mid");
    midifile.doTimeAnalysis();
    midifile.linkNotePairs();

    int tracks = midifile.getTrackCount();
    cout << "TPQ: " << midifile.getTicksPerQuarterNote() << endl;
    if (tracks > 1) cout << "TRACKS: " << tracks << endl;
    for (int track=0; track<tracks; track++) {
        if (tracks > 1) cout << "\nTrack " << track << endl;
        cout << "Tick\tSeconds\tDur\tMessage" << endl;

        // Go through events for track, move to position if its a NOTE ON
        for (int event=0; event<midifile[track].size(); event++) {
            cout << dec << midifile[track][event].tick;
            cout << '\t' << dec << midifile[track][event].seconds;
            cout << '\t';
            if (midifile[track][event].isNoteOn()) {
                double noteDuration = midifile[track][event].getDurationInSeconds();
                cout << noteDuration;
                cout << '\t';
                int note = midifile[track][event].getKeyNumber();
                cout << note;

                //Send motor to position
                moveTo(notesToPosition[note], serial_port);

                //Sleep for duration of note
                this_thread::sleep_for(chrono::duration<double>(noteDuration));
            }
            cout << endl;
        }
    }
    // int check = stepCheck(serial_port);
    // if (check == 1) {
    //     return check;
    // }
    return 0;
}

int stepCheck(SerialPort& port) {
    try {
        for (int i = 0; i < 13; i++){
            moveTo(i, port);
            readPort(port);
        }
        moveTo(0, port);
        readPort(port);
        return 0;
    } catch (const std::runtime_error &e) {
        std::cerr << "Error writing to serial port: " << e.what() << std::endl;
        return 1;
    }
}

void moveTo (const int& pos, SerialPort& port) {
    std::string data_to_send = std::to_string(pos) + "\n";
    port.Write(data_to_send);
}

void readPort (SerialPort& port) {
    while(!port.IsDataAvailable()) {}
    DataBuffer read_buffer ;
    size_t ms_timeout = 250 ;
    try
    {
        // Read as many bytes as are available during the timeout period.
        port.Read(read_buffer, 0, ms_timeout) ;
    }
    catch (const ReadTimeout&)
    {
        for (size_t i = 0 ; i < read_buffer.size() ; i++)
        {
            std::cout << read_buffer.at(i) << std::flush ;
        }
    }
}
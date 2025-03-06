#include "HarmonicaPlayer.h"


HarmonicaPlayer::HarmonicaPlayer(SerialCommunication& serial, HarmonicaMapping& harmonica, MidiHandler& midiHandler)
    : serialComm(serial), harmonica(harmonica), midiHandler(midiHandler) {}

void HarmonicaPlayer::play() {
    int tracks = midiHandler.getMidiFile().getTrackCount();
    for (int track = 0; track < tracks; track++) {
        for (int event = 0; event < midiHandler.getMidiFile()[track].size(); event++) {
            if (midiHandler.getMidiFile()[track][event].isNoteOn()) {
                double noteDuration = midiHandler.getMidiFile()[track][event].getDurationInSeconds();
                int note = midiHandler.getMidiFile()[track][event].getKeyNumber();

                std::cout << "Playing Note: " << std::dec << note << " for " << noteDuration << " seconds." << std::endl;

                // Send motor to position
                serialComm.write(harmonica.getHoleNumber(note));
                serialComm.read();

                // Set blow or draw
                serialComm.write(harmonica.getAction(note));
                serialComm.read();

                // Sleep for the duration of the note
                std::this_thread::sleep_for(std::chrono::duration<double>(noteDuration));
            }
        }
    }
}
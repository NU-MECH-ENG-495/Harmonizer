#ifndef HARMONICA_PLAYER_H
#define HARMONICA_PLAYER_H

#include <chrono>
#include <thread>

#include "MidiHandler.h"
#include "SerialCommunication.h"
#include "HarmonicaMapping.h"

class HarmonicaPlayer {
public:
    HarmonicaPlayer(SerialCommunication& serial, HarmonicaMapping& harmonica, MidiHandler& midiHandler)
        : serialComm(serial), harmonica(harmonica), midiHandler(midiHandler) {}

    void play() {}

private:
    SerialCommunication& serialComm;
    HarmonicaMapping& harmonica;
    MidiHandler& midiHandler;
};

#endif
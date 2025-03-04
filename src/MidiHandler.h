#ifndef MIDI_HANDLER_H
#define MIDI_HANDLER_H

#include <stdio.h>
#include "midiFile/MidiFile.h"

using namespace smf;
using namespace std;

class MidiHandler {
public:
    MidiHandler(const std::string& file_path) {}

    void display() const {}

    MidiFile& getMidiFile() {}

private:
    MidiFile midifile;
};

#endif
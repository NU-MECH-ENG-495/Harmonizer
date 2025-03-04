#include "MidiHandler.h"

class MidiHandler {
public:
    MidiHandler(const std::string& file_path) {
        midifile.read(file_path);
        midifile.doTimeAnalysis();
        midifile.linkNotePairs();
    }

    void display() const {
        int tracks = midifile.getTrackCount();
        std::cout << "TPQ: " << midifile.getTicksPerQuarterNote() << std::endl;
        if (tracks > 1) std::cout << "TRACKS: " << tracks << std::endl;
        for (int track = 0; track < tracks; track++) {
            if (tracks > 1) std::cout << "\nTrack " << track << std::endl;
            std::cout << "Tick\tSeconds\tDur\tMessage" << std::endl;
            for (int event = 0; event < midifile[track].size(); event++) {
                std::cout << dec << midifile[track][event].tick;
                std::cout << '\t' << dec << midifile[track][event].seconds;
                std::cout << '\t';
                if (midifile[track][event].isNoteOn())
                    std::cout << midifile[track][event].getDurationInSeconds();
                std::cout << '\t' << hex;
                for (int i = 0; i < midifile[track][event].size(); i++)
                    std::cout << (int)midifile[track][event][i] << ' ';
                std::cout << std::endl;
            }
        }
    }

    MidiFile& getMidiFile() {
        return midifile;
    }

private:
    MidiFile midifile;
};
/**
 * @file MidiHandler.cpp
 * @brief This file contains the implementation of the MidiHandler class, 
 *        which handles reading, analyzing, and displaying MIDI file data.
 * 
 * The class provides functionality to load a MIDI file, perform time analysis, 
 * link note pairs, and display relevant details about the MIDI file's tracks and events.
 * 
 * @author Joseph Blom
 * @date March 2025
 */

#include "MidiHandler.h"

/**
 * @brief Constructs a MidiHandler object and loads a MIDI file.
 * 
 * This constructor reads the MIDI file from the specified file path, performs time analysis 
 * on the MIDI data, and links any note pairs (for example, paired note-on and note-off events).
 * 
 * @param file_path The path to the MIDI file that will be loaded and processed.
 */
MidiHandler::MidiHandler(const std::string& file_path) {
    midifile.read(file_path);               /**< Read the MIDI file from the specified path. */
    midifile.doTimeAnalysis();              /**< Perform time analysis on the MIDI file. */
    midifile.linkNotePairs();               /**< Link note pairs (e.g., note-on and note-off events). */
}

/**
 * @brief Displays detailed information about the loaded MIDI file.
 * 
 * This method prints out key information about the MIDI file, including the number of tracks, 
 * ticks per quarter note (TPQ), and detailed event information for each track. For each event, 
 * it shows the tick, the time in seconds, the duration (for note-on events), and the raw MIDI message.
 * 
 * The output is displayed in a human-readable format to help understand the structure and content of the MIDI file.
 */
void MidiHandler::display() const {
    int tracks = midifile.getTrackCount();
    
    // Display ticks per quarter note (TPQ)
    std::cout << "TPQ: " << midifile.getTicksPerQuarterNote() << std::endl;

    // Display the number of tracks if there is more than one
    if (tracks > 1) 
        std::cout << "TRACKS: " << tracks << std::endl;

    // Iterate through all tracks in the MIDI file
    for (int track = 0; track < tracks; track++) {
        // Display track number if there are multiple tracks
        if (tracks > 1) 
            std::cout << "\nTrack " << track << std::endl;

        // Print headers for event details
        std::cout << "Tick\tSeconds\tDur\tMessage" << std::endl;

        // Iterate through all events in the current track
        for (int event = 0; event < midifile[track].size(); event++) {
            std::cout << dec << midifile[track][event].tick;
            std::cout << '\t' << dec << midifile[track][event].seconds;
            std::cout << '\t';

            // If the event is a "Note On", display the duration in seconds
            if (midifile[track][event].isNoteOn())
                std::cout << midifile[track][event].getDurationInSeconds();
            std::cout << '\t' << hex;

            // Display the raw MIDI message in hexadecimal format
            for (int i = 0; i < midifile[track][event].size(); i++)
                std::cout << (int)midifile[track][event][i] << ' ';
            
            std::cout << std::endl;
        }
    }
}

/**
 * @brief Gets the loaded MidiFile object.
 * 
 * This method provides access to the underlying MidiFile object, which represents the entire MIDI file.
 * It allows other classes or components to interact with the MIDI file's raw data.
 * 
 * @return A reference to the MidiFile object that contains the loaded MIDI data.
 */
MidiFile& MidiHandler::getMidiFile() {
    return midifile;
}

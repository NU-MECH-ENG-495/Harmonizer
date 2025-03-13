/**
 * @file HarmonicaPlayer.cpp
 * @brief This file contains the implementation of the HarmonicaPlayer class, 
 *        which plays MIDI notes on a harmonica using serial communication.
 * 
 * The class interacts with a serial device and a MIDI file handler to send harmonica control commands 
 * (e.g., hole number and blow/draw action) based on the MIDI events.
 * 
 * @author Joseph Blom
 * @date March 2025
 */

#include "HarmonicaPlayer.h"

/**
 * @brief Constructs a HarmonicaPlayer object with the given serial communication, harmonica mapping, 
 *        and MIDI handler.
 * 
 * This constructor initializes the HarmonicaPlayer object, setting up the serial communication, 
 * harmonica mapping, and MIDI handler objects for further operations.
 * 
 * @param serial A reference to a SerialCommunication object used for sending control commands to the harmonica.
 * @param harmonica A reference to a HarmonicaMapping object that maps MIDI notes to harmonica hole numbers and actions.
 * @param midiHandler A reference to a MidiHandler object used to handle the MIDI file and its events.
 */
HarmonicaPlayer::HarmonicaPlayer(SerialCommunication& serial, HarmonicaMapping& harmonica, MidiHandler& midiHandler)
    : serialComm(serial), harmonica(harmonica), midiHandler(midiHandler) {}

/**
 * @brief Plays the MIDI file on the harmonica using serial communication.
 * 
 * The `play` method iterates through all tracks and events in the provided MIDI file. For each "Note On" event, 
 * it retrieves the corresponding MIDI note, calculates the note duration, and sends the appropriate commands 
 * to the harmonica via serial communication. The commands include:
 * - Hole number (using `HarmonicaMapping::getHoleNumber`)
 * - Action (Blow or Draw, using `HarmonicaMapping::getAction`)
 * The program then sleeps for the duration of the note before proceeding to the next event.
 * 
 * @note This method assumes that the MIDI file contains valid "Note On" events and the serial communication 
 *       works without errors. Works best on one track files.
 */
void HarmonicaPlayer::play() {
    int tracks = midiHandler.getMidiFile().getTrackCount();
    
    // Iterate through all tracks
    for (int track = 0; track < tracks; track++) {
        // Iterate through all events in the current track
        for (int event = 0; event < midiHandler.getMidiFile()[track].size(); event++) {
            // Check if the current event is a "Note On" event
            if (midiHandler.getMidiFile()[track][event].isNoteOn()) {
                // Get the note duration and MIDI key number
                double noteDuration = midiHandler.getMidiFile()[track][event].getDurationInSeconds();
                int note = midiHandler.getMidiFile()[track][event].getKeyNumber();

                std::cout << "Playing Note: " << std::dec << note << " for " << noteDuration << " seconds." << std::endl;

                // Send the corresponding hole number to the harmonica via serial communication
                serialComm.write(harmonica.getHoleNumber(note));
                serialComm.read();

                // Send the corresponding action (Blow or Draw) to the harmonica via serial communication
                serialComm.write(harmonica.getAction(note));
                serialComm.read();

                // Sleep for the duration of the note
                std::this_thread::sleep_for(std::chrono::duration<double>(noteDuration));
            }
        }
    }
}

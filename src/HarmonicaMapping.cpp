/**
 * @file HarmonicaMapping.cpp
 * @brief This file contains the implementation of the HarmonicaMapping class, 
 *        which maps MIDI notes to corresponding hole numbers, actions, and note names 
 *        for a harmonica.
 * 
 * The class contains methods to map MIDI numbers to hole numbers, action types (Blow/Draw),
 * and note names, as well as a helper function to get the closest mapping for a given MIDI number.
 * 
 * @author Joseph Blom
 * @date March 2025
 */

#include "HarmonicaMapping.h"
#include <iostream>

/**
 * @brief Constructor that initializes the MIDI-to-harmonica mappings.
 * 
 * The constructor populates three maps: `hole_map`, `action_map`, and `note_name_map`.
 * These maps associate each MIDI note (represented by MIDI numbers) to:
 * - a corresponding hole number on the harmonica,
 * - an action type (either 1000 for Blow or 1001 for Draw),
 * - and a human-readable note name (e.g., "C4").
 * 
 * The constructor sets mappings for several harmonica notes, from "C4" to "C7".
 */
HarmonicaMapping::HarmonicaMapping() {
    // Populate the hole_map, action_map, and note_name_map with correct MIDI numbers and corresponding hole/action
    hole_map[60] = 0;  action_map[60] = 1000;  note_name_map[60] = "C4";  // C4 (Blow, Hole 0)
    hole_map[62] = 0;  action_map[62] = 1001;  note_name_map[62] = "D4";  // D4 (Draw, Hole 0)

    hole_map[64] = 1;  action_map[64] = 1000;  note_name_map[64] = "E4";  // E4 (Blow, Hole 1)
    hole_map[67] = 1;  action_map[67] = 1001;  note_name_map[67] = "G4";  // G4 (Draw, Hole 1)

    hole_map[67] = 2;  action_map[67] = 1000;  note_name_map[67] = "G4";  // G4 (Blow, Hole 2)
    hole_map[71] = 2;  action_map[71] = 1001;  note_name_map[71] = "B4";  // B4 (Draw, Hole 2)

    hole_map[72] = 3;  action_map[72] = 1000;  note_name_map[72] = "C5";  // C5 (Blow, Hole 3)
    hole_map[74] = 3;  action_map[74] = 1001;  note_name_map[74] = "D4";  // D4 (Draw, Hole 3)

    hole_map[76] = 4;  action_map[76] = 1000;  note_name_map[76] = "E5";  // E5 (Blow, Hole 4)
    hole_map[77] = 4;  action_map[77] = 1001;  note_name_map[77] = "F5";  // F5 (Draw, Hole 4)

    hole_map[79] = 5;  action_map[79] = 1000;  note_name_map[79] = "G5";  // G5 (Blow, Hole 5)
    hole_map[81] = 5;  action_map[81] = 1001;  note_name_map[81] = "A5";  // A5 (Draw, Hole 5)

    hole_map[84] = 6;  action_map[84] = 1000;  note_name_map[84] = "C6";  // C6 (Blow, Hole 6)
    hole_map[83] = 6;  action_map[83] = 1001;  note_name_map[83] = "B5";  // B5 (Draw, Hole 6)

    hole_map[88] = 7;  action_map[88] = 1000;  note_name_map[88] = "E6";  // E6 (Blow, Hole 7)
    hole_map[86] = 7;  action_map[86] = 1001;  note_name_map[86] = "D6";  // D6 (Draw, Hole 7)

    hole_map[91] = 8;  action_map[91] = 1000;  note_name_map[91] = "G6";  // G6 (Blow, Hole 8)
    hole_map[89] = 8;  action_map[89] = 1001;  note_name_map[89] = "F6";  // F6 (Draw, Hole 8)

    hole_map[96] = 9;  action_map[96] = 1000;  note_name_map[96] = "C7";  // C7 (Blow, Hole 9)
    hole_map[93] = 9;  action_map[93] = 1001;  note_name_map[93] = "A6";  // A6 (Draw, Hole 9)
}

/**
 * @brief A helper function to retrieve the closest entry for a given MIDI number from a map.
 * 
 * This template function looks for the exact MIDI number in the provided map. If the exact match 
 * is not found, it returns the value corresponding to the closest MIDI number, either higher or lower.
 * 
 * @param map The map to search through (either hole_map, action_map, or note_name_map).
 * @param midiNumber The MIDI number for which we want to find the closest mapping.
 * 
 * @return The value from the map corresponding to the closest MIDI number.
 */
template <typename T>
T HarmonicaMapping::getClosestEntry(const std::map<int, T>& map, int midiNumber) const {
    // Try to find the exact MIDI number
    auto it = map.find(midiNumber);
    if (it != map.end()) {
        return it->second;  // Return the exact value if found
    }

    // If the exact MIDI number is not found, find the closest key
    auto lower = map.lower_bound(midiNumber);

    if (lower == map.begin()) {
        // If the lower bound is the first element, return it
        return lower->second;
    }

    // If the lower bound is not the first element, we can check both lower and previous keys
    auto prev = std::prev(lower);

    // Compare the difference between midiNumber and both the lower and previous keys
    int lowerDiff = std::abs(lower->first - midiNumber);
    int prevDiff = std::abs(prev->first - midiNumber);

    if (lowerDiff < prevDiff) {
        return lower->second;  // Return the value for the closest higher or equal MIDI number
    } else {
        return prev->second;   // Return the value for the closest lower MIDI number
    }
}

/**
 * @brief Get the hole number corresponding to a given MIDI number.
 * 
 * This method looks up the hole number in the `hole_map` for the closest matching MIDI number.
 * 
 * @param midiNumber The MIDI number to search for.
 * 
 * @return The hole number corresponding to the given MIDI number.
 */
int HarmonicaMapping::getHoleNumber(int midiNumber) const {
    return getClosestEntry(hole_map, midiNumber);
}

/**
 * @brief Get the action (1000 for Blow, 1001 for Draw) corresponding to a given MIDI number.
 * 
 * This method looks up the action in the `action_map` for the closest matching MIDI number.
 * 
 * @param midiNumber The MIDI number to search for.
 * 
 * @return The action (1000 for Blow, 1001 for Draw) corresponding to the given MIDI number.
 */
int HarmonicaMapping::getAction(int midiNumber) const {
    return getClosestEntry(action_map, midiNumber);
}

/**
 * @brief Get the note name corresponding to a given MIDI number.
 * 
 * This method looks up the note name in the `note_name_map` for the closest matching MIDI number.
 * 
 * @param midiNumber The MIDI number to search for.
 * 
 * @return The note name (e.g., "C4", "D4", etc.) corresponding to the given MIDI number.
 */
std::string HarmonicaMapping::getNoteName(int midiNumber) const {
    return getClosestEntry(note_name_map, midiNumber);
}

/**
 * @brief Print all MIDI numbers, their corresponding hole numbers, actions, and note names.
 * 
 * This method prints a human-readable list of all the MIDI-to-harmonica mappings in the form of:
 * - MIDI number
 * - Hole number
 * - Action (1000 for Blow, 1001 for Draw)
 * - Note name (e.g., "C4", "D4")
 */
void HarmonicaMapping::printMappings() const {
    std::cout << "\nMIDI Numbers and their Hole numbers and Actions:\n";
    for (const auto& entry : hole_map) {
        int midi = entry.first;
        std::cout << "MIDI number: " << midi << ", Hole: " << entry.second
                  << ", Action: " << action_map.at(midi)
                  << ", Note: " << note_name_map.at(midi) << std::endl;
    }
}

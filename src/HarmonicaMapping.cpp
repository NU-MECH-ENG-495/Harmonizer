#include "HarmonicaMapping.h"
#include <iostream>

// Constructor to initialize the maps with the harmonica note-to-MIDI mappings
HarmonicaMapping::HarmonicaMapping() {
    // Populate the hole_map and action_map with correct MIDI numbers and corresponding hole/action
    hole_map[60] = 0;  action_map[60] = 1000;  note_name_map[60] = "C4";  // C4 (Blow, Hole 0)
    hole_map[62] = 0;  action_map[62] = 1001;  note_name_map[62] = "D4";  // D4 (Draw, Hole 0)
    hole_map[64] = 1;  action_map[64] = 1000;  note_name_map[64] = "E4";  // E4 (Blow, Hole 1)
    hole_map[65] = 1;  action_map[65] = 1001;  note_name_map[65] = "F4";  // F4 (Draw, Hole 1)
    hole_map[67] = 2;  action_map[67] = 1000;  note_name_map[67] = "G4";  // G4 (Blow, Hole 2)
    hole_map[69] = 2;  action_map[69] = 1001;  note_name_map[69] = "A4";  // A4 (Draw, Hole 2)
    hole_map[72] = 3;  action_map[72] = 1000;  note_name_map[72] = "C5";  // C5 (Blow, Hole 3)
    hole_map[71] = 3;  action_map[71] = 1001;  note_name_map[71] = "B4";  // B4 (Draw, Hole 3)
    hole_map[76] = 4;  action_map[76] = 1000;  note_name_map[76] = "E5";  // E5 (Blow, Hole 4)
    hole_map[74] = 4;  action_map[74] = 1001;  note_name_map[74] = "D5";  // D5 (Draw, Hole 4)
    hole_map[79] = 5;  action_map[79] = 1000;  note_name_map[79] = "G5";  // G5 (Blow, Hole 5)
    hole_map[77] = 5;  action_map[77] = 1001;  note_name_map[77] = "F5";  // F5 (Draw, Hole 5)
    hole_map[84] = 6;  action_map[84] = 1000;  note_name_map[84] = "C6";  // C6 (Blow, Hole 6)
    hole_map[83] = 6;  action_map[83] = 1001;  note_name_map[83] = "B5";  // B5 (Draw, Hole 6)
    hole_map[88] = 7;  action_map[88] = 1000;  note_name_map[88] = "E6";  // E6 (Blow, Hole 7)
    hole_map[86] = 7;  action_map[86] = 1001;  note_name_map[86] = "D6";  // D6 (Draw, Hole 7)
    hole_map[91] = 8;  action_map[91] = 1000;  note_name_map[91] = "G6";  // G6 (Blow, Hole 8)
    hole_map[89] = 8;  action_map[89] = 1001;  note_name_map[89] = "F6";  // F6 (Draw, Hole 8)
    hole_map[96] = 9;  action_map[96] = 1000;  note_name_map[96] = "C7";  // C7 (Blow, Hole 9)
}


// Helper function to get the closest value from a given map
template <typename T>
T HarmonicaMapping::getClosestEntry(const std::map<int, T>& map, int midiNumber) const {
    // Try to find the exact MIDI number
    auto it = map.find(midiNumber);
    if (it != map.end()) {
        return it->second;  // Return the exact value if found
    }

    // If the exact MIDI number is not found, find the closest key
    // Use lower_bound to find the first element that is not less than midiNumber
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

// Get the hole number for a given MIDI number
int HarmonicaMapping::getHoleNumber(int midiNumber) const {
    return getClosestEntry(hole_map, midiNumber);
}

// Get the action (1000 (Blow) or 1001 (Draw)) for a given MIDI number
int HarmonicaMapping::getAction(int midiNumber) const {
    return getClosestEntry(action_map, midiNumber);
}

// Get the note name for a given MIDI number
std::string HarmonicaMapping::getNoteName(int midiNumber) const {
    return getClosestEntry(note_name_map, midiNumber);
}


// Print all MIDI numbers, hole numbers, and actions
void HarmonicaMapping::printMappings() const {
    std::cout << "\nMIDI Numbers and their Hole numbers and Actions:\n";
    for (const auto& entry : hole_map) {
        int midi = entry.first;
        std::cout << "MIDI number: " << midi << ", Hole: " << entry.second
                  << ", Action: " << action_map.at(midi)
                  << ", Note: " << note_name_map.at(midi) << std::endl;
    }
}

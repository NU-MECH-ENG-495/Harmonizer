#include "HarmonicaMapping.h"
#include <iostream>

// Constructor to initialize the maps with the harmonica note-to-MIDI mappings
HarmonicaMapping::HarmonicaMapping() {
    // Populate the hole_map and action_map with MIDI numbers and corresponding hole/action
    hole_map[60] = 0;  action_map[60] = 1000;  // C4
    hole_map[62] = 0;  action_map[62] = 1001;  // D4
    hole_map[64] = 1;  action_map[64] = 1000;  // E4
    hole_map[67] = 1;  action_map[67] = 1001;  // G4
    hole_map[67] = 2;  action_map[67] = 1000;  // G4
    hole_map[71] = 2;  action_map[71] = 1001;  // B4
    hole_map[72] = 3;  action_map[72] = 1000;  // C5
    hole_map[74] = 3;  action_map[74] = 1001;  // D5
    hole_map[76] = 4;  action_map[76] = 1000;  // E5
    hole_map[77] = 4;  action_map[77] = 1001;  // F5
    hole_map[79] = 5;  action_map[79] = 1000;  // G5
    hole_map[81] = 5;  action_map[81] = 1001;  // A5
    hole_map[84] = 6;  action_map[84] = 1000;  // C6
    hole_map[83] = 6;  action_map[83] = 1001;  // B5
    hole_map[85] = 7;  action_map[85] = 1000;  // E6
    hole_map[79] = 7;  action_map[79] = 1001;  // G5
    hole_map[80] = 8;  action_map[80] = 1000;  // F6
    hole_map[77] = 8;  action_map[77] = 1001;  // F5
    hole_map[72] = 9; action_map[72] = 1000;  // C5
    hole_map[81] = 9; action_map[81] = 1001;  // A5
}

// Get the hole number for a given MIDI number
int HarmonicaMapping::getHoleNumber(int midiNumber) const {
    // Try to find the exact MIDI number
    auto it = hole_map.find(midiNumber);
    if (it != hole_map.end()) {
        return it->second;  // Return the exact hole number if found
    }

    // If the exact MIDI number is not found, find the closest key
    // Use lower_bound to find the first element that is not less than midiNumber
    auto lower = hole_map.lower_bound(midiNumber);

    if (lower == hole_map.begin()) {
        // If the lower bound is the first element, return it
        return lower->second;
    }

    // If the lower bound is not the first element, we can check both lower and previous keys
    auto prev = std::prev(lower);

    // Compare which of the two is closer to midiNumber
    if (lower == hole_map.end()) {
        // If no higher value is found (it’s past the last element), return the last one
        return prev->second;
    }

    // Compare the difference between midiNumber and both the lower and previous keys
    int lowerDiff = std::abs(lower->first - midiNumber);
    int prevDiff = std::abs(prev->first - midiNumber);

    if (lowerDiff < prevDiff) {
        return lower->second;  // Return the hole number for the closest higher or equal MIDI number
    } else {
        return prev->second;   // Return the hole number for the closest lower MIDI number
    }
}

// Get the action (1000 (Blow) or 1001 (Draw)) for a given MIDI number
int HarmonicaMapping::getAction(int midiNumber) const {
    // Try to find the exact MIDI number
    auto it = action_map.find(midiNumber);
    if (it != action_map.end()) {
        return it->second;  // Return the exact action if found
    }

    // If the exact MIDI number is not found, find the closest key
    // Use lower_bound to find the first element that is not less than midiNumber
    auto lower = action_map.lower_bound(midiNumber);

    if (lower == action_map.begin()) {
        // If the lower bound is the first element, return it
        return lower->second;
    }

    // If the lower bound is not the first element, we can check both lower and previous keys
    auto prev = std::prev(lower);

    // Compare the difference between midiNumber and both the lower and previous keys
    int lowerDiff = std::abs(lower->first - midiNumber);
    int prevDiff = std::abs(prev->first - midiNumber);

    if (lowerDiff < prevDiff) {
        return lower->second;  // Return the action for the closest higher or equal MIDI number
    } else {
        return prev->second;   // Return the action for the closest lower MIDI number
    }
}

// Print all MIDI numbers, hole numbers, and actions
void HarmonicaMapping::printMappings() const {
    std::cout << "\nMIDI Numbers and their Hole numbers and Actions:\n";
    for (const auto& entry : hole_map) {
        int midi = entry.first;
        std::cout << "MIDI number: " << midi << ", Hole: " << entry.second
                  << ", Action: " << action_map.at(midi) << std::endl;
    }
}

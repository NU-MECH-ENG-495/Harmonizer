#ifndef HARMONICA_MAPPING_H
#define HARMONICA_MAPPING_H

#include <map>
#include <string>

// Class to manage MIDI mappings for a C Major harmonica
class HarmonicaMapping {
public:
    // Constructor to initialize the mappings
    HarmonicaMapping();

    // Function to get the hole number for a given MIDI number
    int getHoleNumber(int midiNumber) const;

    // Function to get the action ("Blow" or "Draw") for a given MIDI number
    int getAction(int midiNumber) const;

    // Function to print all MIDI numbers, hole numbers, and actions
    void printMappings() const;

private:
    // Map for MIDI number -> hole number
    std::map<int, int> hole_map;

    // Map for MIDI number -> Blow/Draw action
    std::map<int, int> action_map;
};

#endif // HARMONICA_MAPPING_H

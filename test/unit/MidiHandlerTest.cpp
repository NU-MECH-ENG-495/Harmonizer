#include <gtest/gtest.h>
#include "MidiHandler.h" // Assuming you've included necessary headers

class MidiHandlerTest : public ::testing::Test {
protected:
    MidiHandler midiHandler;

    MidiHandlerTest() : midiHandler("./newTaps.mid") {}
};

TEST_F(MidiHandlerTest, MidiFileLoaded) {
    EXPECT_NO_THROW(midiHandler.getMidiFile().getTrackCount());
}

TEST_F(MidiHandlerTest, DisplayMidiInfo) {
    // Assuming this doesn't produce output during normal testing
    EXPECT_NO_THROW(midiHandler.display());
}

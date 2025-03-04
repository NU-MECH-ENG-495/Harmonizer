#include <gtest/gtest.h>
#include "HarmonicaPlayer.h" // Assuming you've included necessary headers

class HarmonicaPlayerTest : public ::testing::Test {
protected:
    MockSerialPort mock_serial;
    MidiHandler midiHandler;
    Harmonica harmonica;
    HarmonicaPlayer player;

    HarmonicaPlayerTest() 
        : midiHandler("./newTaps.mid"), 
          player(mock_serial, harmonica, midiHandler) {}

    void SetUp() override {
        // Mock behavior of SerialCommunication
        ON_CALL(mock_serial, IsDataAvailable()).WillByDefault(testing::Return(true));
        ON_CALL(mock_serial, Read(testing::_ , testing::_ , testing::_)).WillByDefault(testing::Invoke([](DataBuffer& buffer, size_t, size_t) {
            buffer.push_back('a');  // Simulating data read
        }));
    }
};

TEST_F(HarmonicaPlayerTest, PlayNoteSequence) {
    // Mock the MIDI file reading and validate that play works as expected
    EXPECT_CALL(mock_serial, Write(testing::_)).Times(testing::AtLeast(1)); // Expect write to be called
    EXPECT_CALL(mock_serial, Read(testing::_ , testing::_ , testing::_)).Times(testing::AtLeast(1)); // Expect read to be called

    EXPECT_NO_THROW(player.play());
}

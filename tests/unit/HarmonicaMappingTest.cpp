#include <gtest/gtest.h>
#include "HarmonicaMapping.h" // Assuming you've included necessary headers

class HarmonicaTest : public ::testing::Test {
protected:
    Harmonica harmonica;

    void SetUp() override {
        // Initialize the harmonica or mock its behavior if needed
    }
};

TEST_F(HarmonicaTest, GetHoleNumber) {
    EXPECT_EQ(harmonica.getHoleNumber(40), 3); // Assuming MIDI note 40 maps to hole 3
}

TEST_F(HarmonicaTest, GetAction) {
    EXPECT_EQ(harmonica.getAction(40), 1); // Assuming MIDI note 40 results in action 1 (e.g., blow)
}

#include <gtest/gtest.h>
#include "HarmonicaMapping.h"

class HarmonicaTest : public ::testing::Test {
protected:
    HarmonicaMapping harmonica;

    void SetUp() override {
        // Initialize the harmonica or mock its behavior if needed
    }
};

TEST_F(HarmonicaTest, GetHoleNumber) {
    EXPECT_EQ(harmonica.getHoleNumber(60), 0); // Assuming MIDI note 40 maps to hole 3
}

TEST_F(HarmonicaTest, GetAction) {
    EXPECT_EQ(harmonica.getAction(60), 1000); // Assuming MIDI note 40 results in action 1 (e.g., blow)
}

TEST_F(HarmonicaTest, GetNoteName) {
    EXPECT_EQ(harmonica.getNoteName(60), "C4"); // Assuming MIDI note 40 results in action 1 (e.g., blow)
}

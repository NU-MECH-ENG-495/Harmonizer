#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SerialCommunication.h" // Assuming you've included necessary headers

using namespace LibSerial;
using namespace std;

// Mock class for SerialPort
class MockSerialPort : public SerialPort {
public:
    MOCK_METHOD(void, Open, (const std::string& port_name), (override));
    MOCK_METHOD(void, SetBaudRate, (BaudRate rate), (override));
    MOCK_METHOD(void, Write, (const std::string& data), (override));
    MOCK_METHOD(void, Read, (DataBuffer& buffer, size_t num_bytes, size_t timeout), (override));
    MOCK_METHOD(bool, IsDataAvailable, (), (override));
};

// Test the SerialCommunication class
class SerialCommunicationTest : public ::testing::Test {
protected:
    MockSerialPort mock_serial;
    SerialCommunication serialComm;

    SerialCommunicationTest() : serialComm("/dev/ttyACM0") {}

    void SetUp() override {
        ON_CALL(mock_serial, IsDataAvailable()).WillByDefault(testing::Return(true));
        ON_CALL(mock_serial, Read(testing::_ , testing::_ , testing::_)).WillByDefault(testing::Invoke([](DataBuffer& buffer, size_t, size_t) {
            buffer.push_back('a');  // Simulating data read
        }));
    }
};

TEST_F(SerialCommunicationTest, WriteToPort) {
    EXPECT_CALL(mock_serial, Write(testing::_)).Times(1);
    serialComm.write(123);
}

TEST_F(SerialCommunicationTest, ReadFromPort) {
    EXPECT_CALL(mock_serial, Read(testing::_ , testing::_ , testing::_)).Times(1);
    serialComm.read();
}

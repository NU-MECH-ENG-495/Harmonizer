#include <TMC2209.h>

// SoftwareSerial can be used on Arduino boards without HardwareSerial ports,
// such as the Uno, Nano, and Mini.
//
// See this reference for more details:
// https://www.arduino.cc/reference/en/language/functions/communication/serial/

// Software serial ports should only be used for unidirectional communication
// The RX pin does not need to be connected, but it must be specified when
// creating an instance of a SoftwareSerial object
const uint8_t RX_PIN = 7;
const uint8_t TX_PIN = 6;
SoftwareSerial soft_serial(RX_PIN, TX_PIN);

const uint8_t STEP_PIN = 4;
const uint8_t DIRECTION_PIN = 3;
const uint8_t MOF1 = 9;
const uint8_t MOF2 = 10;

const uint32_t STEP_PER_SCALE = 2300;
const uint16_t HALF_STEP_DURATION_MICROSECONDS = 20;
const uint16_t STOP_DURATION = 1000;
// current values may need to be reduced to prevent overheating depending on
// specific motor and power supply voltage
const uint8_t RUN_CURRENT_PERCENT = 100;


// Instantiate TMC2209
TMC2209 stepper_driver;

String inString = "";  // string to hold input

int position = 0;
int newPosition = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");

  stepper_driver.setup(soft_serial);

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIRECTION_PIN, OUTPUT);
  pinMode(MOF1, OUTPUT);
  pinMode(MOF2, OUTPUT);

  digitalWrite(MOF1, 1);
  digitalWrite(MOF2, 0);

  stepper_driver.setRunCurrent(RUN_CURRENT_PERCENT);
  stepper_driver.enableCoolStep();
  stepper_driver.enable();
}

void loop()
{
  recvWithEndMarker();
}

void stepFromPosition(int from, int to) {
  int shift = 0;
  if (to > from) {
    shift = to - from;
    digitalWrite(DIRECTION_PIN, 0);
  } else {
    shift = from - to;
    digitalWrite(DIRECTION_PIN, 1);
  }

  for (uint32_t i=0; i<STEP_PER_SCALE*2*shift; ++i)
  {
    digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
    delayMicroseconds(HALF_STEP_DURATION_MICROSECONDS);
  }
}

void recvWithEndMarker() {
    while (Serial.available()==0) {}
    while (Serial.available() > 0) {
      int inChar = Serial.read();
      if (isDigit(inChar)) {
        // convert the incoming byte to a char and add it to the string:
        inString += (char)inChar;
      }
      // if you get a newline, print the string, then the string's value:
      if (inChar == '\n') {
        newPosition = inString.toInt();

        if (newPosition > -1 && newPosition < 10) {
          stepFromPosition(position, newPosition);
          position = newPosition;

          Serial.print("Arrived at step: ");
          Serial.println(position);
        } else if (newPosition == 1001) {
          digitalWrite(MOF1, 0);
          digitalWrite(MOF2, 1);
          Serial.println("Closed");
        } else if (newPosition == 1000) {
          digitalWrite(MOF1, 1);
          digitalWrite(MOF2, 0);
          Serial.println("Opened");
        }
        // clear the string for new input:
        inString = "";
      }
  }
}
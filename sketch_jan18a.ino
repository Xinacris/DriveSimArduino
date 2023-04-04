#include <Joystick.h>

// Create an instance of the Joystick library
Joystick_ Joystick;

// Pin connected to the potentiometer for the steering wheel
const int STEER_PIN = A0;

// Pin connected to the potentiometer for the accelerator
const int ACCEL_PIN = A1;

// Pin connected to the potentiometer for the brake
const int BRAKE_PIN = A2;

// Pin connected to the potentiometer for the clutch
const int CLUTCH_PIN = A3;

// Pin connected to the button for shifting up
const int GEAR_F1 = 2;
const int GEAR_F2 = 3;
const int GEAR_F3 = 4;
const int GEAR_F4 = 5;
const int GEAR_F5 = 6;
const int GEAR_R = 7;


// Pin connected to the button for the handbrake
const int HANDBRAKE_PIN = 9 ;

//Variable for the gear
int gear = 0;

void setup() {
  // Set the pins connected to the potentiometers as inputs
  pinMode(STEER_PIN, INPUT);
  pinMode(ACCEL_PIN, INPUT);
  pinMode(BRAKE_PIN, INPUT);
  pinMode(CLUTCH_PIN, INPUT);
  
  // Set the pins connected to the buttons as inputs
  pinMode(GEAR_F1, INPUT_PULLUP);
  pinMode(GEAR_F2, INPUT_PULLUP);
  pinMode(GEAR_F3, INPUT_PULLUP);
  pinMode(GEAR_F4, INPUT_PULLUP);
  pinMode(GEAR_F5, INPUT_PULLUP);
  pinMode(GEAR_R, INPUT_PULLUP);
  pinMode(HANDBRAKE_PIN, INPUT_PULLUP);

  // Initialize the Joystick library
  Joystick.begin(false);
}

void loop() {
  // Read the values of the potentiometers
  int steerVal = analogRead(STEER_PIN);
  int accelVal = analogRead(ACCEL_PIN);
  int brakeVal = analogRead(BRAKE_PIN);
  int clutchVal = analogRead(CLUTCH_PIN);

  // Map the potentiometer values to values between -32767 and 32767
  int mappedSteerVal = map(steerVal, 0, 1023, -32767, 32767);
  int mappedAccelVal = map(accelVal, 0, 1023, 0, 32767);
  int mappedBrakeVal = map(brakeVal, 0, 1023, 0, 32767);
  int mappedClutchVal = map(clutchVal, 0, 1023, 0, 32767);
  // Set the values of the axes on the joystick
  Joystick.setXAxis(mappedSteerVal);
  Joystick.setYAxis(mappedAccelVal);
  Joystick.setZAxis(mappedBrakeVal);
  Joystick.setRzAxis(mappedClutchVal);

  // Check if the gear shift up button is pressed
  if (digitalRead(GEAR_F1) == LOW) {
    gear=1;
  }
  
   if (digitalRead(GEAR_F2) == LOW) {
    gear=2;
  }
   if (digitalRead(GEAR_F3) == LOW) {
    gear=3;
  }

 if (digitalRead(GEAR_F4) == LOW) {
    gear=4;
  }

 if (digitalRead(GEAR_F5) == LOW) {
    gear=5;
  }

  // Check if the gear shift reverse button is pressed
  if (digitalRead(GEAR_R) == LOW) {
    gear = -1;
  }

  // Check if the handbrake button is pressed
  if (digitalRead(HANDBRAKE_PIN) == LOW) {
    Joystick.setButton(gear, 1);
  } else {
    Joystick.setButton(gear, 0);
  }

  // Send the updated joystick values
  Joystick.sendState();
}
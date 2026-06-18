#include <Servo.h>

/*
  Robotic Eye Control System
  --------------------------
  Controls:
  - Eyelid servo using joystick button
  - Eye movement servo using joystick Y-axis

  Hardware:
  - Arduino Uno
  - 2 Servo Motors
  - Joystick Module

  Author: Aviral
*/

Servo eyelidServo;
Servo eyeServo;

// ---------------- PIN CONFIG ----------------
const int EYELID_SERVO_PIN = 3;
const int EYE_SERVO_PIN = 4;

const int JOYSTICK_Y_PIN = A1;
const int BUTTON_PIN = 7;

// ---------------- SERVO POSITIONS ----------------
const int EYELID_OPEN = 0;
const int EYELID_CLOSED = 90;

// ---------------- SETTINGS ----------------
const int SERVO_MIN = 0;
const int SERVO_MAX = 180;

int joystickYValue = 0;
int eyePosition = 0;
bool buttonPressed = false;

void setup() {

  Serial.begin(9600);

  // Attach servos
  eyelidServo.attach(EYELID_SERVO_PIN);
  eyeServo.attach(EYE_SERVO_PIN);

  // Configure joystick button
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Initial eyelid position
  eyelidServo.write(EYELID_OPEN);

  Serial.println("Eye control system initialized.");
}

void loop() {

  readInputs();
  controlEyelid();
  controlEyeMovement();
  printDebugInfo();

  delay(40);
}

// ==================================================
// INPUT HANDLING
// ==================================================

void readInputs() {

  buttonPressed = (digitalRead(BUTTON_PIN) == LOW);

  joystickYValue = analogRead(JOYSTICK_Y_PIN);

  eyePosition = map(
    joystickYValue,
    0,
    1023,
    SERVO_MIN,
    SERVO_MAX
  );
}

// ==================================================
// SERVO CONTROL
// ==================================================

void controlEyelid() {

  if (buttonPressed) {
    eyelidServo.write(EYELID_CLOSED);
  } else {
    eyelidServo.write(EYELID_OPEN);
  }
}

void controlEyeMovement() {

  eyeServo.write(eyePosition);
}

// ==================================================
// DEBUGGING
// ==================================================

void printDebugInfo() {

  Serial.print("Button: ");
  Serial.print(buttonPressed);

  Serial.print(" | Eye Position: ");
  Serial.println(eyePosition);
}

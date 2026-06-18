#include <Servo.h> // include servo library

Servo servo1; // define servo1
Servo servo2; // define servo2

int servo1_pin = 3; // Pin for servo1
int servo2_pin = 4; // Pin for servo2 (controlled by Y-axis)
int joyY = A1; // Joystick Y connected to analog pin A1
int buttonPin = 7; // Joystick button (SW pin) connected to digital pin D7

int joyValY; // create variable for joystick Y-axis value
int buttonState = 0; // Variable to store the button state

void setup() {
  // Start serial communication (optional for debugging)
  Serial.begin(9600); 
  
  // Attach servos to specified pins
  servo1.attach(servo1_pin); // Attach servo1 to pin 3
  servo2.attach(servo2_pin); // Attach servo2 to pin 4
  
  // Set button pin as input
  pinMode(buttonPin, INPUT_PULLUP); // Use the internal pull-up resistor for the button

  // Initialize servo1 to start at 180 degrees
  servo1.write(180); // Start position for servo1
  delay(1000); // Delay to allow servo to reach position
}

void loop() {
  // Read the state of the joystick button (SW pin)
  buttonState = digitalRead(buttonPin);

  // If the button is pressed, move servo1 to 90 degrees
  if (buttonState == LOW) { // LOW means the button is pressed (because of the pull-up resistor)
    servo1.write(90); // Move servo1 to 90 degrees
  } else {
    // If the button is not pressed, keep servo1 at 180 degrees
    servo1.write(0); // Keep servo1 at 180 degrees
  }

  // Read value from joystick Y axis (vertical movement) and map to 0-180 degrees for servo2
  joyValY = analogRead(joyY); // Read value from Y-axis
  joyValY = map(joyValY, 0, 1023, 0, 180); // Map value to 0-180 degrees
  servo2.write(joyValY); // Move servo2 based on Y-axis joystick movement

  // Debugging: Print button state and Y-axis value (optional)
  Serial.print("Button: ");
  Serial.print(buttonState);
  Serial.print(" | Joystick Y: ");
  Serial.println(joyValY);

  delay(40); // Small delay for smoother movement
}

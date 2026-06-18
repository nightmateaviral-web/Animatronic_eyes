#include <Servo.h>

Servo servo1; 
Servo servo2;

int servo1_pin = 3;
int servo2_pin = 4;

int joyY = A1;
int buttonPin = 7;

int joyValY;
int buttonState = 0;


void setup() {
  Serial.begin(9600);

  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);

  pinMode(buttonPin, INPUT_PULLUP);

  // Start centered
  servo1.write(0);   // eyelid open (adjust if needed)
  servo2.write(90);  // eye center
}

void loop() {

  // ---------- BLINK ----------
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    servo1.write(90); // blink
  } else {
    servo1.write(0);  // open
  }

  // ---------- EYE MOVEMENT ----------
  joyValY = analogRead(joyY);

  int angle;

  // DEAD ZONE (this fixes your problem)
  if (joyValY > 480 && joyValY < 540) {
    angle = 90; // force center
  } else {
    angle = map(joyValY, 0, 1023, 0, 180);
  }

  servo2.write(angle);

  Serial.print("Joystick Y: ");
  Serial.print(joyValY);
  Serial.print(" | Angle: ");
  Serial.println(angle);

  delay(15);
}

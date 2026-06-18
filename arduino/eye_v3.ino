#include <Servo.h>

Servo eyelid;
Servo eye;

int eyelidPin = 3;
int eyePin = 4;

int joyY = A1;
int buttonPin = 7;

int currentPos = 90;

// Blink timing
unsigned long lastBlink = 0;
int blinkInterval = 3000; // will randomize

void setup() {
  Serial.begin(9600);

  eyelid.attach(eyelidPin);
  eye.attach(eyePin);

  pinMode(buttonPin, INPUT_PULLUP);

  // Start closed
  eyelid.write(90);
  delay(500);

  // Open slowly
  for (int i = 90; i >= 0; i--) {
    eyelid.write(i);
    delay(10);
  }

  eye.write(90);

  // random seed
  randomSeed(analogRead(0));
}

void loop() {

  // ---------- AUTO BLINK ----------
  unsigned long now = millis();

  if (now - lastBlink > blinkInterval) {
    blinkEye();
    lastBlink = now;
    blinkInterval = random(2000, 6000); // next blink
  }

  // ---------- BUTTON BLINK ----------
  if (digitalRead(buttonPin) == LOW) {
    blinkEye();
    delay(200);
  }

  // ---------- JOYSTICK ----------
  int joyVal = analogRead(joyY);
  int target;

  if (joyVal > 470 && joyVal < 550) {
    target = 90;
  } else {
    target = map(joyVal, 0, 1023, 0, 180);
  }

  // smooth movement
  if (currentPos < target) currentPos++;
  else if (currentPos > target) currentPos--;

  eye.write(currentPos);

  delay(10);
}

// ---------- BLINK FUNCTION ----------
void blinkEye() {
  // close
  for (int i = 0; i <= 90; i++) {
    eyelid.write(i);
    delay(5);
  }

  // hold closed
  delay(random(50, 200));

  // open
  for (int i = 90; i >= 0; i--) {
    eyelid.write(i);
    delay(5);
  }
}

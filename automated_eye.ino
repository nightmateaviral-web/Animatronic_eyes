#include <Servo.h>

Servo eyelid;
Servo eye;

int eyelidPin = 3;
int eyePin = 4;

int joyY = A1;
int buttonPin = 7;

int currentPos = 90;

// Blink system
unsigned long lastBlink = 0;
unsigned long blinkInterval = 3000;

bool isBlinking = false;
int blinkStage = 0;
int eyelidPos = 0;

void setup() {
  Serial.begin(9600);

  eyelid.attach(eyelidPin);
  eye.attach(eyePin);

  pinMode(buttonPin, INPUT_PULLUP);

  eyelid.write(0); // open
  eye.write(90);

  randomSeed(analogRead(0));
}

void loop() {

  unsigned long now = millis();

  // ---------- AUTO BLINK TRIGGER ----------
  if (!isBlinking && (now - lastBlink > blinkInterval)) {
    isBlinking = true;
    blinkStage = 0;
  }

  // ---------- BUTTON BLINK ----------
  if (digitalRead(buttonPin) == LOW) {
    isBlinking = true;
    blinkStage = 0;
  }

  // ---------- BLINK STATE MACHINE ----------
  if (isBlinking) {

    if (blinkStage == 0) { 
      eyelidPos += 3; // closing
      if (eyelidPos >= 90) {
        eyelidPos = 90;
        blinkStage = 1;
        lastBlink = now;
      }
    }

    else if (blinkStage == 1) { 
      if (now - lastBlink > 100) { // hold closed
        blinkStage = 2;
      }
    }

    else if (blinkStage == 2) { 
      eyelidPos -= 3; // opening
      if (eyelidPos <= 0) {
        eyelidPos = 0;
        isBlinking = false;
        blinkInterval = random(2000, 6000);
        lastBlink = now;
      }
    }

    eyelid.write(eyelidPos);
  }

  // ---------- JOYSTICK ----------
  int joyVal = analogRead(joyY);
  int target;

  if (joyVal > 470 && joyVal < 550) {
    target = 90;
  } else {
    target = map(joyVal, 0, 1023, 30, 150);
  }

  // smooth movement
  if (currentPos < target) currentPos++;
  else if (currentPos > target) currentPos--;

  eye.write(currentPos);

  delay(10);
}

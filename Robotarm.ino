#include <Servo.h>

Servo baseServo;
Servo jointServo;

const int basePotiPin = A0;
const int jointPotiPin = A1;

int baseAngle = 90;
int jointAngle = 90;

const int deadzone = 8;      // Totzone gegen Zittern
const float smooth = 0.15;  // Glättung (0.1–0.3 gut)

void setup() {
  baseServo.attach(10);
  jointServo.attach(9);

  baseServo.write(baseAngle);
  jointServo.write(jointAngle);
}

void loop() {
  int rawBase = analogRead(basePotiPin);
  int rawJoint = analogRead(jointPotiPin);

  int targetBase = map(rawBase, 0, 1023, 0, 180);
  int targetJoint = map(rawJoint, 0, 1023, 0, 180);

  // Glättung (low-pass filter)
  baseAngle = baseAngle + smooth * (targetBase - baseAngle);
  jointAngle = jointAngle + smooth * (targetJoint - jointAngle);

  baseServo.write(baseAngle);
  jointServo.write(jointAngle);

  delay(10);
}

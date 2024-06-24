#include "MeOrion.h"
// #include <Arduino.h>
#include "SoftwareSerial.h"
#include <HardwareSerial.h>
#include <Wire.h>

MeEncoderMotor motor1(0x09, SLOT1);
MeEncoderMotor motor2(0x09, SLOT2);
MeEncoderMotor motor3(0x08, SLOT1);
MeEncoderMotor motor4(0x08, SLOT2);

int moveSpeed = 25;
unsigned char stop_flag = 0;

void setup() {
  Serial.begin(9600);
  motor1.begin();
  motor2.begin();
  motor3.begin();
  motor4.begin();
}

void loop() {
  Stop_run();
  control();
}

void control() {
  if (Seiral.available() <= 0) {
    Serial.print("no device found!\n");
    delay(100);
  } else {
    String speed = Serial.readStringUntil(' ').toFloat();
    String direction = Serial.readStringUntil('\n');
    //int len = usbhost.host_recv(); // Read data length
    parseJoystick(speed, direction);
    delay(5);
  }
}

void parseJoystick(float speed, String direction) {

  float currentSpeed = int(moveSpeed*speed);

  if (direction=='UP')
  {
    Forward_run(currentSpeed);
  }
  else if (direction=='DOWN')
  {
    Backward_run(currentSpeed);
  }
  else if (direction=='RIGHT')
  {
    Right_run(currentSpeed);
  }
  else if (direction=='LEFT')
  {
    Left_run(currentSpeed);
  }
  else if (direction=='RIGHTUP')
  {
    RightUp_run(currentSpeed);
  }
  else if (direction=='RIGHTDOWN')
  {
    RightDown_run(currentSpeed);
  }
  else if (direction=='LEFTUP')
  {
    LeftUp_run(currentSpeed);
  }
  else if (direction=='LEFTDOWN')
  {
    LeftDown_run(currentSpeed);
  }
  else if (direction=='STOP')
  {
    Stop_run(currentSpeed);
  }
}

// ALL MOVES
void Forward_run() {
  motor1.runSpeed(-moveSpeed);
  motor2.runSpeed(moveSpeed);
  motor3.runSpeed(-moveSpeed);
  motor4.runSpeed(moveSpeed);
}
void Backward_run() {
  motor1.runSpeed(moveSpeed);
  motor2.runSpeed(-moveSpeed);
  motor3.runSpeed(moveSpeed);
  motor4.runSpeed(-moveSpeed);
}
void Right_run() {
  motor1.runSpeed(-moveSpeed);
  motor2.runSpeed(-moveSpeed);
  motor3.runSpeed(moveSpeed);
  motor4.runSpeed(moveSpeed);
}
void Left_run() {
  motor1.runSpeed(moveSpeed);
  motor2.runSpeed(moveSpeed);
  motor3.runSpeed(-moveSpeed);
  motor4.runSpeed(-moveSpeed);
}
void RightDown_run() {
  motor1.runSpeed(0);
  motor2.runSpeed(-moveSpeed);
  motor3.runSpeed(moveSpeed);
  motor4.runSpeed(0);
}
void RightUp_run() {
  motor1.runSpeed(-moveSpeed);
  motor2.runSpeed(0);
  motor3.runSpeed(0);
  motor4.runSpeed(moveSpeed);
}
void LeftDown_run() {
  motor1.runSpeed(moveSpeed);
  motor2.runSpeed(0);
  motor3.runSpeed(0);
  motor4.runSpeed(-moveSpeed);
}
void LeftUp_run() {
  motor1.runSpeed(0);
  motor2.runSpeed(moveSpeed);
  motor3.runSpeed(-moveSpeed);
  motor4.runSpeed(0);
}
void TurnRight_run() {
  motor1.runSpeed(-moveSpeed);
  motor2.runSpeed(-moveSpeed);
  motor3.runSpeed(-moveSpeed);
  motor4.runSpeed(-moveSpeed);
}
void TurnLeft_run() {
  motor1.runSpeed(moveSpeed);
  motor2.runSpeed(moveSpeed);
  motor3.runSpeed(moveSpeed);
  motor4.runSpeed(moveSpeed);
}

void Speed_up() {
  moveSpeed = moveSpeed + 3;
  if (moveSpeed > 50)
    moveSpeed = 50;
}
void Speed_down() {
  moveSpeed = moveSpeed - 3;
  if (moveSpeed < 0)
    moveSpeed = 0;
}
void Stop_run() {
  motor1.runSpeed(0);
  motor2.runSpeed(0);
  motor3.runSpeed(0);
  motor4.runSpeed(0);
}

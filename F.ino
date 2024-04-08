#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4LCD lcd;
Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4Buzzer buzzer;
Zumo32U4ButtonA buttonA;
Zumo32U4LCD display;
Zumo32U4IMU imu;

#include "TurnSensor.h"

unsigned int lineSensorValues[3];
int detectedhouse = 0;
const uint16_t turnSpeed = 200;// Motor speed when turning.  400 is the max speed.
const int DetectBorder = 600; // Threshold for detecting a line (black space)
const int OpenSpace = 250; // Lower threshold for detecting white space, potentially adjust based on your setup


void setup() {
  turnSensorSetup();
  lineSensors.initThreeSensors();
  proxSensors.initThreeSensors();
}

void loop() {
  while(detectedhouse <= 2) {
    navigateMaze();
    if (detectHouse()) {
      detectedhouse++;

      turnAround();
    }
  } 
  ledGreen(1)
  ReturnHome();
}

void navigateMaze() {
    lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
    if (lineSensorValues[0] > DetectBorder || lineSensorValues[1] > DetectBorder || lineSensorValues[2] > DetectBorder) {
      motors.setSpeeds(0, 0); // Stop to decide next move
    if (return lineSensorValues[2] < DetectBorder;) {
      turnRight();// If right is clear, prefer turning right
    } else if (return lineSensorValues[0] < DetectBorder;) {
      turnLeft();// If cannot turn right but can go forward, proceed
    } else if (return lineSensorValues[0] < OpenSpace;) {
      motors.setSpeeds(100, 100);// If right and forward are blocked, try left
    } else {
      goBackWard();
      delay(550); 
      turnAround();
    }
  } else {
  goStraight();
}
  

}

void Right() {
  motors.setSpeeds(turnSpeed, -turnSpeed);
  while((int32_t)turnAngle > -turnAngle45){
    turnSensorUpdate();
  }
  motors.setSpeeds(0, 0);
}

void Left() {
  motors.setSpeeds(-turnSpeed, turnSpeed);
  while((int32_t)turnAngle < turnAngle45){
    turnSensorUpdate();
  }
  motors.setSpeeds(0, 0);
}

void turnAround() {
  motors.setSpeeds(-turnSpeed, turnSpeed);
  while((int32_t)turnAngle < turnAngle45 * 3){
    turnSensorUpdate();
  }
  motors.setSpeeds(0, 0);
}

void goBackWard() {
  motors.setSpeeds(-100, 100);
  delay(100);
  motors.setSpeeds(0, 0);
}

bool detectHouse() {
  proxSensors.read();
  int center_leftsensor = proxSensors.countsFrontWithLeftLeds();
  int center_rightsensor = proxSensors.countsFrontWithRightLeds();

  if (center_leftsensor == 6 && center_rightsensor == 6) {//change
      buzzer.playFrequency(440, 200, 15);
      delay(1000);
      return true;
  }else{
    return false;
  }
}

void ReturnHome() {

}

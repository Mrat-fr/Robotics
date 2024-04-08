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
const uint16_t turnSpeed = 200;
const int DetectBorder = 600; //detecting black line 
const int OpenSpace = 250; //detecting white space


void setup() {
  turnSensorSetup();
  lineSensors.initThreeSensors();
  proxSensors.initThreeSensors();
}

void loop() {
  while(detectedhouse == 0) {
    navigateMaze();
    if (detectHouse()) {
      detectedhouse++;

      turnAround();
    }
  } 
  ledGreen(1);
}

void navigateMaze() {
    lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
    if (lineSensorValues[0] > DetectBorder || lineSensorValues[1] > DetectBorder || lineSensorValues[2] > DetectBorder) {
      motors.setSpeeds(0, 0);
    if (lineSensorValues[2] < DetectBorder) {
      BackWard();
      Right();
    } else if (lineSensorValues[0] < DetectBorder) {
      BackWard();
      Left();
    } else if (lineSensorValues[0] < OpenSpace) {
      BackWard();
      motors.setSpeeds(100, 100);
    } else {
      BackWard();
      turnAround();
    }
  } else {
  motors.setSpeeds(100, 100);
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

void BackWard() {
  motors.setSpeeds(200, -200);
  delay(100);
  motors.setSpeeds(0, 0);
}

bool detectHouse() {
  proxSensors.read();
  int center_leftsensor = proxSensors.countsFrontWithLeftLeds();
  int center_rightsensor = proxSensors.countsFrontWithRightLeds();

  if (center_leftsensor == 6 && center_rightsensor == 6) {//change
    motors.setSpeeds(0, 0);
    buzzer.playFrequency(440, 200, 15);
    delay(1000);
    return true;
  }else{
    return false;
  }
}


# Robotics

My code consists of 2 files the F.ino which has the main code and the TurnSensor.h which I imported from example codes which implements gyro and helps detect which angle the robot is facing which will help when it comes to moving the Zumo. The important functions are turnSensorSetup to calibrate the Gyro and turnSensorUpdate which returns with how much the Zumo has moved.

For the main code we declare values that we would be using throughout the code so that would be the lineSensorValues, how many houses are detected and the detection thresholds.

Then for the setup I just have the turnSensorSetup and starting up the line Sensors and proximity Sensors.

For the loop we want the Zumo to keep looking for houses until we found the amount we need and to do that we use the navigateMaze() to explore util the detectHouse() goes off which just uses the proximity Sensors to see if there is a house in front of the Zumo.

The navigateMaze() works by using the line sensors and having the Zumo move forward until once one of the line Sensors goes the Zumo stops and makes a decision, if it can see an open space on the left it goes backwards and turns left, if not then if there is an open space right it goes backwards and turns right. If both sides are blocked, then the Zumo will do a 180 and go forwards. This goes on until all the houses are detected.

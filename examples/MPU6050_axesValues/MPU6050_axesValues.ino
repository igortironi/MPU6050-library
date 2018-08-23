/*
 * Exemple code wrote By Igor Tironi.
 * 23/08/2018.
 * library version 1.0
*/
#include <MPU6050.h>

MPU6050 gyroscope;  //declaring object "gyroscope".

void setup() {
  gyroscope.begin();            //initializing the gyroscope.
  gyroscope.config_filter(6);   //setting a 5Hz low pass filter.
  gyroscope.config_gyro(3);     //setting a full 2000°/s scale.
  gyroscope.config_accel(3);    //setting a full 16g scale.
   
  Serial.begin(115200);         //initializing the serial communication;
}

void loop() {
  Serial.print("x_accel: ");            //from here we are acquiring the axes values and sending to the computer via serial communication.
  Serial.print(gyroscope.x_accel());
  Serial.print(" | y_accel: ");
  Serial.print(gyroscope.y_accel());
  Serial.print(" | z_accel: ");
  Serial.print(gyroscope.z_accel());
  Serial.print(" | x_gyro: ");
  Serial.print(gyroscope.x_gyro());
  Serial.print(" | y_gyro: ");
  Serial.print(gyroscope.y_gyro());
  Serial.print(" | z_gyro: ");
  Serial.println(gyroscope.z_gyro());
  delay(100);
}
//end;

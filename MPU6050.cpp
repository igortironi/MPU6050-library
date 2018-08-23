/*  MPU6050.cpp - Class file for the MPU6050 Triple Axis Gyroscope & Accelerometer Arduino Library.

    BY by Igor Tironi.
    23/04/2018.
    Version 1.0

        This program is free software: you can redistribute it and/or modify
    it under the terms of the version 3 GNU General Public License as
    published by the Free Software Foundation.

        This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/
#include "arduino.h"
#include "MPU6050.h"

#include <Wire.h>

MPU6050::MPU6050(){
}


void MPU6050::begin(){
    Wire.begin();

    Wire.beginTransmission(ADDR);
    Wire.write(PWR_MGMT_1);
    Wire.write(0);
    Wire.endTransmission(true);
}


void MPU6050::config_accel(int8_t data){
    if(data>=0 && data<=3){
        Wire.beginTransmission(ADDR);
        Wire.write(ACCEL_CONFIG);
        Wire.write(data<<3);
        Wire.endTransmission(true);
    }

}


void MPU6050::config_gyro(int8_t data){
    if(data>=0 && data<=3){
        Wire.beginTransmission(ADDR);
        Wire.write(GYRO_CONFIG);
        Wire.write(data<<3);
        Wire.endTransmission(true);
        Gyro_scale = data;
    }

}


void MPU6050::config_filter(int8_t data){
    if(data>=0 && data<=6){
        Wire.beginTransmission(ADDR);
        Wire.write(CONFIG);
        Wire.write(data);
        Wire.endTransmission(true);
    }
}


int MPU6050::x_accel(){
    int result=0;
    Wire.beginTransmission(ADDR);
    Wire.write(ACCEL_XOUT_H);
    Wire.endTransmission(false);

    Wire.requestFrom(ADDR, 2, true);
    result = Wire.read()<<8|Wire.read();

    return result;
}

int MPU6050::y_accel(){
    int result=0;
    Wire.beginTransmission(ADDR);
    Wire.write(ACCEL_YOUT_H);
    Wire.endTransmission(false);

    Wire.requestFrom(ADDR, 2, true);
    result = Wire.read()<<8|Wire.read();

    return result;
}

int MPU6050::z_accel(){
    int result=0;
    Wire.beginTransmission(ADDR);
    Wire.write(ACCEL_ZOUT_H);
    Wire.endTransmission(false);

    Wire.requestFrom(ADDR, 2, true);
    result = Wire.read()<<8|Wire.read();

    return result;
}


int MPU6050::x_gyro(){
    int result=0;
    Wire.beginTransmission(ADDR);
    Wire.write(GYRO_XOUT_H);
    Wire.endTransmission(false);

    Wire.requestFrom(ADDR, 2, true);
    result = Wire.read()<<8|Wire.read();

    return result;
}

int MPU6050::y_gyro(){
    int result=0;
    Wire.beginTransmission(ADDR);
    Wire.write(GYRO_YOUT_H);
    Wire.endTransmission(false);

    Wire.requestFrom(ADDR, 2, true);
    result = Wire.read()<<8|Wire.read();

    return result;
}

int MPU6050::z_gyro(){
    int result=0;
    Wire.beginTransmission(ADDR);
    Wire.write(GYRO_ZOUT_H);
    Wire.endTransmission(false);

    Wire.requestFrom(ADDR, 2, true);
    result = Wire.read()<<8|Wire.read();

    return result;
}


void MPU6050::gyro(int16_t angle){
    float scale;
    volatile float total = 0;
    volatile int value;
    int normal;


    switch (Gyro_scale){
        case 0:
            scale = 131;
        break;
        case 1:
            scale = 65.5;
        break;
        case 2:
            scale = 32.8;
        break;
        case 3:
            scale = 16.4;
        break;
    }

        Wire.beginTransmission(ADDR);
        Wire.write(GYRO_ZOUT_H);
        Wire.endTransmission(false);

        Wire.requestFrom(ADDR, 2, true);
        normal = (Wire.read()<<8|Wire.read());

    while(total <= angle){
            Wire.beginTransmission(ADDR);
            Wire.write(GYRO_ZOUT_H);
            Wire.endTransmission(false);

            Wire.requestFrom(ADDR, 2, true);
            value = Wire.read()<<8|Wire.read();
            if(value<0)value*=-1;
            total+=(value/scale)*0.01;
            delay(8);

    }

}

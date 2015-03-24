/* 
 * File:   IMU.cpp
 * Author: Robin
 * 
 * Created on 11 March 2015, 13:07
 */
#include <math.h>
#include <stdio.h>      /* printf */
#include <stdlib.h> 

#include "IMU.h"
#include "parallel.h"

IMU::IMU() {
}

IMU::IMU(const IMU& orig) {
}

IMU::~IMU() {
}



void IMU::update(Parallel::ParallelData sensorsData)
{   
  float pitchAcc, rollAcc;

  // Integrate the gyroscope data -> int(angularSpeed) = angle
  pitch += ((float)(sensorsData.gyroX)*2000.0f/32768.0f) * 0.005; // Angle around the X-axis
  roll -= ((float)(sensorsData.gyroY)*2000.0f/32768.0f) * 0.005; // Angle around the Y-axis

  // Compensate for drift with accelerometer data if no vibration
  // Weight for accelerometer info (<0.75G = 0.0, 1G = 1.0 , >1.25G = 0.0)
  int forceMagnitudeApprox = abs(sensorsData.accelX) + abs(sensorsData.accelY) + abs(sensorsData.accelZ);


  if (forceMagnitudeApprox > 6144 && forceMagnitudeApprox < 10240)
  {
    // Turning around the X axis results in a vector on the Y-axis
    pitchAcc = atan2((float)sensorsData.accelY, (float)sensorsData.accelZ) * 180 / M_PI;
    pitch = pitch * 0.98 + pitchAcc * 0.02;

    // Turning around the Y axis results in a vector on the X-axis
    rollAcc = atan2((float)sensorsData.accelX, (float)sensorsData.accelZ) * 180 / M_PI;
    roll = roll * 0.98 + rollAcc * 0.02;
  }
    
 //std::cout<<pitch<<" "<<roll<<" "<<std::endl;   
}
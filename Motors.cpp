#include "Motors.h"
#include <iostream>
/** Default constructor, uses default I2C address.
 * @see MPU6050_DEFAULT_ADDRESS
 */
Motors::Motors() {
    devAddr = MOTORS_DEFAULT_ADDRESS;
}





/** Get raw 6-axis motion sensor readings (accel/gyro).
 * Retrieves all currently available motion sensor values.
 * @param ax 16-bit signed integer container for accelerometer X-axis value
 * @param ay 16-bit signed integer container for accelerometer Y-axis value
 * @param az 16-bit signed integer container for accelerometer Z-axis value
 * @param gx 16-bit signed integer container for gyroscope X-axis value
 * @param gy 16-bit signed integer container for gyroscope Y-axis value
 * @param gz 16-bit signed integer container for gyroscope Z-axis value
 * @see getAcceleration()
 * @see getRotation()
 * @see MPU6050_RA_ACCEL_XOUT_H
 */
void Motors::setMotors(int mot0_, int mot1_, int mot2_, int mot3_) {
    
    mot0 = mot0_;
    mot1 = mot1_;
    mot2 = mot2_;
    mot3 = mot3_;
    
        buffer[0] = (uint8_t)(mot0>>8) ;
        buffer[1] = (uint8_t)mot0;
        buffer[2] = (uint8_t)(mot1>>8);
        buffer[3] = (uint8_t)mot1;
        buffer[4] = (uint8_t)(mot2>>8);
        buffer[5] = (uint8_t)mot2;
        buffer[6] = (uint8_t)(mot3>>8);
        buffer[7] = (uint8_t)mot3;
                
        I2Cdev::writeBytes(devAddr, 0x0B, 8, buffer);
}





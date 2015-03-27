#include "RC.h"
#include <iostream>
/** Default constructor, uses default I2C address.
 * @see MPU6050_DEFAULT_ADDRESS
 */
RC::RC() {
    devAddr = RC_DEFAULT_ADDRESS;
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
void RC::getRC() {
    
    I2Cdev::readBytes(devAddr, 0x00, 14, buffer);
    rc0 = (((int16_t)buffer[0]) << 8) | buffer[1];
    rc1 = (((int16_t)buffer[2]) << 8) | buffer[3];
    rc2 = (((int16_t)buffer[4]) << 8) | buffer[5];
    rc3 = (((int16_t)buffer[6]) << 8) | buffer[7];
    rc4 = (((int16_t)buffer[8]) << 8) | buffer[9];
    /*
    I2Cdev::readByte(0x29, 0x00, &rc0_0);
    I2Cdev::readByte(0x29, 0x01, &rc0_1);
    I2Cdev::readByte(0x29, 0x02, &rc1_0);
    I2Cdev::readByte(0x29, 0x03, &rc1_1);
    I2Cdev::readByte(0x29, 0x04, &rc2_0);
    I2Cdev::readByte(0x29, 0x05, &rc2_1);
    I2Cdev::readByte(0x29, 0x06, &rc3_0);
    I2Cdev::readByte(0x29, 0x07, &rc3_1);
    I2Cdev::readByte(0x29, 0x06, &rc4_0);
    I2Cdev::readByte(0x29, 0x07, &rc4_1);
    
    
    
    rc0 = (((int16_t)rc0_0) << 8) | rc0_1;
    rc1 = (((int16_t)rc1_0) << 8) | rc1_1;
    rc2 = (((int16_t)rc2_0) << 8) | rc2_1;
    rc3 = (((int16_t)rc3_0) << 8) | rc3_1;
    rc4 = (((int16_t)rc4_0) << 8) | rc4_1;
     * 
     * /
    
    /*
    std::cout<<(int)rc0<<" ";   
    //std::cout<<(int)rc0_1<<" ";  
    std::cout<<(int)rc1<<" ";  
    //std::cout<<(int)rc1_1<<" ";  
    std::cout<<(int)rc2<<" ";  
    //std::cout<<(int)rc2_1<<" ";  
    std::cout<<(int)rc3<<" "<<std::endl;  
    //std::cout<<(int)rc3_1<<" "<<std::endl;  
     * */
    
}







#ifndef _MOTORS_H_
#define _MOTORS_H_

#include "I2Cdev.h"
#include <math.h>
#include <unistd.h>
#include <string>

#define MOTORS_DEFAULT_ADDRESS     0x29

class Motors {
    public:
        
        Motors();
        
        void setMotors(int mot0, int mot1, int mot2, int mot3);
        
       
    private:
        uint8_t devAddr;
        uint8_t buffer[14];
        
        int mot0;
        int mot1;
        int mot2;
        int mot3;
};

#endif /* _MOTORS_H_ */


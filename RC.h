

#ifndef _RC_H_
#define _RC_H_

#include "I2Cdev.h"
#include <math.h>
#include <unistd.h>
#include <string>

#define RC_DEFAULT_ADDRESS     0x29

class RC {
    public:
        RC();
        
        void update(){getRC();}
        
        int get_rc0(){return rc0;}
        int get_rc1(){return rc1;}
        int get_rc2(){return rc2;}
        int get_rc3(){return rc3;}
        int get_rc4(){return rc4;}
        
       
    private:
        uint8_t devAddr;
        uint8_t buffer[14];
        
        uint16_t rc0;
        uint16_t rc1;
        uint16_t rc2;
        uint16_t rc3;
        uint16_t rc4;

        
        void getRC();
};

#endif /* _RC_H_ */


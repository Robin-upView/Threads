/* 
 * File:   IMU.h
 * Author: Robin
 *
 * Created on 11 March 2015, 13:07
 */

#ifndef IMU_H
#define	IMU_H

#include "parallel.h"

class IMU {
public:
    IMU();
    IMU(const IMU& orig);
    virtual ~IMU();
    
    void update(Parallel::ParallelData sensorsData);
    float getPitch(){return pitch;}
    float getRoll(){return roll;}

private:

    float pitch;
    float roll;
    
    
};

#endif	/* IMU_H */


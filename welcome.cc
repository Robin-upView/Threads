#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

#include <termios.h>
#include <unistd.h>

#include <sys/time.h>

#include <iostream>

//#include "parallel.h"
#include "IMU.h"
#include "MPU6050.h"
#include "RC.h"

using namespace std;

const int UPDATETIMEUS = 10000;
const int MINSPARETIME = 2000;
int loopTimeUs_;
    
void nanoWait(int secs, int nsecs);

int main()
{
    MPU6050 accelgyro;
    RC rc;
    
    IMU imu;

    //Parallel parallel;
    //parallel.open();
    //parallel.start();

    
    while(true)
    {
        // time loop started
        timeval loopStart;
        gettimeofday(&loopStart, NULL);
        
        accelgyro.update();
        rc.update();
        
        imu.update(accelgyro.get_ax(),accelgyro.get_ay(),accelgyro.get_az(),accelgyro.get_gx(),accelgyro.get_gy(),accelgyro.get_gz());
        
        uint8_t buf[8];
        buf[0] = (uint8_t)(rc.get_rc0()>>8) ;
        buf[1] = (uint8_t)rc.get_rc0();
        buf[2] = (uint8_t)(rc.get_rc1()>>8);
        buf[3] = (uint8_t)rc.get_rc1();
        buf[4] = (uint8_t)(rc.get_rc2()>>8);
        buf[5] = (uint8_t)rc.get_rc2();
        buf[6] = (uint8_t)(rc.get_rc3()>>8);
        buf[7] = (uint8_t)rc.get_rc3();
                
        I2Cdev::writeBytes(0x29, 0x0B, 8, buf);
        
        //cout << accelgyro.get_ax()<<" "<<accelgyro.get_ay()<<" "<<accelgyro.get_az()<<" "<<accelgyro.get_gx()<<" "<<accelgyro.get_gy()<<" "<<accelgyro.get_gz()<<endl;
        cout << imu.getPitch() << " " << imu.getRoll() << " ";
        cout << rc.get_rc0()<<" "<<rc.get_rc1()<<" "<<rc.get_rc2()<<" "<<rc.get_rc3()<<" "<<endl;
        cout << loopTimeUs_<<endl;
        
        
        //do the work
        //Parallel::ParallelData microcontroler_data;
        //parallel.getParallelData(microcontroler_data);
        
        //std::cout<<microcontroler_data.gyroX<<" "<<microcontroler_data.gyroY<<" "<<microcontroler_data.gyroZ<<" "<<microcontroler_data.accelX<<" "<<microcontroler_data.accelY<<" "<<microcontroler_data.accelZ<<std::endl;
        //std::cout<<microcontroler_data.motor1<<" "<<microcontroler_data.motor2<<" "<<microcontroler_data.motor3<<" "<<microcontroler_data.motor4<<" "<<i<<std::endl;
        
        
        
        
        

        
        
        
        
        
        
        
        
        
        // finished all the work, whats the time now?
        timeval loopEnd;
        gettimeofday(&loopEnd, NULL);

        // how long did the work take
        loopTimeUs_ = (loopEnd.tv_sec - loopStart.tv_sec)*1000000 + (loopEnd.tv_usec - loopStart.tv_usec);

        // how much spare time have we
        int spareTime = UPDATETIMEUS - loopTimeUs_;

        // have we overrun?
        if (spareTime < MINSPARETIME || loopTimeUs_ < 0)
        {
            // into our spare time buffer, give other processes some time at the expense of realtimeness!
            spareTime = MINSPARETIME;
        }
        
        // wait to make the loop last for UPDATETIMEUS
        // and let other stuff run
        nanoWait(0, spareTime*1000);
    }
    

    return 0;

    
}


// timing utility
void nanoWait(int secs, int nsecs)
{
    timespec waitTime;
    timespec remTime;
    waitTime.tv_sec = secs;
    waitTime.tv_nsec = nsecs;
    nanosleep(&waitTime, &remTime);
}
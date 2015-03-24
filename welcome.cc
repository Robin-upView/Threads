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

#include "parallel.h"
#include "IMU.h"

const int UPDATETIMEUS = 10000;
const int MINSPARETIME = 2000;
int loopTimeUs_;
    
void nanoWait(int secs, int nsecs);

int main()
{
    
    Parallel parallel;
    parallel.open();
    parallel.start();
    
    
    IMU imu;
    
    //usleep(10000000);
    int i = 2000;
    
    while(true)
    {
        // time loop started
        timeval loopStart;
        gettimeofday(&loopStart, NULL);
        
        
        
        
        
        
        
        
        //do the work
        Parallel::ParallelData microcontroler_data;
        parallel.getParallelData(microcontroler_data);
        
        //std::cout<<microcontroler_data.gyroX<<" "<<microcontroler_data.gyroY<<" "<<microcontroler_data.gyroZ<<" "<<microcontroler_data.accelX<<" "<<microcontroler_data.accelY<<" "<<microcontroler_data.accelZ<<std::endl;
        //std::cout<<microcontroler_data.motor1<<" "<<microcontroler_data.motor2<<" "<<microcontroler_data.motor3<<" "<<microcontroler_data.motor4<<" "<<i<<std::endl;
        
        
        imu.update(microcontroler_data);
        
        
        i++;
        
        parallel.sendMotors(i,i,i,i);
        
        if(i==2100)
        {
            i = 2000;
        }
        
        
        
        
        
        
        
        
        
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
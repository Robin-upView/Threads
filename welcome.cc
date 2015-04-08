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
#include "Motors.h"

#ifdef	__cplusplus
extern "C" {
#endif

#include "robin_control_law.h"


#ifdef	__cplusplus
}
#endif

using namespace std;

const int UPDATETIMEUS = 10000;
const int MINSPARETIME = 2000;
int loopTimeUs_;
    
void nanoWait(int secs, int nsecs);

int main()
{
    MPU6050 accelgyro;
    RC rc;
    Motors motors;
    
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
        
        
        //control law here
        robin_control_law_U.rx[0]=rc.get_rc0();
        robin_control_law_U.rx[1]=rc.get_rc1();
        robin_control_law_U.rx[2]=rc.get_rc2();
        robin_control_law_U.rx[3]=rc.get_rc3();
        
        robin_control_law_U.attitude[0]=imu.getPitch();
        robin_control_law_U.attitude[1]=imu.getRoll();
        
        robin_control_law_step();
        
        cout<<robin_control_law_Y.log_h[0];
                cout<<" ";
        cout<<robin_control_law_Y.log_h[1];
                cout<<" ";
        cout<<robin_control_law_Y.log_h[2];
                cout<<" ";
        cout<<robin_control_law_Y.log_h[3];
                cout<<" ";
        cout<<robin_control_law_Y.log_h[4];
                cout<<" ";
        cout<<robin_control_law_Y.log_h[5];
                cout<<endl;
        
        motors.setMotors(robin_control_law_Y.motors[0],robin_control_law_Y.motors[1],robin_control_law_Y.motors[2],robin_control_law_Y.motors[3]);
        
        

        
        //cout << accelgyro.get_ax()<<" "<<accelgyro.get_ay()<<" "<<accelgyro.get_az()<<" "<<accelgyro.get_gx()<<" "<<accelgyro.get_gy()<<" "<<accelgyro.get_gz()<<endl;
        //cout << imu.getPitch() << " " << imu.getRoll() << " ";
        //cout << rc.get_rc0()<<" "<<rc.get_rc1()<<" "<<rc.get_rc2()<<" "<<rc.get_rc3()<<" "<<endl;
        //cout << loopTimeUs_<<endl;
        
        
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
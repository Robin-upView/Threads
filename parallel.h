/* 
 * File:   parallel.h
 * Author: Robin
 *
 * Created on 17 décembre 2014, 23:42
 */

#ifndef PARALLEL_H
#define	PARALLEL_H

extern "C"
 {
    #include <pthread.h>
    #include <unistd.h>
 }

#include <iostream>

class Parallel
{
public:
    void start();
    Parallel();
    void open();
    
    struct ParallelData
    {
        int accelX;
        int accelY;
        int accelZ;
        int gyroX;
        int gyroY;
        int gyroZ;
        int motor1;
        int motor2;
        int motor3;
        int motor4;
        int rc0;
        int rc1;
        int rc2;
        int rc3;
        int rc4;
        float G_Dt;
    };
    
    void getParallelData(ParallelData& parallelData);
    
    void sendMotors(int, int, int, int);
    
private:
    pthread_t thread;
    
    static void * staticEntryPoint(void * c);
    void entryPoint();
    
    int uart0_filestream;
    
    ParallelData data_;
    
    pthread_mutex_t mutex_;

};



#endif	/* PARALLEL_H */


/* 
 * File:   Parallel.cpp
 * Author: Robin
 * 
 * Created on 11 March 2015, 11:18
 */

#include "parallel.h"
#include <fcntl.h>			//Used for UART
#include <termios.h>
#include <vector>
#include <sstream>
#include <unistd.h>

Parallel::Parallel():uart0_filestream(-1)
{
     pthread_mutex_init(&mutex_, NULL);
}

void Parallel::start()
{
    pthread_create(&thread, NULL, Parallel::staticEntryPoint, this);
}

void * Parallel::staticEntryPoint(void * c)
{
    ((Parallel *) c)->entryPoint();
    return NULL;
}

void Parallel::entryPoint()
{
int index=0;
    char lineBuf[128];
    char receive[50] = {0};
    
    while(1)
    {
        int ret = read(uart0_filestream, lineBuf, 1);
        
        if(ret>0)
        {
            receive[index] = lineBuf[0];
            index++;
        }
        
        if(lineBuf[0] == '\n')
        {
            receive[index]='\0';
            index = 0;
            //printf("%s",receive);
            
            std::string str(receive);

            std::vector<float> vect;

            std::stringstream ss(str);

            float i;

            while (ss >> i)
            {
                vect.push_back(i);

                if (ss.peek() == ',')
                ss.ignore();
            }

            if(vect.size()==16)
            {   
                /*
                for(int i=0;i<vect.size();i++)
                {
                    std::cout<<vect[i]<<" ";
                }
                std::cout<<std::endl;
                */
                
                pthread_mutex_lock(&mutex_);
                data_.accelX = vect[0];
                data_.accelY = vect[1];
                data_.accelZ = vect[2];
                data_.gyroX = vect[3];
                data_.gyroY = vect[4];
                data_.gyroZ = vect[5];
                data_.motor1 = vect[6];
                data_.motor2 = vect[7];
                data_.motor3 = vect[8];
                data_.motor4 = vect[9];
                data_.rc0 = vect[10];
                data_.rc1 = vect[11];
                data_.rc2 = vect[12];
                data_.rc3 = vect[13];
                data_.rc4 = vect[14];
                data_.G_Dt = vect[15];
                pthread_mutex_unlock(&mutex_);
                
                std::cout<<data_.gyroX<<" "<<data_.gyroY<<" "<<data_.gyroZ<<" "<<data_.accelX<<" "<<data_.accelY<<" "<<data_.accelZ<<" "<<data_.motor1<<" "<<data_.motor2<<" "<<data_.motor3<<" "<<data_.motor4<<" "<<data_.rc0 << " " << data_.rc1 << " " << data_.rc2 << " " << data_.rc3 << " " << data_.rc4 << " " <<   data_.G_Dt<<std::endl;
            
                 
                 } 
        } 
    }

}

void Parallel::open()
{
    uart0_filestream = ::open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode
    if (uart0_filestream == -1)
    {
        //ERROR - CAN'T OPEN SERIAL PORT
        std::cout<<"Error - Unable to open UART.  Ensure it is not in use by another application"<<std::endl;
    }

    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;		//<Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);
}

void Parallel::getParallelData(ParallelData& parallelData)
{
    pthread_mutex_lock(&mutex_);
    parallelData = data_;
    pthread_mutex_unlock(&mutex_);
}

void Parallel::sendMotors(int motor1, int motor2, int motor3, int motor4)
{

    // form the control string
    std::ostringstream os;
   
        os << motor1<<","<<motor2<<","<<motor3<<","<<motor4;
    os << '\n';
    
    // send it off
    write(uart0_filestream, os.str().c_str(), os.str().size());
    // @XXX hardwire to stdio
    //write(STDOUT_FILENO, os.str().c_str(), os.str().size());





}
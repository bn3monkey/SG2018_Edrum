#ifndef __SERIAL__
#define __SERIAL__

#include <cstdio>
#include <cstdlib>

#include <string.h> //for errno
#include <errno.h> //error output

#include <wiringPi.h>
#include <wiringSerial.h>

#include <thread>

#include "NoteData.hpp"

// flag to iterate serial flag
extern bool continue_flag;

//The buffer object
class Serial_buffer
{
private:
    char* buffer;
    int size;
    int top;

public:
    Serial_buffer(int _size = 500) : size(_size)
    {
        buffer = new char[size];
        this->top = 0;
    }
    ~Serial_buffer()
    {
        if(buffer != NULL)
            delete buffer;
    }
    inline void push(char value)
    {
        if(this->top == size)
        {
            fprintf(stderr, "buffer full!\n");
            return;
        }
        buffer[(this->top)++] = value;
    }
    inline void finish()
    {
        buffer[--(this->top)] = '\0';
    }

    inline int gettop() {return this->top;}
    inline char* data() {return this->buffer;}

    char& operator[](int index)
    {
        return buffer[index];
    }
    char operator[](int index) const
    {
        return buffer[index];
    }
    inline void refresh()
    {
        this->top = 0;
    }
};

class Serial_io
{
    // the instance of serial buffer
    Serial_buffer* buff;
    // the file description of serial device
    int serial_fd;

    // the thread to excute thread_readSerial
    std::thread pthread;
    // the method to read string from serial port
    static void thread_readSerial(int fd);

    public:
    Serial_io()
    {
    	continue_flag = true;
        // make buffer
        buff = new Serial_buffer(100);
        // open serial port (it can be only activated in linux OS)
        if ((serial_fd = serialOpen ("/dev/ttyACM0", 115200)) < 0)  // 두번째 인자값이 보레이트 설정
        {
            fprintf (stderr, "Unable to open serial device : %s\n",strerror(errno)) ;                   
            exit(-1);
        }
        // activate wiring Pi library.
        if (wiringPiSetup() == -1)
        { 
            fprintf (stdout, "Unable to start wiringPi : %s\n", strerror(errno)) ;
            exit(-1);
        }
        // flush data in serial port
	    serialFlush(serial_fd);
        // kick thread to read serial
        pthread = std::thread(thread_readSerial, serial_fd);
    }
    ~Serial_io()
    {
        // end thread
	    continue_flag = false;
        // join thread
        pthread.join();
        // flush data in serial port
	    serialFlush(serial_fd);
        // close serial port
	    serialClose(serial_fd);
        // delete buffer
        if(buff != NULL)
            delete buff;
    }


    // read string from serial port and store in serial buffer
    int readSerial();
    // make pnote from serial buffer
    int setSerial(NoteData* pnote);
    // Send one byte character to Serial
    int putSerial(char buf); 
    // send string to serial
    int writeSerial(char* buf);
    // send note to serial
    int writeNote(NoteData note);
    // clean serial buffer
    int cleanSerial();
};

#endif

#include "serial.hpp"
#include <cstring>
#include <wiringPi.h>
#include <wiringSerial.h>

int Serial_io::getSerial(int fd)
{
    char ch;
    buff->refresh();
    //serialGetchar blocking 함수.. character 받을 떄까지 대기한다. 
    do
    {
        ch = serialGetchar(fd);
        switch(ch)
        {
            case -1 : break;
            default: buff->push(ch);
        }
    }
    while(ch == '\0');
}

int Serial_io::setSerial(char* tempbuf)
{
    memcpy(tempbuf, buff->data, buff->gettop());
}
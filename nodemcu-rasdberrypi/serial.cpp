#include "serial.hpp"
#include <cstring>


int Serial_io::getSerial()
{
    char ch;
    buff->refresh();
    //serialGetchar blocking 함수.. character 받을 떄까지 대기한다. 
    do
    {
        if(serialDataAvail(serial_fd))
        {
            ch = serialGetchar(serial_fd);
            buff->push(ch);
        }
    }
    while(ch == '\0');
    return 1;
}

int Serial_io::setSerial(char* tempbuf)
{
    memcpy(tempbuf, buff->data(), buff->gettop());
    return 1;
}
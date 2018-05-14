#include "serial.hpp"

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
            //printf("%c(%d)",ch,ch);
        }
    }
    while(ch != '.');
    buff->finish();
    return 1;
}

int Serial_io::setSerial(char* tempbuf)
{
    memcpy(tempbuf, buff->data(), buff->gettop());
    //출력했으니 버퍼를 비워줌.
    buff->refresh();
    return 1;
}
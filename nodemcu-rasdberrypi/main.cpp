#include "serial.hpp"
#include <cstdio>

typedef struct _note
{
    // 시작 시간으로부터 찍힌 노트의 시간 (milli초 단위)
    long long int msec;
    // 연주한 악기의 종류
    int drum;
    // 악기 친 세기
    int power;
} note;


int main()
{

    Serial_io* io = new Serial_io();
    char temp[100];
    while(true)
    {
        io->getSerial();
        io->setSerial(temp);
        printf("%s",temp);
    }
    delete io;
    return 0;
}
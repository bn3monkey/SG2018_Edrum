#include "serial.hpp"
#include "file.h"
#include <cstdio>

int main()
{

    Serial_io* io = new Serial_io();
    printf("Start Program!\n");
    char temp[1000];
    while(continue_flag)
    {
        io->getSerial();
        io->setSerial(temp);
        printf("%s\n",temp);
	if(!makefile(temp))
		continue_flag = false;
    }
    printf("End Program!\n");
    delete io;
    return 0;
}

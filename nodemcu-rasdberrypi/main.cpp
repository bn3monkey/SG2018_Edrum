#include "serial.hpp"
#include "file.h"
#include <cstdio>
#include <cstdlib>
int main()
{

    Serial_io* io = new Serial_io();
    printf("Start Program!\n");
    char temp[1000];
    char cmd[100];
    char filename[50];
    while(continue_flag)
    {
        io->getSerial();
        io->setSerial(temp);
        printf("%s\n",temp);
	    if(!makefile(temp,filename))
	    {
	    	sprintf(cmd, "python3 send.py %s", filename);
		    system(cmd);
	    }		
		//continue_flag = false;
    }
    printf("End Program!\n");
    delete io;
    return 0;
}

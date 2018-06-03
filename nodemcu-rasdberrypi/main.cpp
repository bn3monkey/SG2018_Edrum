#include "serial.hpp"
#include "play.hpp"

#include <cstdio>
#include <cstdlib>

void logSerial(note pnote)
{
    switch(pnote.drum)
    {
        case cmd_idle : printf("IDLE "); break;
        case cmd_recordstart : printf("RECORD_START "); break;
        case cmd_recordend : printf("RECORD_END "); break;
        case cmd_playstart : printf("PLAY_START "); break;
        case cmd_playend : printf("PLAY_END "); break;
        case cmd_fileup : printf("FILE_UP "); break;
        case cmd_filedown : printf("FILE_DOWN "); break;

        case cmd_drum1 : printf("DRUM1 "); break;
        case cmd_drum2 : printf("DRUM2 "); break;

        case cmd_led1 : printf("LED1 "); break;
        case cmd_led2 : printf("LED2 "); break;
    }
    printf("%d %llu", pnote.power, pnote.msec);
}

int main()
{

    Serial_io* io = new Serial_io();
    printf("Start Program!\n");
    note temp;
    char cmd[100];
    char filename[50];
    while(continue_flag)
    {
        io->readSerial();
        io->setSerial(temp);
        logSerial(temp);

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

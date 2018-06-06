#include "serial.hpp"
#include "play.hpp"

#include <cstdio>
#include <cstdlib>

#include "serial_protocol.h"

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
        case cmd_downloadreq : printf("DOWNLOAD_REQUSET "); break;
        case cmd_downloadres : printf("DOWNLOAD_RESPOND "); break;
        case cmd_refreshreq : printf("REFRESH_REQUSET "); break;
        case cmd_refreshres : printf("REFRESH_RESPOND "); break;
        
	    case cmd_drum1 : printf("DRUM1 "); break;
        case cmd_drum2 : printf("DRUM2 "); break;

        case cmd_led1 : printf("LED1 "); break;
        case cmd_led2 : printf("LED2 "); break;
    }
    printf("%d %llu\n", pnote.power, pnote.msec);
}



char cmd[512];

int main()
{

    Serial_io* io = new Serial_io();
    Serial_play* play = new Serial_play();
    printf("Start Program!\n");
    note temp;
    char filename[50];
    while(continue_flag)
    {
        io->readSerial();
        io->setSerial(&temp);
        logSerial(temp);
	
        switch(play->play(&temp))
        {
            case cmd_downloadreq :
		        printf("please download\n");                
                io->writeNote( play->getnote(temp.power));
                io->writeNote( play->getnote(temp.power));
                sprintf(cmd, "%d %d %d\n",cmd_downloadsuc,-1,0);
                io->writeSerial(cmd);

                break;
            
            case cmd_refreshreq :
		        printf("please refresh\n");
                io->writeNote( play->getnote(temp.power));
                sprintf(cmd, "%d %d %d\n",cmd_refreshsuc,-1,0);
                io->writeSerial(cmd);

                break;
        }
	
	    if(!makefile(&temp,filename))
	    {
            io->cleanSerial();
	    	sprintf(cmd, "python3 send.py %s", filename);
		    system(cmd);
	    }
        		
		//continue_flag = false;
    }
    printf("End Program!\n");
    delete io;
    delete play;
    return 0;
}

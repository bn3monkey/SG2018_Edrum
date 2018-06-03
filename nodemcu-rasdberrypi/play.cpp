#include "play.hpp"
#include "serial_protocol.h"
void Serial_play::play(note* temp, char* buf)
{
    if(!playing && temp->drum == cmd_playstart)
    {
        // nono
    }
    else if(!playing && temp->drum == cmd_fileup)
    {
        this->fileup(buf);
    }
    else if(!playing && temp->drum == cmd_filedown)
    {
         this->filedown(buf);
    }
    else if(playing && temp->drum == cmd_playend)
    {

    }
}

void Serial_play::fileup(char* buf)
{
    playable = makefilename(++current_filenum, current_filename);
    if(playable)
    {
        printf("File can be opend : %s\n", current_filename);
        sprintf(buf, "OK");
    }
    else
    {
        printf("File cannot be opend : %s\n", current_filename);
        sprintf(buf, "NO");
    }
}

void Serial_play::filedown(char* buf)
{
    if(--current_filenum < 0)
        current_filenum = 0;
    playable = makefilename(--current_filenum, current_filename);
    if(playable)
    {
        printf("File can be opend : %s\n", current_filename);
        sprintf(buf, "OK");
    }
    else
    {
        printf("File cannot be opend : %s\n", current_filename);
        sprintf(buf, "NO");
    }
}
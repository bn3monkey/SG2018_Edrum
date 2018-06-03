#include "play.hpp"

void Serial_play::play(note* temp, char* buf)
{

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
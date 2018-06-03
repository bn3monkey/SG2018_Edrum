#include "play.hpp"

void Serial_play::play(char* temp, char* buf)
{
    char drum[10];
    int power;
	unsigned long long int msec;
	sscanf(temp,"%s %d %llu",drum,&power,&msec);

    if(!playing && strcmp(drum,"record_start")==0)
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
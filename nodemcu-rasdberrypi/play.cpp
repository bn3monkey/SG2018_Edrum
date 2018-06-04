#include "play.hpp"
#include "serial_protocol.h"

void Serial_play::deallocation()
{
    if(drum[0] != NULL)
        delete drum[0];
    if(drum[1] != NULL)
        delete drum[1];
}

int Serial_play::play(note* temp)
{
    if(!playing && temp->drum == cmd_playstart)
    {
        file_initialize();
        return cmd_playstart;
    }
    else if(!playing && temp->drum == cmd_fileup)
    {
        this->fileup();
        return cmd_fileup;
    }
    else if(!playing && temp->drum == cmd_filedown)
    {
         this->filedown();
         return cmd_filedown;
    }
    else if(playing && temp->drum == cmd_playend)
    {
        return cmd_playend;
    }
    return cmd_idle;
}

void Serial_play::file_initialize()
{
    char temp[10];
    int num;

    if(!playable)
    {
        printf("File cannot be opend : %s\n", current_filename);
        return;
    }

    fp = fopen(current_filename, "r");

    fscanf(fp,"%d ",&num);
	
    //첫번쨰 드럼
    fscanf(fp,"%s %d ",temp,&(drum_cnt[0]));
    drum[0] = new note[drum_cnt[0]];
    if(drum[0] == NULL)
    {
        fprintf(stderr, "PLAY DRUM1 ALLOCATION ERROR!\n");
        return;
    }
    for(int i=0;i<drum_cnt[0];i++)
    {
        drum[0][i].drum = cmd_led1;
        fscanf(fp,"%d %llu ",&(drum[0][i].power),&(drum[0][i].msec));
    }
    drum_index[0] = 0;

    printf("drum1 file : %d\n",drum_cnt[0]);
    for(int i=0;i<drum_cnt[0];i++)
        printf("%d %d %llu\n",drum[0][i].drum, drum[0][i].power, drum[0][i].msec);

    //두번쨰 드럼
    fscanf(fp,"%s %d ",temp,&(drum_cnt[1]));
    drum[1] = new note[drum_cnt[1]];
    if(drum[1] == NULL)
    {
        fprintf(stderr, "PLAY DRUM2 ALLOCATION ERROR!\n");
        return;
    }
    for(int i=0;i<drum_cnt[1];i++)
    {
       drum[1][i].drum = cmd_led2;
       fscanf(fp,"%d %llu ",&(drum[1][i].power),&(drum[1][i].msec));
    }
    drum_index[1] = 0;

    printf("drum2 file : %d\n",drum_cnt[1]);
    for(int i=0;i<drum_cnt[1];i++)
        printf("%d %d %llu\n",drum[1][i].drum, drum[1][i].power, drum[1][i].msec);

    fclose(fp);
}

void Serial_play::fileup()
{
    playable = makefilename(++current_filenum, current_filename);
    if(playable)
    {
        printf("File can be opend : %s\n", current_filename);
    }
    else
    {
        printf("File cannot be opend : %s\n", current_filename);
    }
}

void Serial_play::filedown()
{
    if(--current_filenum < 0)
        current_filenum = 0;
    playable = makefilename(current_filenum, current_filename);
    if(playable)
    {
        printf("File can be opend : %s\n", current_filename);
    }
    else
    {
        printf("File cannot be opend : %s\n", current_filename);
    }
}

note Serial_play::getnote(int number)
{
    int index = this->drum_index[number];
    if(index < this->drum_cnt[number])
    {
        this->drum_index[number]++;
        return this->drum[number][index];
    }
    else
    {
        note temp;
        temp.drum = 0x100*(number+1);
        temp.power = -1;
        temp.msec = 0;
        return temp;
    }
}

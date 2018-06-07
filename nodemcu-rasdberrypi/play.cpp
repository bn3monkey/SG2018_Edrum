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
	    playing =  true;
        score = _score();
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
	    playing = false;
        return cmd_playend;
    }
    else if(playing && temp->drum == cmd_downloadreq)
    {
        return cmd_downloadreq;
    }
    else if(playing && temp->drum == cmd_refreshreq)
    {
        return cmd_refreshreq;
    }
    else if(playing && temp->drum == cmd_scoring)
    {
        score_in(*temp);
        return cmd_scoring;
    }
    else if(playing && temp->drum == cmd_endscore)
    {
        print_endscore();
        return cmd_endscore;
    }
    return cmd_idle;
}

void Serial_play::file_initialize()
{
    char temp[10];

    if(!playable)
    {
        printf("File cannot be opend : %s\n", current_filename);
        return;
    }

    fp = fopen(current_filename, "r");

    fscanf(fp,"%d ",&drum_num);
	
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

void Serial_play::score_in(note temp)
{
    switch(temp.power)
    {
        case excellent : this->score.excellent++; this->score.whole_score += 6;
        case nice: this->score.nice++; this->score.whole_score += 3;
        case good: this->score.good++; this->score.whole_score += 1;
        case bad: this->score.bad++; this->score.whole_score += 0;
        case verybad: this->score.verybad++; this->score.whole_score += -2;
    }
}
void Serial_play::print_endscore()
{
    int basis = 0;
    int whole_score = this->score.whole_score;
    for(int i=0;i<this->drum_num;i++)
    {
        basis += 6 * drum_cnt[i];
    }
    printf("\n----------end score----------\n");
    printf("very bad : %d\n", this->score.verybad);
    printf("bad : %d\n", this->score.bad);
    printf("good : %d\n", this->score.good);
    printf("nice : %d\n", this->score.nice);
    printf("excellent : %d\n", this->score.excellent);

    if(basis * 0.95 <= whole_score)
        printf("SSS\n");
    else if(basis * 0.9 <= whole_score)
        printf("SS\n");
    else if(basis * 0.85 <= whole_score)
        printf("S\n");
    else if(basis * 0.8 <= whole_score)
        printf("A\n");
    else if(basis * 0.7 <= whole_score)
        printf("B\n");
    else if(basis * 0.5 <= whole_score)
        printf("C\n");
    else if(basis * 0.2 <= whole_score)
        printf("D\n");
    else
        printf("F\n");
    printf("----------end score----------\n");
}
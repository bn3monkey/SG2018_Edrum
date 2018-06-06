#include "note.hpp"
#include <string.h>

bool note_queue::download(int trial)
{
    static char buffer[50];
    note temp;

    memset(buffer, 0, 50);
    while(Serial.readBytesUntil('\n', buffer, 50)==0 && refresh--);
    if(refresh <= 0)
        return false;
    sscanf(buffer, "%d %d %lu" ,&(temp.drum), &(temp.power), &(temp.time));
    this->now = temp;
    
    memset(buffer, 0, 50);
    if(Serial.readBytesUntil('\n', buffer, 50)==0)
        return false;
    sscanf(buffer, "%d %d %lu" ,&(temp.drum), &(temp.power), &(temp.time));
    this->next = temp;
    
    memset(buffer, 0, 50);
    if(Serial.readBytesUntil('\n', buffer, 50)==0)
        return false;
    sscanf(buffer, "%d %d %lu" ,&(temp.drum), &(temp.power), &(temp.time));
    if(temp.power == -1)
        return true;
    return false;
}

bool note_queue::refresh(int trial)
{
    static char buffer[50];
    note temp;

    memset(buffer, 0, 50);
    while(Serial.readBytesUntil('\n', buffer, 50)==0 && refresh--);
    if(refresh <= 0)
        return false;
    sscanf(buffer, "%d %d %lu" ,&(temp.drum), &(temp.power), &(temp.time));
    
    memset(buffer, 0, 50);
    if(Serial.readBytesUntil('\n', buffer, 50)==0)
        return false;
    sscanf(buffer, "%d %d %lu" ,&(temp.drum), &(temp.power), &(temp.time));
    if(temp.power == -1)
    {
        this->now = this->next;
        this->next = temp;
        return true;
    }
    return false;
}

#define IN_SCORE(score, gap) ((score) - HALF_TIME_INTERVAL <= (gap) && (gap) < (score) + HALF_TIME_INTERVAL)
int note_queue::note_sync(unsigned long elapsed)
{
    unsigned long gap = now.time - elapsed;

    if(gap < passaway)
        return passaway;
    else if(IN_SCORE(excellent, gap))
        return excellent;
    else if(IN_SCORE(nice, gap))
        return nice;
    else if(IN_SCORE(good, gap))
        return good;
    else if(IN_SCORE(bad, gap))
        return bad;
    else
        return verybad;
}


bool note_queue::download_debug()
{
    Serial.println("7 0 0");
    Serial.print( this->now.drum,DEC);
    Serial.write(" ");
    Serial.print( this->now.power,DEC);
    Serial.write(" ");
    Serial.print(this->now.time,DEC);
    Serial.write("\n");
    Serial.print( this->next.drum,DEC);
    Serial.write(" ");
    Serial.print( this->next.power,DEC);
    Serial.write(" ");
    Serial.print(this->next.time,DEC);
    Serial.write("\n");
    Serial.println("8 0 0");
}

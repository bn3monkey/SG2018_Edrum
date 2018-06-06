#include "note.hpp"
#include <string.h>
#include "serial_protocol.h"

bool note_queue::download(int trial)
{
    static char buffer[50];
    note temp;

    cmd_send(cmd_downloadreq, led_number, 0);
    
    memset(buffer, 0, 50);
    while(Serial.readBytesUntil('\n', buffer, 50)==0 && trial--);
    if(trial <= 0)
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
    if(temp.drum == cmd_downloadsuc && temp.power == -1 && temp.time == 0)
        return true;
    return false;
}

bool note_queue::refresh(int trial)
{
    static char buffer[50];
    note temp, endmsg;

    cmd_send(cmd_refreshreq, led_number, 0);

    memset(buffer, 0, 50);
    while(Serial.readBytesUntil('\n', buffer, 50)==0 && trial--);
    if(trial <= 0)
        return false;
    sscanf(buffer, "%d %d %lu" ,&(temp.drum), &(temp.power), &(temp.time));
    
    memset(buffer, 0, 50);
    if(Serial.readBytesUntil('\n', buffer, 50)==0)
        return false;
    sscanf(buffer, "%d %d %lu" ,&(endmsg.drum), &(endmsg.power), &(endmsg.time));
    
    this->now = this->next;
    if(endmsg.drum == cmd_refreshsuc && endmsg.power == -1 && endmsg.time == 0)
    {
        this->next = temp;
        return true;
    }
    this->next.time = this->next.time += 3000;
    return false;
}
bool note_queue::finish()
{
  if(this->now.drum == led_number && this->now.power == -1)
    return true;
   return false;
}
#define IN_SCORE(score, gap) ((score) - HALF_TIME_INTERVAL <= (gap) && (gap) < (score) + HALF_TIME_INTERVAL)
int note_queue::note_sync(unsigned long elapsed)
{
    int gap;
    
    if(now.time > elapsed)
      gap = (int)(now.time - elapsed);
    else
      gap = -(int)(elapsed - now.time);

    //Serial.println(gap,DEC);
    
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
    cmd_send(cmd_downloadres, 0, 0);
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
    cmd_send(cmd_downloadres, 0, 0);
}

bool note_queue::refresh_debug()
{
    cmd_send(cmd_refreshres, 0, 0);
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
    cmd_send(cmd_refreshres, 0, 0);
}

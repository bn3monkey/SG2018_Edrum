#include "note.hpp"

bool note_queue::download()
{
    static char buffer[50];
    note temp;
    if( Serial.readBytesUntil('\n', buffer, 50) == 0)
      return false;
      
    sscanf(buffer, "%d %lu" , &(temp.power), &(temp.time));
    if(temp.power == -1)
        return false;

    this->queue[(this->len)++] = temp;
    return true;
}

bool note_queue::download_debug()
{
    Serial.println("--download Debug--");
    for(int i=0;i<len;i++)
    {
        Serial.print( this->queue[i].power,DEC);
        Serial.write(" ");
        Serial.print(this->queue[i].time,DEC);
        Serial.write("\n");
    }
}

note note_queue::front()
{
    if(index<len)
    {
        return this->queue[index];
    }
    else
    {
        note temp;
        temp.power = -1;
        temp.time = 0;
        return temp;
    }
}

bool note_queue::next()
{
    if(this->index < len)
    {
        (this->index)++;
        return true;
    }
    else
    {
        return false;
    }
}

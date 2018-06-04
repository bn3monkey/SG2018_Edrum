#include "note.hpp"

bool note_queue::download()
{
    static char buffer[50];
    note temp;
    if(Serial.readBytesUntil('\n', buffer, 50)==0)
        return false;
    sscanf(buffer, "%d %d %lu" ,&(temp.drum) &(temp.power), &(temp.time));
    if(Serial.readBytesUntil('\n', buffer, 50)==0)
        return false;
    sscanf(buffer, "%d %d %lu" ,&(temp.drum) &(temp.power), &(temp.time));
    if(Serial.readBytesUntil('\n', buffer, 50)==0)
        return false;
    sscanf(buffer, "%d %d %lu" ,&(temp.drum) &(temp.power), &(temp.time));
    if(temp.power == -1)
        return true;
    return false;
}

bool note_queue::refresh()
{
    static char buffer[50];
    note temp;
    if(Serial.readBytesUntil('\n', buffer, 50)==0)
        return false;
    sscanf(buffer, "%d %d %lu" ,&(temp.drum) &(temp.power), &(temp.time));
    if(Serial.readBytesUntil('\n', buffer, 50)==0)
        return false;
    sscanf(buffer, "%d %d %lu" ,&(temp.drum) &(temp.power), &(temp.time));
    if(temp.power == -1)
    {
        this->now = this->next;
        this->next = this->temp;
        return true;
    }
    return false;
}

bool note_queue::download_debug()
{
    Serial.println("--download Debug--");
    Serial.print( this->now.power,DEC);
    Serial.write(" ");
    Serial.print(this->now.time,DEC);
    Serial.write("\n");
    Serial.print( this->next.power,DEC);
    Serial.write(" ");
    Serial.print(this->next.time,DEC);
    Serial.write("\n");
    Serial.println("--download Debug END--");
}

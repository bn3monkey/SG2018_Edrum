#ifndef __NOTE__
#define __NOTE__

#include <arduino.h>

enum NoteProtocol
{
    //drum 0x10 ~ 0x30
    np_drum1 = 0x11,
    np_drum2 = 0x12,

    //switch 0x40 ~ 0x60
    np_up,
    np_down,
    np_right,
    np_left,
    np_ok,
    np_idle,
};

class NoteData
{
public:
    unsigned long time;
    int drum;
    int power;

    NoteData()
    {
        time = 0;
        drum = 0;
        power = 0;
    }
    void send()
    {
        Serial.print(this->time ,DEC);
        Serial.write(" ");
        Serial.print(this->drum, DEC);
        Serial.write(" ");
        Serial.println(this->power, DEC);
    }

    void csv_send()
    {
        Serial.print(this->time, DEC);
        Serial.write(",");
        Serial.print(this->power, DEC);
        Serial.print("\n");
    }
};

#endif
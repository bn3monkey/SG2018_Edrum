#ifndef __DRUM_SIGNAL__
#define __DRUM_SIGNAL__

#include "NoteData.hpp"

const int drum_threshold = 100;

class DrumSignal
{
    int drum;
    int pin;
    int value;

    NoteData prevnote;
    NoteData note;
public:
    DrumSignal(int _pin = 0, int _drum = 0) : pin(_pin), drum(_drum)
    {
       pinMode(pin, INPUT);
    }

    void read(unsigned long elapsed)
    {
         //0. 이전 입력을 처리한다.
        prevnote = note;

        //1. Analog input을 받는다.
        note.power = analogRead(this->pin);
        
        //2. input에 따른 버튼의 종류를 구분한다.
        note.drum = this->drum;

        //3. input이 들어온 시간을 넣는다.
        note.time = elapsed;
    }

    void write()
    {
        if(note.power > drum_threshold)
            note.send();
    }
};

#endif
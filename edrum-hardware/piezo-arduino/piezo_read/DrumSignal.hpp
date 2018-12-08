#ifndef __DRUM_SIGNAL__
#define __DRUM_SIGNAL__

#include "NoteData.hpp"
#include "SignalQueue.hpp"

const int drum_threshold = 10;

class DrumSignal
{
    int pin;

    int pre_value;
    int value;

    int max;

    SignalQueue filter;
    SignalQueue filter2;

    NoteData note;

public:
    DrumSignal(int _pin = 0, int _drum = 0) : pin(_pin)
    {
       pinMode(pin, INPUT);
       //input에 따른 버튼의 종류를 구분한다.
       note.drum = _drum;

       pre_value = 0;
       value = 0;
       max = 0;
    }

    void read(unsigned long elapsed)
    {
        pre_value = value;

        //1. Analog input을 받는다.
        value = analogRead(this->pin);
        // Analog input 값을 필터링한다.
        // moving average filter를 통해 high frequency를 통제한다.
        filter.push(value);
        value = filter.average();
        // 한 번 더 average filter를 적용시켜 local maximum을 제거한다.
        filter2.push(value);
        value = filter2.average();     
         

        //3. input이 들어온 시간을 넣는다.
        note.time = elapsed;
    }

    void write()
    {
        if(value > drum_threshold)
        {
            // 양의 기울기에, 현재 값이 최대값을 초과하면 max값을 기록해준다.
            if(pre_value < value && max < value)
                max = value;
            // 음의 기울기에 값이 최대값에 떨어지면 max 값을 출력한다.
            else if(pre_value > value && max > value)
            {
                note.power = max;
                note.send();
                max = 0;
            }
        }
    }

    void test_write()
    {   
        note.power = value;   
        note.csv_send();
    }
};

#endif
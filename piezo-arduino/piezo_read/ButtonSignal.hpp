#ifndef __BUTTON_SIGNAL__
#define __BUTTON_SIGNAL__

#include "NoteData.hpp"
#include "SignalQueue.hpp"

enum threshold_button
{
    t_up = 6,
    t_down = 2,
    t_left = 10,
    t_right = 0,
    t_ok = 14,
    t_idle = 1020,
};

class ButtonSignal
{
    int pin;
    int value;
    //버튼이 눌렸는지 안 눌렸는지 검사
    bool pressed;
    // 버튼을 눌렀다고, 신호를 보냈는지 안 보냈는지 여부
    bool written;

    SignalQueue queue;
    NoteData note;

public:
    ButtonSignal(int _pin = 0) : pin(_pin)
    {
        pinMode(pin, INPUT);
        pressed = false;
        written = false;
    }

    void read(unsigned long elapsed)
    {
        //1. Analog input을 받는다.
        value = analogRead(this->pin);
        
        //2. 누르지 않았을 경우, queue를 비운다.
        if(value > t_idle)
        {
            queue.clean();
            pressed = false;
            written = false;
        }
        //3. 눌렀을 경우, queue에 값을 넣는다.
        else
        {
            queue.push(value);
            pressed = true;
        }
        //3. input이 들어온 시간을 넣는다.
        note.time = elapsed;
    }

    void write()
    {
        //누르고 있는 상태지만, 아두이노에 신호를 보낸 적이 없고 큐가 꽉 차있다면 신호를 보낸다.
        if(written == false && pressed == true && queue.full())
        {
            written = true;
            note.power = queue.average();
            switch(note.power)
            {
                case t_up : note.drum = np_up; break;
                case t_down : note.drum = np_down;break;
                case t_left : note.drum = np_left;break;
                case t_right : note.drum = np_right;break;
                case t_ok : note.drum = np_ok;break;
                default : note.drum = np_idle; break;
            }
            note.send();
        }
    }

};

#endif

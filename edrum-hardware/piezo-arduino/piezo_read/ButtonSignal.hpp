#ifndef __BUTTON_SIGNAL__
#define __BUTTON_SIGNAL__

#include "NoteData.hpp"
#include "SignalQueue.hpp"

enum threshold_button
{
    t_up = 1,
    t_down = 3,
    t_left = 0,
    t_right = 5,
    t_ok = 7,
    t_idle = 1020,
};

class ButtonSignal
{
    int pin;
    int value;
    // variable to check whether button is pressed or not
    bool pressed;
    // variable to check wheter pressed signal is already sent or not 
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
    // read analog input
    void read(unsigned long elapsed);
    // send note to client
    void write();

};

#endif

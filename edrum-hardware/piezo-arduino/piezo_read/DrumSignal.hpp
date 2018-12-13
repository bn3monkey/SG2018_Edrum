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
       note.drum = _drum;

       pre_value = 0;
       value = 0;
       max = 0;
    }

    // read analog input
    void read(unsigned long elapsed);
    // send signal to client
    void write();
    // send signal in csv form to client 
    void test_write();
};

#endif
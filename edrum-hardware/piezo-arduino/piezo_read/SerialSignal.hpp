#ifndef __SERIAL_SIGNAL__
#define __SERIAL_SIGNAL__

#include <arduino.h>
#include "NoteData.hpp"
class SerialSignal
{
    char buffer;
    NoteData note;

    public:
    SerialSignal()
    {
         Serial.setTimeout(1);
    }
    //read signal from serial
    bool read();
    // write signal to serial
    bool write(unsigned long& clock);
};

#endif
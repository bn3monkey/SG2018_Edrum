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
    bool read();
    bool write(unsigned long& clock);
};

#endif
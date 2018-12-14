 #include "SerialSignal.hpp"
 #include "string.h"
bool SerialSignal::read()
{
    // intialize protocol
    note.drum = np_none;

    // read character form serial port
    buffer = 0;
    buffer = Serial.read();
    if(buffer < 0)
        return false;
    
    // match charecter to command protocol, and set note.drum to command
    if(buffer == nc_clock)
        note.drum = np_cmd_clock;

    return true;
}
bool SerialSignal::write(unsigned long& clock)
{
    switch(note.drum)
    {
        case np_cmd_clock:
            clock = 0;
            note.time = clock;
            note.power = 0;
            note.send();
            break;
    }
}
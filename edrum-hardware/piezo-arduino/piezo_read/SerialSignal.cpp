 #include "SerialSignal.hpp"
 #include "string.h"
bool SerialSignal::read()
{
    //현재 command를 초기화한다.
    note.drum = np_none;

    // serial에서 문자열을 받아온다.
    buffer = 0;
    buffer = Serial.read();
    if(buffer < 0)
        return false;
    
    // 문자열에서 명령을 받아오면, 명령을 배정한다.
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
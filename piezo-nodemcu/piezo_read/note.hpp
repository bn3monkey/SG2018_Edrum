#ifndef __NOTE__
#define __NOTE__

#include <arduino.h>

struct note
{
    int drum;
    int power;
    unsigned long time;
};

class note_queue
{
    int led_number;
    note now;
    note next;
    
    public:
    note_queue(int _led_number) : led_number(_led_number)
    {
        
    }
    ~note_queue()
    {

    }

    // play start 시 note_queue에 있는 정보를 두 개 받는다.
    bool download();
    // playing 시 note_queue에 있는 정보를 하나 받는다.
    bool refresh();

    //제대로 받아왔는지 출력.
    bool download_debug();

};

#endif

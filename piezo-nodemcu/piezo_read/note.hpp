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
    note_queue(int _led_number = 0) : led_number(_led_number)
    {
        next.drum = now.drum = 0x100 * led_number;
        next.power = now.power = -1;
        next.time = now.time = 0;
        
    }
    ~note_queue()
    {

    }

    // play start 시 note_queue에 있는 정보를 두 개 받는다.
    //trial은 라즈베리파이와의 접속시도다.
    bool download(int trial);
    // playing 시 note_queue에 있는 정보를 하나 받는다.
    // trial은 라즈베리파이와의 접속시도다.
    bool refresh(int trial);

    //제대로 받아왔는지 출력.
    bool download_debug();

};

#endif

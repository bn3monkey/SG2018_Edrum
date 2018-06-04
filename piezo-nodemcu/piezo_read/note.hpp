#ifndef __NOTE__
#define __NOTE__

#define MAX_TIME 1000
#include <arduino.h>

struct note
{
    int power;
    unsigned long time;
};

class note_queue
{
    note* queue;
    int index;
    int len;

    public:
    note_queue()
    {
        queue = new note[MAX_TIME];
        if(queue == NULL)
        {
            Serial.println("ALLOC_ERROR 0 0");
        }
        index = 0;
        len = 0;
    }
    ~note_queue()
    {
        if(queue != NULL)
            delete queue;
    }

    // Arduino에서 보낸 Serial을 받아 note queue에 저장한다.
    // note 정보면 true, note 정보가 아니거나, note 정보를 다 받았으면 false를 return한다.
    bool download();

    //제대로 받아왔는지 출력.
    bool download_debug();

    //가장 앞에 있는 note를 가져온다.
    note front();
    // 내부적으로 다음 note를 가리킨다. 다음 note가 없으면 false를 return한다.
    bool next();
};

#endif

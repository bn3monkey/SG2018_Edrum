#include <arduino.h>
#define INPUT_BUF_LENGTH 31
class Drum_signal
{
    int pin;
    int DRUM_THRESHOLD;
    int input_buf[INPUT_BUF_LENGTH];
    int max;
    bool sensing;

public:
    Drum_signal(int _pin = 0, int _DRUM_THRESHOLD = 0) : pin(_pin),  DRUM_THRESHOLD(_DRUM_THRESHOLD) 
    {
       pinMode(pin, INPUT);
        for(int i=0;i<INPUT_BUF_LENGTH;i++)
            this->input_buf[i] = _DRUM_THRESHOLD;
        this->max = _DRUM_THRESHOLD;
        sensing = false;
    }

    // Analog input을 얻는다.
    void set();
    // 가장 최근의 input과 max 값을 비교하여 갱신한다.
    void setMax();

    // 기억하고 있는 input 중 가장 최대값을 뽑고, 최대값을 다시 input Domain 내에 가장 작은 값으로 설정한다.
    int get();


    // 가장 최근에 받아온 input을 return한다.
    int recent_get();

    // 드럼의 input이 시작됐으면, true를 return한다.
    bool signal_on();
    // 드럼의 input이 진행중이면, true를 return한다.
    bool signal_doing();
    // 드럼의 output이 시작됐으면, false를 return한다.
    bool signal_off();

    //모든 buffer 값 출력
    bool debug(char* buf);
};

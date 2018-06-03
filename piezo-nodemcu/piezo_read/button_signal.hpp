#include <arduino.h>
#define RECORD_THRESHOLD 300
#define PLAY_THRESHOLD 400

enum signal_status
{
    p_idle,
    p_record,
    p_play,
};
enum status_identifier
{
    idle,
    recording,
    record_end,
    playing,
    play_end,
};


class Button_signal
{
    int pin;
    int status;

    int prev_signal;
    int signal;

    public:
        Button_signal(int _pin = 0) : pin(_pin)
        {
            pinMode(pin, INPUT);
            this->status = idle;
            this->prev_signal = this->signal = p_idle;
        }

        //Signal을 읽어와서 현재 상태를 얻어온다.
        //현재 상태를 Serial로 보내고, 필요할 경우 elapsed를 초기화한다.
        int read(unsigned long* elpased);
};

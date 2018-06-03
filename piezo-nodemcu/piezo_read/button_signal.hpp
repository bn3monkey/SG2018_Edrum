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
    record_start,
    recording,
    record_end,
    play_start,
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
        int read();
        // read에서 얻어온 현재 상태를 이용해, 현재 상태에서 필요한 부분을 세팅한다.
        void set(unsigned long* elapsed);
};

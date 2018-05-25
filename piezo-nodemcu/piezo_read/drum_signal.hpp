#define INPUT_BUF_LENGTH 11
class Drum_signal
{
    int DRUM_THRESHOLD;
    int input_buf[INPUT_BUF_LENGTH];
    int max;

    Drum_signal(int _DRUM_THRESHOLD)
    {
        DRUM_THRESHOLD = _DRUM_THRESHOLD;
        for(int i=0;i<INPUT_BUF_LENGTH;i++)
            this->input_buf[i] = _DRUM_THRESHOLD;
        this->max = _DRUM_THRESHOLD;
    }

    // Analog input을 얻는다.
    void set(int input);
    // 가장 최근의 input과 max 값을 비교하여 갱신한다.
    void setMax();

    // 기억하고 있는 input 중 가장 최대값을 뽑는다.
    int get();


    // 가장 최근에 받아온 input을 return한다.
    int recent_get();

    // 드럼의 input이 시작됐으면, true를 return한다.
    bool signal_on();
    // 드럼의 output이 시작됐으면, false를 return한다.
    bool signal_off();
}
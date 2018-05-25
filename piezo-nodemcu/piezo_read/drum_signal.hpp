#define INPUT_BUF_LENGTH 11
class drum_signal
{
    int input_buf[INPUT_BUF_LENGTH];
    int max;

    drum_signal()
    {
        for(int i=0;i<INPUT_BUF_LENGTH;i++)
            this->input_buf[i] = 0;
        this->max = 0;
    }

    // Analog input을 얻는다.
    void set(int input);
    // 기억하고 있는 input 중 가장 최대값을 뽑는다.
    void get();
    // 가장 최근에 받아온 input을 return한다.
    void recent_get();

    // 드럼의 input이 시작됐으면, true를 return한다.
    bool signal_on();
    // 드럼의 output이 시작됐으면, false를 return한다.
    bool signal_off();
}
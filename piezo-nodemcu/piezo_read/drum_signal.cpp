#include "drum_signal.hpp"
#include <stdio.h>
#include <string.h>
// Analog input을 얻는다.
void Drum_signal::set(int input)
{
    int i;
    for(i=0;i<INPUT_BUF_LENGTH-1;i++)
        this->input_buf[i] = this->input_buf[i+1];
    this->input_buf[i] = input;
}
void Drum_signal::setMax()
{
    int temp = this->input_buf[INPUT_BUF_LENGTH-1];
    if(temp > max)
        max = temp;
}
// 기억하고 있는 input 중 가장 최대값을 뽑는다.
// , 최대값을 다시 input Domain 내에 가장 작은 값으로 설정한다.
int Drum_signal::get()
{
    int temp = this->max;
    this->max = DRUM_THRESHOLD;
    return temp;
}

// 가장 최근에 받아온 input을 return한다.
int Drum_signal::recent_get()
{
    return this->input_buf[INPUT_BUF_LENGTH -1];
}

// 드럼의 input이 시작됐으면, true를 return한다.
bool Drum_signal::signal_on()
{
    int i;
    for(i=0; i<INPUT_BUF_LENGTH-1;i++)
        if(this->input_buf[i] > DRUM_THRESHOLD)
            break;
    if(i == INPUT_BUF_LENGTH-1 && this->input_buf[INPUT_BUF_LENGTH-1] > DRUM_THRESHOLD)
    {
        this->sensing = true;
        return true;
    }
    else
        return false;
}
// 드럼의 input이 진행중이면, true를 return한다.
bool Drum_signal::signal_doing()
{
      return this->sensing;
}
// 드럼의 output이 시작됐으면, false를 return한다.
bool Drum_signal::signal_off()
{
  int i;
    for(i=1; i<INPUT_BUF_LENGTH;i++)
        if(this->input_buf[i] > DRUM_THRESHOLD)
            break;
    if(i == INPUT_BUF_LENGTH && this->input_buf[0] > DRUM_THRESHOLD)
    {
        this->sensing = false;
        return true;
    }
    else
        return false;
}

bool Drum_signal::debug(char* buf)
{
  int len = 0;
  for(int i=0;i<INPUT_BUF_LENGTH;i++)
  {
    sprintf(buf+len, "%d ", this->input_buf[i]);
    len = strlen(buf);
  }
}


#include "button_signal.hpp"

int Button_signal::read()
{
   this->signal = analogRead(this->pin);

    if(RECORD_THRESHOLD <= this->signal &&  this->signal < RECORD_THRESHOLD + 100)
    {
        this->signal = p_record;
    }
    else if(PLAY_THRESHOLD <= this->signal && this->signal < PLAY_THRESHOLD + 100)
    {
        this->signal = p_play;
    }
    else
    {
        this->signal = p_idle;
    }


    switch(this->status)
    {
        case record_start : 
            this->status = recording;
            break;

        case recording :
            if(this->prev_signal == p_idle && this->signal == p_record)
                this->status = record_end;
            break;

        case record_end :
            this->status = idle;
            break;

        case play_start :
            this->status = playing;
            break;

        case playing :
            if(this->prev_signal == p_idle && this->signal == p_play)
                this->status = play_end;
            break;

        case play_end:
            this->status = idle;
            break;
        
        case idle :
            if(this->prev_signal == p_idle)
            {
                switch(this->signal)
                {
                    case p_idle : this->status = idle; break;
                    case p_record : this->status = record_start; break;
                    case p_play : this->status = play_start; break;
                }
            }
            break;

        
    }

    this->prev_signal = this->signal;

    return this->status;
}

void Button_signal::set(unsigned long* elapsed)
{
    switch(this->status)
    {
        case record_start : Serial.write("record_start 0 0\n"); *elapsed = 0; break;
        case record_end: Serial.write("record_end 0 0\n");  break;
        case play_start : Serial.write("play_start 0 0\n"); *elapsed = 0; break;
        case play_end: Serial.write("play_end 0 0\n"); break;
    }
}

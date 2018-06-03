#include "button_signal.hpp"

int Button_signal::read(unsigned long* elapsed)
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

    
    if(this->status == recording)
    {
        if(this->prev_signal == p_idle && this->signal == p_record)
        {   
            Serial.println("record_end 0 0");
            this->status = record_end;
        }
    }
    else if(this->status == playing)
    {
        if(this->prev_signal == p_idle && this->signal == p_play)
        {
            Serial.println("play_end 0 0");
            this->status = play_end;
        }
    }
    else // (this->status == idle)
    {
        if(this->prev_signal == p_idle)
        {
            switch(this->signal)
            {
                case p_idle : this->status = idle; break;
                case p_record : this->status = recording; 
                                Serial.println("record_start 0 0");
                                *elapsed = 0; break;
                case p_play : this->status = playing; 
                                Serial.println("play_start 0 0");
                                *elapsed = 0;break;
            }
        }
    }

    this->prev_signal = this->signal;

    return this->status;
}


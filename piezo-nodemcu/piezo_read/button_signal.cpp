#include "button_signal.hpp"
#include "serial_protocol.h"

int Button_signal::read()
{
   this->power = analogRead(this->pin);
   
    if(RECORD_THRESHOLD <= this->power &&  this->power < RECORD_THRESHOLD + 100)
    {
        this->signal = p_record;
    }
    else if(PLAY_THRESHOLD <= this->power && this->power < PLAY_THRESHOLD + 100)
    {
        this->signal = p_play;
    }
    else if(FILEDOWN_THRESHOLD <= this->power && this->power < FILEDOWN_THRESHOLD + 100)
    {
        this->signal = p_filedown;
    }
    else if(FILEUP_THRESHOLD <= this->power && this->power < FILEUP_THRESHOLD + 100)
    {
        this->signal = p_fileup;
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
        
        case file_up:
            this->status = idle;
            break;
        
        case file_down:
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
                    case p_fileup : this->status = file_up; break;
                    case p_filedown : this->status = file_down; break;
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
        case record_start : Serial.print(cmd_recordstart ,DEC); *elapsed = 0; break;
        case record_end: Serial.print(cmd_recordend ,DEC); break;
        case play_start : Serial.print(cmd_playstart ,DEC); *elapsed = 0; break;
        case play_end: Serial.print(cmd_playend ,DEC); break;
        case file_up : Serial.print(cmd_fileup ,DEC); break;
        case file_down :  Serial.print(cmd_filedown ,DEC); break;
    }
    Serial.write(" ");
    Serial.print(this->power, DEC);
    Serial.write(" 0\n");
}

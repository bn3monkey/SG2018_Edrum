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

static void cmd_send(int command, int power, int chrono)
{
  Serial.print(command ,DEC);
  Serial.write(" ");
  Serial.print(power, DEC);
  Serial.write(" ");
  Serial.println(chrono, DEC);
}
void Button_signal::set(unsigned long* elapsed, note_queue* q)
{
    switch(this->status)
    {
        case record_start :cmd_send(cmd_recordstart, this->power, 0); *elapsed = 0; break;
        case record_end : cmd_send(cmd_recordend, this->power, 0);break;
        case play_start : cmd_send(cmd_playstart, this->power, 0); *elapsed = 0; 
        
                        while(q[0].download());
                        while(q[1].download());
                        
                        q[0].download_debug();
                        q[1].download_debug();
        
                        break;
        case play_end : cmd_send(cmd_playend, this->power, 0); break;
        case file_up : cmd_send(cmd_fileup, this->power, 0); break;
        case file_down : cmd_send(cmd_filedown, this->power, 0); break;
    }
   
}

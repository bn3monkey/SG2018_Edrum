#include "button_signal.hpp"
#include "serial_protocol.h"

int Button_signal::read(int* status)
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


    switch(*status)
    {
        case record_start : 
            *status = recording;
            break;

        case recording :
            if(this->prev_signal == p_idle && this->signal == p_record)
                *status = record_end;
            break;

        case record_end :
            *status = idle;
            break;

        case play_start :
            *status = playing;
            break;

        case playing :
            if(this->prev_signal == p_idle && this->signal == p_play)
                *status = play_end;
            break;

        case play_end:
            *status = idle;
            break;
        
        case file_up:
            *status = idle;
            break;
        
        case file_down:
            *status = idle;
            break;

        case idle :
            if(this->prev_signal == p_idle)
            {
                switch(this->signal)
                {
                    case p_idle : *status = idle; break;
                    case p_record : *status = record_start; break;
                    case p_play : *status = play_start; break;
                    case p_fileup : *status = file_up; break;
                    case p_filedown : *status = file_down; break;
                }
            }
            break;

        
    }

    this->prev_signal = this->signal;

    return *status;
}


void Button_signal::set(int* status, unsigned long* elapsed, note_queue* q)
{
    switch(*status)
    {
        case record_start :cmd_send(cmd_recordstart, this->power, 0); *elapsed = 0; break;
        case record_end : cmd_send(cmd_recordend, this->power, 0);break;
        case play_start : cmd_send(cmd_playstart, this->power, 0); *elapsed = 0; 
        
                        if(!q[0].download(1))
                        {
                            *status = play_end;
                            cmd_send(cmd_downloadfail, 0, 0);
                            return;
                        }
                        if(!q[1].download(1))
                        {
                            *status = play_end;
                            cmd_send(cmd_downloadfail, 0, 0);
                            return;
                        }
                        
                        q[0].download_debug();
                        q[1].download_debug();
        
                        break;
        case play_end : cmd_send(cmd_playend, this->power, 0); break;
        case file_up : cmd_send(cmd_fileup, this->power, 0); break;
        case file_down : cmd_send(cmd_filedown, this->power, 0); break;
    }
   
}

#include "ButtonSignal.hpp"
void ButtonSignal::read(unsigned long elapsed)
{
    // read analog input from sensor
    value = analogRead(this->pin);
    
    // if you do not press button, clean queue.
    if(value > t_idle)
    {
        queue.clean();
        pressed = false;
        written = false;
    }
    // if you press button, push input to queue and check 'pressed'
    else
    {
        queue.push(value);
        pressed = true;
    }

    // set time from elapsed
    note.time = elapsed;
}

void ButtonSignal::write()
{
    // send signal if pressed but not sended and queue is full
    if(written == false && pressed == true && queue.full())
    {
        // check that the signal is already sent
        written = true;

        // set power to average value of all queue value
        note.power = queue.average();
        
        // set drum name to make protocol
        switch(note.power/100)
        {
            case t_up : note.drum = np_up; break;
            case t_down : note.drum = np_down;break;
            case t_left : note.drum = np_left;break;
            case t_right : note.drum = np_right;break;
            case t_ok : note.drum = np_ok;break;
            default : note.drum = np_idle; break;
        }
        
        // send note
        note.send();
    }
}
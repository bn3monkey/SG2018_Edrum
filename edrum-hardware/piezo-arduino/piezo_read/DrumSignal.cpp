#include "DrumSignal.hpp"
// read analog input
void DrumSignal::read(unsigned long elapsed)
{
    // set previous value
    pre_value = value;

    // read analog input
    value = analogRead(this->pin);
    // filter analog input
    // control high frequency signal using moving average filter
    filter.push(value);
    value = filter.average();
    // use moving average filter to remove local maxima
    filter2.push(value);
    value = filter2.average();


    // send note
    note.time = elapsed;
}

void DrumSignal::write()
{
    if(value > drum_threshold)
    {
        // current derivative is positive and current value is max, change max 
        if(pre_value < value && max < value)
            max = value;
        // current derivative is negative and current vlaue is not max, send current max and initialize
        else if(pre_value > value && max > value)
        {
            note.power = max;
            note.send();
            max = 0;
        }
    }
}
// send signal in csv form to client 
void DrumSignal::test_write()
{
    note.power = value;
    note.csv_send();
}
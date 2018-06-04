#include <arduino.h>

#define MAX_SIGNAL 256

class LED_signal
{
    int pin_red;
    int pin_green;
    int pin_blue;

    public:
        LED_signal(int _red = 0, int _green = 1, int _blue = 2) :
            pin_red(_red), pin_green(_green), pin_blue(_blue) 
        {
            pinMode(_red, OUTPUT);
            pinMode(_green, OUTPUT);
            pinMode(_blue, OUTPUT);
        }
        
        void read();
        void write(int red, int green, int blue);


};

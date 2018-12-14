#include "led_signal.hpp"

void LED_signal::write(int red, int green, int blue)
{
    analogWrite(pin_red, red);
    analogWrite(pin_green, green);
    analogWrite(pin_blue, blue); 
}
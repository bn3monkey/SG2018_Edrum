#include "button_signal.hpp"
#include "drum_signal.hpp"
#include "led_signal.hpp"

#define DRUM1 A1
#define DRUM2 A2
#define BUTTON A0

#define RED1 10
#define GREEN1 11
#define BLUE1 9

#define RED2 5
#define GREEN2 6
#define BLUE2 3

//the qunatitiy of drum sensor signals.
#define NUM_DRUM 2

Drum_signal drum[NUM_DRUM];
LED_signal led[NUM_DRUM];
Button_signal button;

//For serial message
char buf[1000];

//For switch press
int status;

//For time checking
unsigned long elapsed;

void setup()
{
  drum[0] = Drum_signal(A1);
  drum[1] = Drum_signal(A2);  
  led[0] = LED_signal(RED1, GREEN1, BLUE1);
  led[1] = LED_signal(RED2, GREEN2, BLUE2);
  button = Button_signal(BUTTON);

  elapsed = 0;
  
  Serial.begin(115200);
}

void loop()
{  
  drum[0].set();
  drum[1].set();
  status = button.read();
  button.set(&elapsed);

  if(status == recording || status == playing)
  {
    for(int i=0;i<NUM_DRUM;i++)
    {
      if(drum[i].signal_on() || drum[i].signal_doing())
      {
        //sprintf(buf,"SIG : %d",drum[i].recent_get());
        //Serial.println(buf);
        drum[i].setMax();
      }

      if(drum[i].signal_off())
      {
        //drum[i].debug(buf);
        //Serial.println(buf);
        sprintf(buf, "%d %d %lu",0x10 * (i+1),drum[i].get(),elapsed);
        Serial.println(buf);
      }
    }
  }


  elapsed = elapsed + 1;
  delay(1);
}

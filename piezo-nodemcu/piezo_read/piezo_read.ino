#include "drum_signal.hpp"

#define DRUM1 A1
#define DRUM2 A2
#define BUTTON A0
#define DRUM_THRESHOLD 0
#define BUTTON_THRESHOLD 100

//the qunatitiy of drum sensor signals.
#define NUM_DRUM 2

Drum_signal drum[NUM_DRUM];

int button;

//For serial message
char buf[1000];

//For switch press
bool pressed;
bool onoff;

//For time checking
unsigned long elapsed;


void setup()
{
  for(int i=0; i< NUM_DRUM; i++)
    drum[i] = Drum_signal(DRUM_THRESHOLD);
  elapsed = 0;
  pressed = false;
  onoff = false;
  Serial.begin(115200);
}

void loop()
{  
  button = 0;

  drum[0].set(analogRead(DRUM1));
  drum[1].set(analogRead(DRUM2));
  
  button = analogRead(BUTTON);

  //pressed
  if(button > BUTTON_THRESHOLD)
  {
    //not pressed -> pressed
    if(pressed == false)
    {
      pressed = true;
      onoff = !onoff;
      if(onoff)
      {
        sprintf(buf, "start 0 0\n");
        elapsed = 0;
      }
      else
        sprintf(buf, "end 0 0\n");
      Serial.print(buf);
    }
  }
  else
  {
    //pressed -> not pressed
    if(pressed == true)
    {
      pressed = false;
    }
  }

  if(onoff)
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
        sprintf(buf, "DRUM%d %d %lu",i+1,drum[i].get(),elapsed);
        Serial.println(buf);
      }
    }
  }

  elapsed = elapsed + 1;
  delay(1);
}

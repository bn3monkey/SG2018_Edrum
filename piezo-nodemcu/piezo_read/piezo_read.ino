#include "drum_signal.hpp"

#define DRUM1 A1
#define DRUM2 A2
#define BUTTON A0
#define DRUM_THRESHOLD 0
#define BUTTON_THRESHOLD 100

//the qunatitiy of drum sensor signals.
#define NUM_DRUM 2

drum_signal drum[NUM_DRUM];

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
  elapsed = 0;
  pressed = false;
  onoff = false;
  Serial.begin(115200);
}

void loop()
{  
  button = 0;

  for(int i=0;i<NUM_DRUM;i++)
    drum[i].prev = drum[i].now;
  drum[0].now = analogRead(DRUM1);
  drum[1].now = analogRead(DRUM2);
  
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
      //input start
      bool v_check = noise_check(&drum[i]);
      
      if(drum[i].now > DRUM_THRESHOLD && drum[i].prev <= DRUM_THRESHOLD)
      {
        if(drum[i].maxima < drum[i].now)
          drum[i].maxima = drum[i].now;
      }
      //input end
      if(drum[i].now <= DRUM_THRESHOLD && drum[i].prev > DRUM_THRESHOLD)
      {
        sprintf(buf,"DRUM%d %d %lu",i,drum[i].maxima,elapsed);
        Serial.println(buf);
        drum[i].maxima = DRUM_THRESHOLD;
      }
    }
  }

  elapsed = elapsed + 1;
  delay(1);
}

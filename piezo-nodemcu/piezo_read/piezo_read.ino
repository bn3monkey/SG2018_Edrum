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

#define DRUM_THRESHOLD 5
#define BUTTON_THRESHOLD 100

//the qunatitiy of drum sensor signals.
#define NUM_DRUM 2

Drum_signal drum[NUM_DRUM];
LED_signal led[NUM_DRUM];

int button;

//For serial message
char buf[1000];

//For switch press
bool pressed;
bool onoff;

//For time checking
unsigned long elapsed;

int val;

void setup()
{
  drum[0] = Drum_signal(A1, DRUM_THRESHOLD);
  drum[1] = Drum_signal(A2, DRUM_THRESHOLD);  
  led[0] = LED_signal(RED1, GREEN1, BLUE1);
  led[1] = LED_signal(RED2, GREEN2, BLUE2);
  
  elapsed = 0;
  pressed = false;
  onoff = false;

  
  
  val = 0;
  
  Serial.begin(115200);
}

void loop()
{  
  button = 0;

  drum[0].set();
  drum[1].set();
  
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


  switch(elapsed % 3000)
  {
    case 0 : led[0].write(val, 0, 0); led[1].write(val, 0, 0);
            Serial.print("RED ");
            Serial.println(val, DEC); break;
    case 1000 : led[0].write(0, val, 0); led[1].write(0, val, 0);
            Serial.print("GREEN ");
            Serial.println(val, DEC); break;
    case 2000: led[0].write(0, 0, val); led[1].write(0, 0, val);
            Serial.print("BLUE ");
            Serial.println(val, DEC); val += 1; break;
  }
  if(val> 255)
    val = 0;


  elapsed = elapsed + 1;
  delay(1);
}

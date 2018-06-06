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

//the quantity of drum sensor signals.
#define NUM_DRUM 2

Drum_signal drum[NUM_DRUM];
LED_signal led[NUM_DRUM];
Button_signal button;
note_queue nqueue[NUM_DRUM];

//For serial message
char buf[1000];

//For switch press
int status;

//For time checking
unsigned long elapsed;

// when hit_time is determined, these value are true.
bool hit_time[NUM_DRUM];

void setup()
{
  drum[0] = Drum_signal(A1);
  drum[1] = Drum_signal(A2);  
  led[0] = LED_signal(RED1, GREEN1, BLUE1);
  led[1] = LED_signal(RED2, GREEN2, BLUE2);
  button = Button_signal(BUTTON);

  nqueue[0] = note_queue(0);
  nqueue[1] = note_queue(1);

  hit_time[0] = false;
  hit_time[1] = false;

  elapsed = 0;
  
  Serial.begin(115200);
}

void loop()
{ 
  //For button input test 
  //Serial.println(analogRead(BUTTON), DEC);
  
  drum[0].set();
  drum[1].set();
  status = button.read();
  button.set(&elapsed, nqueue);

  if(status == playing || status == recording)
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
        hit_time[i] = true;
      }
    }

    if(status == playing)
    {
      for(int i=0;i<NUM_DRUM;i++)
      {
        int score = nqueue[i].note_sync(elapsed);
        
        //1. 현재 가장 가까운 노트 확인
        if(score == passaway)
        {
          //2-1. 지났으면 현재 노트를 새 노트로 변경
          led[i].write(0, 0, 0);
          cmd_send(cmd_downloadreq, 0, 0);
          nqueue[i].refresh(1);
          nqueue[i].refresh_debug();
        }
        //2-2. 지나지 않았으면, 현재 시각이랑 간격 확인
        else
        {
          //3(2-2일 경우). 시각에 따라서 불이 들어옴
          switch(score)
          {
            case verybad : led[i].write(0, 0, 0); break;
            case bad : led[i].write(0, 1, 0); break;
            case good : led[i].write(0, 20, 0); break;
            case nice : led[i].write(0, 40, 0); break;
            case excellent : led[i].write(0, 60, 0); break;
          }

          //4(2-2일 경우). 현재 친거랑 비교해서 채점해서 Serial로 메시지 보냄
        }
      }
    }
  }


  elapsed = elapsed + 1;
  hit_time[0] = false;
  hit_time[1] = false;

  delay(1);
}

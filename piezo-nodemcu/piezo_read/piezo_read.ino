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

//드럼 개수
#define NUM_DRUM 2

// 드럼 센서 처리 클래스
Drum_signal drum[NUM_DRUM];
// LED 센서 처리 클래스
LED_signal led[NUM_DRUM];
// 버튼 센서 처리 클래스
Button_signal button;
// 라즈베리 파이에서 받아온 노트 정보 처리 클래스
note_queue nqueue[NUM_DRUM];

//현재 상태
int status;

// recording이나 playing을 시작하고 나서 지난 시간
unsigned long elapsed;

// 드럼을 치고 나서 얼마만큼 LED를 켜줄 지 결정해주는 변수
#define HIT_TIMELAP 50
int hit_time[NUM_DRUM];

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

  status = idle;
  elapsed = 0;
  
  Serial.begin(115200);
}

void loop()
{ 
  //For button input test 
  //Serial.println(analogRead(BUTTON), DEC);
  
  //1. 드럼값을 센서로 받아옴
  drum[0].set();
  drum[1].set();
  //2. 버튼값을 받아 현재 상태를 결정
  button.read(&status);
  // 3. 현재 상태를 통해, 필요한 것들을 초기화 
  button.set(&status, &elapsed, nqueue);

  
  if(status == playing || status == recording)
  {
    //4. 드럼의 입력에 관한 부분
    for(int i=0;i<NUM_DRUM;i++)
    {
      //5. 드럼의 입력이 진행중일 때 입력의 최대값과 그 때의 시간을 기억한다.
      if(drum[i].signal_on() || drum[i].signal_doing())
      {
        //sprintf(buf,"SIG : %d",drum[i].recent_get());
        //Serial.println(buf);
        drum[i].setMax();
      }
      //6. 드럼의 입력이 끝났을 때 기억해둔 최대값과 그 시점을 라즈베리 파이로 보낸다.
      // 이 때 채점 시 사용을 위해 hit_time 변수의 값을 올려둔다. 
      if(drum[i].signal_off())
      {
        //drum[i].debug(buf);
        //Serial.println(buf);
        cmd_send(0x10 * (i+1), drum[i].get(), elapsed);
        hit_time[i] = HIT_TIMELAP;
      }
    }

    if(status == playing)
    {
      int allplay = 0;
      
      for(int i=0;i<NUM_DRUM;i++)
      {
         //1. 현재 시점에서 가장 가까운 노트 확인
        int score = nqueue[i].note_sync(elapsed);
        
        // 지났으면 현재 노트를 새 노트로 변경
        if(score == passaway)
        {
          led[i].write(0, 0, 0);
          //현재 led의 모든 노트를 출력했으면, 체크!
          if(nqueue[i].finish())
          {
            allplay++;
            continue;
          }
          //라즈베리 파이에서 새 노트를 받아온다.
          if(!nqueue[i].refresh(1))
          {
            status = play_end;
            cmd_send(cmd_playend, 0, 0);
            cmd_send(cmd_refreshfail, 0, 0);
            break;
          }
          nqueue[i].refresh_debug();
        }
        // 지나지 않았으면, 현재 시각이랑 간격 확인
        else
        {
          // 시각에 따라서 불이 들어옴
          if(!hit_time[i])
          {
            switch(score)
            {
              case verybad : led[i].write(0, 0, 0); break;
              case bad : led[i].write(0, 1, 0); break;
              case good : led[i].write(20, 20, 0); break;
              case nice : led[i].write(25, 50, 0); break;
              case excellent : led[i].write(0, 60, 0); break;
            }
          }
          // 현재 친거랑 비교해서 채점해서 Serial로 메시지 보냄
          // 채점이 된 것을 LED의 불이 달라지는 것을 통해 표현.
          else if(hit_time[i] == HIT_TIMELAP)
          {
            switch(score)
            {
              case verybad : led[i].write(1, 0, 0); break;
              case bad : led[i].write(60, 0, 0); break;
              case good : led[i].write(20, 0, 20); break;
              case nice : led[i].write(0, 0, 40); break;
              case excellent : led[i].write(0, 0, 60); break;
            }
             cmd_send(cmd_scoring, score ,0);
          }
        }
      }
      //모든 LED의 값이 다 출력됐다면 play는 끝냄.
      if(allplay == NUM_DRUM)
      {
        led[0].write(0, 0, 0);
        led[0].write(0, 0, 0);
        status = play_end;
        cmd_send(cmd_playend, 0, 0);
        cmd_send(cmd_endscore, 0 ,0);
      }
    }
  }


  elapsed = elapsed + 1;

  // hit_time을 정확히 HIT_TIMELAP을 처음 설정할 때만 불이 들어오고
  // hit_time 안에 있는 동안은 LED를 건들지 않고
  // hit_time이 0일 때는 노트 대로 작동하게 함으로서
  // 드럼을 쳤을 때 HIT_TIMELAP 시간동안만 LED에 채점 불이 들어오게 하는 것을 의도함.
  if(hit_time[0]>0)
    hit_time[0]--;
  if(hit_time[1]>0)
    hit_time[1]--;
  delay(1);
}

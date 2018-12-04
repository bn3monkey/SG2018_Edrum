#include "DrumSignal.hpp"
#include "ButtonSignal.hpp"

#define DRUM1 A1
#define DRUM2 A2
#define BUTTON A0

//드럼 개수
#define NUM_DRUM 2

DrumSignal drum[NUM_DRUM];
ButtonSignal button;

unsigned long elapsed;

void setup()
{
  drum[0] = DrumSignal(A1, np_drum1);
  drum[1] = DrumSignal(A2, np_drum2);  
  button = ButtonSignal(BUTTON);
  
  elapsed = 0;
  
  Serial.begin(115200);
}

void loop()
{ 
  
  
  //1. 드럼값을 센서로 받아옴
  drum[0].read(elapsed);
  //drum[1].read(elapsed);
  //2. 버튼값을 받아 현재 상태를 결정
  button.read(elapsed);

  drum[0].write();
  //drum[1].write();
  button.write();

  elapsed = elapsed + 1;

  delay(1);
}

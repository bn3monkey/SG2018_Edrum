#include "DrumSignal.hpp"
#include "ButtonSignal.hpp"
#include "SerialSignal.hpp"

#define DRUM1 A1
#define DRUM2 A2
#define BUTTON A0

//드럼 개수
#define NUM_DRUM 2

DrumSignal drum[NUM_DRUM];
ButtonSignal button;
SerialSignal serial;

unsigned long elapsed;

void setup()
{
  drum[0] = DrumSignal(A1, np_drum1);
  drum[1] = DrumSignal(A2, np_drum2);  
  button = ButtonSignal(BUTTON);
  serial = SerialSignal();

  elapsed = 0;
  
  Serial.begin(115200);
}

void loop()
{ 
  
  
  // read drum signal
  drum[0].read(elapsed);
  //drum[1].read(elapsed);
  // read button signal
  button.read(elapsed);
  // read serial signal
  serial.read();

  // write drum signal
  //drum[0].test_write();
  drum[0].write();
  //drum[1].write();
  // write button signal
  button.write();
  //write serial signal
  serial.write(elapsed);

  elapsed = elapsed + 1;

  delay(1);
}

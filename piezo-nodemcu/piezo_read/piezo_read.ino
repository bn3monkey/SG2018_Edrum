#define DRUM1 D0
#define DRUM2 D1
#define BUTTON D2
#define THRESHOLD 10

int val1;
int val2;
int val3;
char buff[1000];

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  val1 = analogRead(DRUM1);
  val2 = analogRead(DRUM2);
  val3 = analogRead(BUTTON);
  
  if(val1 > THRESHOLD)
  {
      sprintf(buff, "DRUM1 : %d:", val1); 
      Serial.println(buff); 
  }
  
  if(val2 > THRESHOLD)
  {
    sprintf(buff, "DRUM2 : %d:", val2);
    Serial.println(buff);
  }


  if(val3)
  {
    sprintf(buff, "SWITCH : %d:", val3);
    Serial.println(buff);
  }

  delay(1);
}

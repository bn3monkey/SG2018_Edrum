#define DRUM1 D0
#define DRUM2 D1
#define BUTTON A0
#define THRESHOLD 50

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
  val1 = 0;
  val2 = 0;
  val3 = 0;
  val1 = analogRead(DRUM1);
  val2 = analogRead(DRUM2);
  val3 = analogRead(BUTTON);

  
  if (val1)
  {
    sprintf(buff, "DRUM1 : %d:", val1);
    Serial.println(buff);
  }


  if (val2)
  {
    sprintf(buff, "DRUM2 : %d:", val2);
    Serial.println(buff);
  }  


  
    if(val3 > THRESHOLD)
    {
      sprintf(buff, "BUTTON : %d:", val3);
      Serial.println(buff);
    } 
  
  delay(1);
}

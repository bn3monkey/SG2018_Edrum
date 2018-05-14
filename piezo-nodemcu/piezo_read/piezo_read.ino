#define DRUM1 A1
#define DRUM2 A2
#define BUTTON A0
#define DRUM_THRESHOLD 20
#define BUTTON_THRESHOLD 100

int drum1;
int drum2;
int button;
bool pressed;
char buff[1000];
bool onoff;
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
  drum1 = 0;
  drum2 = 0;
  button = 0;
  drum1 = analogRead(DRUM1);
  drum2 = analogRead(DRUM2);
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
        sprintf(buff, "start 0 0");
        elapsed = 0;
      }
      else
        sprintf(buff, "end 0 0");
      Serial.println(buff);
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
    if (drum1 >= DRUM_THRESHOLD)
    {
      sprintf(buff, "DRUM1 %d %lu", drum1, elapsed);
      Serial.println(buff);
    }


    if (drum2 >= DRUM_THRESHOLD)
    {
      sprintf(buff, "DRUM2 %d %lu", drum2, elapsed);
      Serial.println(buff);
    }
  }

  elapsed = elapsed + 1;
  delay(1);
}

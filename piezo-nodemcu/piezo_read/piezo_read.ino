#define DRUM1 A1
#define DRUM2 A2
#define BUTTON A0
#define DRUM_THRESHOLD 20
#define BUTTON_THRESHOLD 100

//the qunatitiy of drum sensor signals.
int drum1[3] = {0};
int drum2[3] = {0};
int button;

//For serial message
char buff[1000];

//For switch press
bool pressed;
bool onoff;

//For time checking
unsigned long elapsed;

void setup()
{
  for(int i=0;i<3;i++)
  {
    drum1[i] = 0;
    drum2[i] = 0;
  }
  elapsed = 0;
  pressed = false;
  onoff = false;
  Serial.begin(115200);
}

void loop()
{
  drum1[2] = 0;
  drum2[2] = 0;
  button = 0;
  drum1[2] = analogRead(DRUM1);
  drum2[2] = analogRead(DRUM2);
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
        sprintf(buff, "start 0 0\n");
        elapsed = 0;
      }
      else
        sprintf(buff, "end 0 0\n");
      Serial.print(buff);
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
      if(drum1[0] <= drum1[1] && drum1[1] > drum1[2])
      {
        sprintf(buff, "DRUM1 %d %lu\n", drum1[1], elapsed);
        Serial.print(buff);
      }
    }


    if (drum2 >= DRUM_THRESHOLD)
    {
      if(drum2[0] <= drum2[1] && drum2[1] > drum2[2])
      {
        sprintf(buff, "DRUM2 %d %lu\n", drum2[1], elapsed);
        Serial.print(buff);
      }
    }
  }

  /*
  drum1[0] = drum1[1];
  drum1[1] = drum1[2];
  drum2[0] = drum2[1];
  drum2[1] = drum2[2];
`*/
  elapsed = elapsed + 1;
  delay(1);
}

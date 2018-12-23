#include "serial_protocol.h"
#include <arduino.h>
void cmd_send(int command, int power, int chrono)
{
  Serial.print(command ,DEC);
  Serial.write(" ");
  Serial.print(power, DEC);
  Serial.write(" ");
  Serial.println(chrono, DEC);
}
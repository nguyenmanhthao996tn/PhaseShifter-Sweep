#include "PhaseShiftChannel.h"

/*********** Project DataType  ***********/

/*********** Project function  ***********/

/*********** Global variables ***********/
PhaseShiftChannel *phaseShifter;
uint8_t angleIndex = Angle_D0;
Led_State_t status = Led_State_On;

const char *str0 = "0 deg";
const char *str1 = "22.5 deg";
const char *str2 = "45 deg";
const char *str3 = "90 deg";
const char *str4 = "180 deg";
const char *str5 = "337.5 deg";
char* strArr[] = {str0, str1, str2, str3, str4, str5};

/*********** Main ***********/
void setup()
{
  Serial.begin(115200);
  while (!Serial && (millis() < 5000))
  {
  }

  phaseShifter = new PhaseShiftChannel();

  Serial.println("/*********** PhaseShifter Rev2.0 Sweep Test ***********/");

  phaseShifter->setLED(3, Led_State_On); // Set LED on Channel 3
  phaseShifter->setLED(5, Led_State_On); // Set LED on Channel 5
  phaseShifter->update();

  delay(500);
}

void loop()
{
  phaseShifter->setPhaseShiftAngle(3, (PhaseShiftAngle_t)angleIndex);
  phaseShifter->setPhaseShiftAngle(5, (PhaseShiftAngle_t)angleIndex);

  phaseShifter->setLED(0, status);
  status ^= Led_State_Off; // Toggle status

  Serial.print("Phase shift: ");
  Serial.println(strArr[angleIndex]);

  phaseShifter->update();

  if (++angleIndex > Angle_D337_5)
  {
    angleIndex = Angle_D0;
  }

  delay(5000);
}

/*********** Function declare ***********/

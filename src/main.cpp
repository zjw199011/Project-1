// COMP-10184 – Mohawk College
// PIR Sensor Test Application
// Turn on the blue LED with motion is detected.

/**
 * StAuth10184: I Jiawei Zhang, 000730840 certify that this material is my original work.
 * No other person's work has been used without due acknowledgement.
 */

#include <Arduino.h>

// digital input pin definitions
#define PIN_PIR D5
#define PIN_BUTTON D6

// define all possible alarm states.
#define ALARM_DISABLED 0
#define ALARM_ENABLE 1
#define ALARM_COUNTDOWN 2
#define ALARM_ACTIVE 3

int iAlarmState = ALARM_ENABLE;
bool LastButtonValue = 0;

long int startTime = millis();

// *************************************************************
void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);

  // configure the LED output
  pinMode(LED_BUILTIN, OUTPUT);

  // PIR sensor is an INPUT
  pinMode(PIN_PIR, INPUT);

  // Button is an INPUT
  pinMode(PIN_BUTTON, INPUT_PULLUP);
}

void Blinks()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(125);
  digitalWrite(LED_BUILTIN, LOW);
  delay(125);
}

void loop()
{
  bool bPIR;
  bPIR = digitalRead(PIN_PIR);

  int iButton;
  iButton = digitalRead(PIN_BUTTON);

  switch (iAlarmState)
  {
  case ALARM_DISABLED:
  {
    iAlarmState = ALARM_ENABLE;
    digitalWrite(LED_BUILTIN, LOW);
  }
  break;
  case ALARM_ENABLE:
  {
    if (bPIR)
    {
      iAlarmState = ALARM_ACTIVE;
    }
  }
  break;
  case ALARM_COUNTDOWN:
  {
    if (LastButtonValue == 1 && iButton == 0)
    {
      // button status changed
      iAlarmState = ALARM_DISABLED;
    }
    

    unsigned long runMillis = millis() - startTime;
    unsigned long allSeconds = runMillis / 1000;
    if (allSeconds >= 10)
    {
      iAlarmState = ALARM_DISABLED;
    }
    Blinks();
  }
  break;
  case ALARM_ACTIVE:
  {
    startTime = millis();
    iAlarmState = ALARM_COUNTDOWN;
  }
  break;
  default:
    break;
  }

  LastButtonValue = iButton;
}

/*
  Project: ESP32 LED Controller Using Hardware Timer
  Name: Prerna Bhalshankar
  Department: Electronics and Telecommunication
  Board: ESP32 DevKit
*/

#include <Arduino.h>

const int LED_PIN = 2;

hw_timer_t *ledTimer = nullptr;

volatile bool timerEvent = false;
bool ledState = LOW;

// Timer interrupt function
void IRAM_ATTR onTimer()
{
  timerEvent = true;
}

void setup()
{
  // Set LED pin as output
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  // Initialize hardware timer
  ledTimer = timerBegin(1000000);

  // Attach timer interrupt
  timerAttachInterrupt(ledTimer, &onTimer);

  // Set timer interval to 1 second
  timerAlarm(ledTimer, 1000000, true, 0);
}

void loop()
{
  // Check timer event
  if (timerEvent)
  {
    timerEvent = false;

    // Toggle LED
    ledState = !ledState;

    digitalWrite(LED_PIN, ledState);
  }
}
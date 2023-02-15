#include "tripwire.h"
#include <Arduino.h>

// Create a Tripwire instance
Tripwire tw;

// Initialize the tripwire, setting the connected state to 0
void tripwireInit()
{
  tw.connected = 0;
}

// Check the connected state of the tripwire
int tripwireCheck()
{
  // Read the analog value of the tripwire pin and set the connected state to the value
  tw.connected = analogRead(Tripwire::tripwirePin);
  
  // Return the connected state of the tripwire
  return tw.connected;
}

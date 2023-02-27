

  Hardware Connections (Breakoutboard to Arduino):
  -5V = 5V
  -GND = GND
  -SDA = A4 (or SDA)
  -SCL = A5 (or SCL)
  -INT = Not connected

  The MAX30105 Breakout can handle 5V or 3.3V I2C logic but requires 5V to power the sensor.
*/

#include <Wire.h>
#include "MAX30105.h"

MAX30105 particleSensor;

void setup()
{
  Serial.begin(115200);

  
}

void loop()
{
  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

  particleSensor.setup(); //Configure sensor. Use 6.4mA for LED drive

  //Arduino plotter auto-scales annoyingly. To get around this, pre-populate
  //the plotter with 500 of an average reading from the sensor

  //Take an average of IR readings at power up
  const byte avgAmount = 64;
  long baseValue = 0;
  for (byte x = 0 ; x < avgAmount ; x++)
  {
    //Wait for new readings to come in
    while (particleSensor.available() == false)
    {
      particleSensor.check(); //Check the sensor, read up to 3 samples
    }

    baseValue += particleSensor.getIR(); //Read the IR value
    particleSensor.nextSample(); //We're finished with this sample so move to next sample
  }
  baseValue /= avgAmount;

  for (int x = 0 ; x < 500 ; x++)
  
  
   //Serial.println(baseValue);
  particleSensor.check(); //Check the sensor, read up to 3 samples
  while (particleSensor.available()) //do we have new data?
  {
   //this is whats shown on the serial mon
 //Serial.println("BPM"); bILL 
    Serial.println(particleSensor.getIR());
    particleSensor.nextSample(); //We're finished with this sample so move to next sample
   
  }
  
}

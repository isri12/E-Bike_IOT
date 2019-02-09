#include "Adafruit_Si7021.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

Adafruit_Si7021 sensor = Adafruit_Si7021();
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

void configureSensor(void)
{
  /* You can also manually set the gain or enable auto-gain support */
  // tsl.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
  // tsl.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
  tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */
  
  /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
  //tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
  // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */

  /* Initialise the sensor */
  //use tsl.begin() to default to Wire, 
  //tsl.begin(&Wire2) directs api to use Wire2, etc.
  if(!tsl.begin())
  {
    /* There was a problem detecting the TSL2561 ... check your connections */
    Serial.print(F("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!"));
    while(1);
  }
}


void setup() {
  Serial.begin(9600);
  
  // wait for serial port to open
  while (!Serial) {
    delay(10);
  }
  
  if (!sensor.begin()) {
    Serial.println(F("Did not find Si7021 sensor!"));
    while (true);
  }
  
  /* Setup the sensor gain and integration time */
  configureSensor();
}

void loop() {
  Serial.print(F("\nHumidity: "));
  Serial.print(sensor.readHumidity(), 2);
  Serial.print(F("\tTemperature: "));
  Serial.print(sensor.readTemperature(), 2);
  
  sensors_event_t event;
  tsl.getEvent(&event);
  
  if (event.light)
  {
    Serial.print(F("\tBrightness: "));
    Serial.print(event.light); 
  }
  else
  {
    Serial.print(F("\tSensor overload"));
  }
  
  delay(1000);
}


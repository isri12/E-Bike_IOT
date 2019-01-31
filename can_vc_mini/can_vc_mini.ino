// Libraries
#include <SPI.h>
#include <mcp2515.h>
#include <power_data.h>
MCP2515 mcp2515(10);

//-----------------------------------------------------------------------//
// Voltage/Current CAN message ID = 0xAB
//-----------------------------------------------------------------------//

// PINOUT
const PROGMEM byte vtgPin = A0;    // select the input pin for the potentiometer
const PROGMEM byte curntPin = A1;

//-----------------------------------------------------------------------//
void setup() {

  while (!Serial);
  Serial.begin(115200);
  SPI.begin();
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
  Serial.println(F("Example: Write to CAN"));
}

void loop() {
  struct can_frame canMsg;
  struct power_t data;
  // Voltage Sensor
  unsigned int voltage_read = analogRead(vtgPin);
  uint16_t vtgValue = map(voltage_read, 0, 1023, 0, 65535);
  data.voltage = vtgValue * 1.0; // conversion to voltage

  // Current Sensor
  unsigned int current_read = analogRead(curntPin);
  uint16_t curntValue = map(current_read, 0, 1023, 0, 65535);
  data.current = curntValue * 1.0; // Conversion to current
  
  // Building up the CAN message
  data.serialize(&canMsg);
  mcp2515.sendMessage(&canMsg);

  for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
      
    Serial.print(canMsg.data[i],HEX);
    Serial.print(F(" "));
  }
  Serial.println();
  delay(10);
}

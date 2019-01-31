// Libraries
#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg1;
MCP2515 mcp2515(10);

//-----------------------------------------------------------------------//
// Voltage CAN message ID = 0xAB
//-----------------------------------------------------------------------//

// Variables
byte vtgPin = A0;    // select the input pin for the potentiometer
byte curntPin = A1;


//-----------------------------------------------------------------------//
void setup() {

  while (!Serial);
  Serial.begin(115200);
  SPI.begin();
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("Example: Write to CAN");
}

void loop() {

  // Voltage Sensor
  unsigned int raw_vtgValue = analogRead(vtgPin);
  uint16_t vtgValue = map(raw_vtgValue, 0, 1023, 0, 65535);
  float voltage = vtgValue * 1.0; // conversion to voltage

  // Current Sensor
  unsigned int raw_curntValue = analogRead(curntPin);
  uint16_t curntValue = map(raw_curntValue, 0, 1023, 0, 65535);
  float current = curntValue * 1.0; // Conversion to current
  
  // Building up the CAN message
  canMsg1.can_id  = 0xAB;
  canMsg1.can_dlc = 8;
  uint8_t *ptr = canMsg1.data;
  memcpy(ptr, &voltage, sizeof(float));
  ptr += sizeof(float);
  memcpy(ptr, &current, sizeof(float));
  
  mcp2515.sendMessage(&canMsg1);

  for (int i = 0; i<canMsg1.can_dlc; i++)  {  // print the data
      
    Serial.print(canMsg1.data[i],HEX);
    Serial.print(F(" "));
  }
   Serial.println();

  delay(10);
}

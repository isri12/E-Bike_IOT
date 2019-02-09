#include <SPI.h>
#include <mcp2515.h>
#include <power_data.h>

//-----------------------------------------------------------------------//
// Voltage/Current CAN message ID = 0xAB
//-----------------------------------------------------------------------//


MCP2515 mcp2515(10);

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
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(F(" ")); 
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(F(" "));
    
    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
      Serial.print(canMsg.data[i],HEX);
      Serial.print(F(" "));
    }
    Serial.println();

    struct power_t data;
    // reading first 2 bytes  0xAB message of raw data for voltage
    switch(canMsg.can_id){
      case 0xAB: {
        data.deserialize(&canMsg);
        break;
      }
      case 0xBC: {
        
      }
      case
      default:
        break;
    }
    delay(50); 
  }

}

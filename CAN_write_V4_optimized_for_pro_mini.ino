#include <SPI.h>
#include <mcp2515.h>


struct can_frame canMsg1;
//struct can_frame canMsg2;
MCP2515 mcp2515(10);
String  incomingByte; 
int counter = 0 ;
int inByte;
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int16_t outputValue =0;
const int buttonPin = 2;     // the number of the pushbutton pin
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

int sensorPin1 = A1;    // select the input pin for the potentiometer
int sensorValue1 = 0;  // variable to store the value coming from the sensor
int16_t outputValue1 =0;


uint8_t Byte1=0;
uint8_t Byte2=0;
uint8_t Byte3=0;
uint8_t Byte4=0;






void setup() {

// initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

//  canMsg1.can_id  = 0x0F6;
//  canMsg1.can_dlc = 8;
//  canMsg1.data[0] = incomingByte;
//  canMsg1.data[1] = incomingByte;
//  canMsg1.data[2] = 0x00;
//  canMsg1.data[3] = 0x00;
//  canMsg1.data[4] = 0x00;
//  canMsg1.data[5] = 0x00;
//  canMsg1.data[6] = 0x00;
//  canMsg1.data[7] = 0x00;
//
//  canMsg2.can_id  = 0x036;
//  canMsg2.can_dlc = 8;
//  canMsg2.data[0] = 0x0E;
//  canMsg2.data[1] = 0x00;
//  canMsg2.data[2] = 0x00;
//  canMsg2.data[3] = 0x08;
//  canMsg2.data[4] = 0x01;
//  canMsg2.data[5] = 0x00;
//  canMsg2.data[6] = 0x00;
//  canMsg2.data[7] = 0xA0;
  
  while (!Serial);
  Serial.begin(115200);
  SPI.begin();
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
 // Serial.println("Example: Write to CAN");
}

void loop() {


  buttonState = digitalRead(buttonPin);
  
  sensorValue = analogRead(sensorPin);
  outputValue = map(sensorValue, 0, 1023, 0, 65535);

  
  sensorValue1 = analogRead(sensorPin1);
  outputValue1 = map(sensorValue1, 0, 1023, 0, 65535);


  

 if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.readString();
                inByte=incomingByte.toInt(); 
                
                // say what you got:
              //  Serial.print("I received: ");
            //    Serial.println(inByte);
        }


Byte1 = outputValue >>8;
Byte2 = outputValue &0xff;


Byte3 = outputValue1 >>8;
Byte4 = outputValue1 &0xff;


  //delay(500);

  canMsg1.can_id  = 0x0F6;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = Byte1;
  canMsg1.data[1] = Byte2;
  canMsg1.data[2] = Byte3;
  canMsg1.data[3] = Byte4;
  canMsg1.data[4] = 0x00;
  canMsg1.data[5] = 0x00;
  canMsg1.data[6] = 0x00;
  canMsg1.data[7] = buttonState;
  mcp2515.sendMessage(&canMsg1);
 // mcp2515.sendMessage(&canMsg2);
  
  //Serial.print("I received: ");
  //Serial.println(inByte);
      counter++ ; 
      Serial.println("CAN Send");
//    Serial.print(" "); 
//    Serial.print(canMsg1.can_id, HEX); // print ID
//    Serial.print(" "); 
//    Serial.print(canMsg1.can_dlc, HEX); // print DLC
//    Serial.print(" ");
//    
//  for (int i = 0; i<canMsg1.can_dlc; i++)  {  // print the data
//        
//      Serial.print(canMsg1.data[i],HEX);
//      Serial.println(" ");
////
//  }

 delay(10);
 
}

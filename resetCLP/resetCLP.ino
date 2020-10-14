#include <Wire.h>

// 24C04 pins assignment:
// 1 (PRE) write protection not connected
// 2,3,4   E1,E2,VSS  =  GND
// 5,6 SDA, SCL connected to Analog 4, Analog 5 of Arduino
// 7 MODE or  /WC = GND.
// 8 VCC
// 24c04 contains 2 blocks, each 256x8
// I2C device address is 1 0 1 0 E2 E1 block  R/W.          E1/2 = 0 (GND).    
// I2C device  memory is 0x50 for the first block or 0x51 2nd one.
// new memory contains 0xFF everywhere


int addr1 =0x50;     // address 1st block
int addr2 =0x51;     // address 2nd block
int addr  =addr1;

void setup() 
{
   int rc;
  
   Serial.begin(9600);       //
   Serial.println("Resetting...");
   delay(100);
   
   Wire.begin();                    //  i2c bus start
   Wire.beginTransmission(addr);    //restart of address to zero
   rc = Wire.write(0x00);
   Serial.print("Write address 8A returned ");
   Serial.println(rc);
   rc = Wire.write(0);
   Serial.print("Write data returned ");
   Serial.println(rc);

   Serial.println("Writing byte 1...");
   delay(100);
   
   rc = Wire.endTransmission();
   Serial.print("endTransmission returned ");
   Serial.println(rc);

   delay(100);
   Serial.println("Done byte 1!");
   
   Wire.beginTransmission(addr);    //restart of address to zero
   Wire.write(0x8B);
   Serial.print("Write address 8B returned ");
   Serial.println(rc);
   rc = Wire.write(0);
   Serial.print("Write data returned ");
   Serial.println(rc);
   rc = Wire.endTransmission();
   Serial.print("endTransmission returned ");
   Serial.println(rc);

   delay(100);
   Serial.println("Done!");

  delay(100);
  Serial.println("Reading back the data...");
  delay(100);
  
   Wire.beginTransmission(addr);    
   Wire.write(0x0);
   rc = Wire.endTransmission();
   delay(10);
   Serial.print("endTransmission returned ");
   Serial.println(rc);

   Wire.requestFrom(addr,255); // gets the value from the address mentioned above
   do 
   {
      byte data = Wire.read();
      Serial.print("Read: ");
      Serial.println(data);
   }
   while (Wire.available());
   
   rc = Wire.endTransmission();
   delay(10);
   Serial.print("endTransmission returned ");
   Serial.println(rc);

   delay(100);
   Serial.println("Done");
}
  

void loop() 
{
  while(1)
  {}
}

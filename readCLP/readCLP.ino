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

long int blocksize=255;    //how many bytes to be read
long int linesize=8;

byte data[300];      //array to store data, max 100 bytes to read
int i,j=0;           // variables for cycles
int offset = 0;

void setup() 
{
int rc;
  
   Serial.begin(9600);       //
  
   Wire.begin();                    //  i2c bus start
   Wire.beginTransmission(addr);    //restart of address to zero
   Wire.write(0);                        
   rc = Wire.endTransmission(false);
   delay(10);
   Serial.print("endTransmission returned ");
   Serial.println(rc);
   Serial.println();
}


void printLine(int offset, byte *data, int howmany)
{
  if (offset<10) 
  {                              // indent of line counter for better readability. One line contains 'howmany' data.
     Serial.print(" ");
  }
  if (offset<100)
  {
    Serial.print(" ");
  }
  Serial.print(offset);
  Serial.print(":   ");                

  int j;
  for (j=0;j<howmany;j++) 
  {                  // printout of collected data
     if (data[j]<0x10)
      Serial.print('0');
     Serial.print(data[j],HEX);
     Serial.print("   ");
  }        
  
  Serial.print("    ");     
  for (j=0; j<howmany; j++)
  {
     if (data[j]==0)
      Serial.print('.');
     else
      Serial.print((char)data[j]);
     Serial.print(" ");  
  }
  
  Serial.print("    ");     
  for (j=0; j<howmany; j++)
  {
     Serial.print(data[j]);
     Serial.print(" ");  
  }
  Serial.println();                            // end of line
}


void loop() 
{
  Wire.requestFrom(addr,blocksize);               //request to read 'howmany' bytes
  while (Wire.available())
  {
    delay(200);
    for (j=0;j<linesize;j++) 
    {
       data[j]=Wire.read();                // reading howmany bytes if available to array data[]
    }

    // Print out line
    printLine(offset, data, linesize);
    offset+=linesize;
  }
}

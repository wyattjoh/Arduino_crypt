/*
  Step 1: Press button to indicate ready


*/
#include "structs.h"

pub_t pub;
pri_t pri;

uint32_t myPow(uint32_t b, uint32_t p)
{
  uint32_t x = 1;
  
  for(int i = 0; i < p; i++)
  {
    x = b * x;
  }
    
  return x;
}

void setup()
{
  // Ini ports
 
  Serial.begin(9600);
  Serial3.begin(9600);
  
  pub.p = 37;
  pub.g = 5;
  
  pri.a = 12;
  pub.A = myPow(pub.g,pri.a) % pub.p;
}

int16_t key = 100;

void loop()
{
  Serial.print("Public P: ");
  Serial.print(pub.p, HEX);
  Serial.print(" - ");
  Serial.print(pub.p, DEC);
  Serial.print(" - ");
  Serial.println(pub.p, BIN);
  
  Serial.print("Public G: ");
  Serial.print(pub.g, HEX);
  Serial.print(" - ");
  Serial.print(pub.g, DEC);
  Serial.print(" - ");
  Serial.println(pub.g, BIN);
  
  Serial.print("Shared key: ");
  Serial.print(pub.A, HEX);
  Serial.print(" - ");
  Serial.print(pub.A, DEC);
  Serial.print(" - ");
  Serial.println(pub.A, BIN);
  
  Serial.print("\n");
  delay(1000);
  
  // read from port 3
  if(Serial3.available())
  {
    int16_t inByte = Serial3.read();
    
    int16_t decByte = (inByte - key)%256;
    
    Serial.write(decByte);
  }
  
  // read from serial moniter
  if(Serial.available())
  {
    int16_t inByte = Serial.read();
    
    int16_t encByte = (inByte + key)%256;
    
    Serial3.write(encByte);
  }
}


#include "structs.h"
#include "functions.h"

pub_t pub;
pri_t pri;

void setup()
{
  // Ini ports
  Serial.begin(9600);
  Serial3.begin(9600);
  
  Serial.print("\n\nREADY\n\n");
  
  pub.p = 19211;
  pub.g = 6;
  
  pri.a = 0;
  pub.A = 0;
  
  while(pub.A == 0)
  {
    randomSeed(analogRead(0));
    
    pri.a = random(2, 254);
    
    pub.A = pow_mod(pub.g,pri.a,pub.p);
  }
 
  print_variable("Public Key",&pub.A);
  
  char *fpk;
  fpk = read_line("Input Foreign Public Key");
  pub.B = atoi(fpk);
  Serial.print(pub.B, DEC);
  Serial.println("_10");
  
  pri.s = pow_mod(pub.B,pri.a,pub.p);
  
  Serial.print("Waiting for input to encrypt/transmit or decrypt/recieve:\n\n");
}

void loop()
{
  // read from port 3
  if(Serial3.available())
  {
    uint16_t inByte = Serial3.read();
    
    cipher(&inByte, pri.s);
    
    Serial.write(inByte);
  }
  
  // read from serial moniter
  if(Serial.available())
  {
    uint16_t inByte = Serial.read();
    
    cipher(&inByte, pri.s);
    
    Serial3.write(inByte);
  }
}


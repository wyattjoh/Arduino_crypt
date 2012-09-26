/*
  Step 1: Press button to indicate ready


*/
#include "structs.h"
#include "functions.h"

pub_t pub;
pri_t pri;
char *fpk;

void setup()
{
  // Ini ports
 
  Serial.begin(9600);
  Serial3.begin(9600);
  
  pub.p = 37;
  pub.g = 5;
  
  //pri.a = 12; // Now im actually going to use a random seed to generate the session random key
  randomSeed(analogRead(0));
  
  pri.a = random(2, 254);
  
  pub.A = myPow(pub.g,pri.a) % pub.p;
  
  print_variable("Public Key",&pub.A);
  
  fpk = read_line("Input Foreign Public Key");
  pub.B = atoi(fpk);
  Serial.print("\n");
  
  pri.s = myPow(pub.B,pri.a) % pub.p;
}

//uint32_t key = 100;
uint32_t modulo = 256;

void loop()
{
//  print_variable("Private key pri.a", &pri.a);
//  print_variable("Shared key pub.A", &pub.A);
//  print_variable("Shared key pub.B", &pub.B);
//  print_variable("Private Shared Key pri.s", &pri.s);
  
  // read from port 3
  if(Serial3.available())
  {
    int16_t inByte = Serial3.read();
    
    unprotect(&inByte);
    
    Serial.write(inByte);
  }
  
  // read from serial moniter
  if(Serial.available())
  {
    int16_t inByte = Serial.read();
    
    protect(&inbyte);
    
    Serial3.write(inbyte);
  }
}


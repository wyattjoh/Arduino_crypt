#ifndef functions_h
#define functions_h

#include "Arduino.h"

uint16_t pow_mod(uint16_t b, uint16_t p, uint16_t n)
{
  uint32_t x = 1;
  
  for(uint32_t i = 0; i < p; i++)
  {
    x = ((b % n) * (x % n)) % n; // as Mod[b*x,n] == Mod[Mod[b,n]*Mod[x,n],n] == Mod[Mod[b*x,n],n];
  }
    
  return x;
}

char *read_line(char text[] = "Waiting for input")
{
  int bufferlength = 256;
  char buffer[255];
  int i = 0;
  
  Serial.print(text);
  Serial.print(": ");
  
  while(i+1<=bufferlength)
  {
    int8_t input = Serial.read();
    if(input == -1)
    {
      // Nothing to see here... Serial buffer is empty
    }
    else
    {
      // We got a value! Process it.
      buffer[i+1] = '\0'; // Ensure that following char is null terminated
      if(input == '\n') // Is there a new line character?
        break; // If so, break from while loop
      
      buffer[i] = input; // Store input into buffer
      i++; // Increment byte character
    }
  }
  
  return buffer;
}

void cipher(uint16_t *input, uint16_t key)
{
  *input = (*input ^ key);
}

void print_variable(char name[], uint16_t *var)
{
  Serial.print(name);
  Serial.print(": 0x");
  Serial.print(*var, HEX);
  Serial.print(" - ");
  Serial.print(*var, DEC);
  Serial.print("_10 - ");
  Serial.print(*var, BIN);
  Serial.println("_2");
}

void print_compare(uint32_t *var1, uint16_t *var2)
{
  Serial.print(*var1, BIN);
  Serial.print("\t");
  Serial.println(*var2, BIN);
}

#endif

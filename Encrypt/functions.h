#ifndef functions_h
#define functions_h

#include "Arduino.h"

uint32_t myPow(uint32_t b, uint32_t p)
{
  uint32_t x = 1;
  
  for(int i = 0; i < p; i++)
  {
    x = b * x;
  }
    
  return x;
}

uint32_t pow_mod(uint32_t b, uint32_t p, uint32_t n)
{
  uint32_t x = 1;
  
  for(int i = 0; i < p; i++)
  {
    x = b * x;
  }
  
  x = x % n;
    
  return x;
}

char *read_line(char text[] = "Waiting for input")
{
  int bufferlength = 256;
  char buffer[255];
  int i = 0;
  
  Serial.print(text);
  Serial.println(": ");
  
  for(;;)
  {
    int8_t input = Serial.read();
    if(input == -1)
    {
      // Nothing to see here...
    }
    else
    {
      // We got a value! Process it.
      
      buffer[i+1] = '\0';
      if(input == '\n')
        break;
      
      buffer[i] = input;
      i++;
      
      if(i == bufferlength - 1)
        break; // Buffer full
      
    }
  }
  
  return buffer;
}

//void protect(uint32_t *input, uint32_t *key = &pub.B, boolean mode = 1)
void protect(uint32_t *input, bool mode = 1)
{
  int modulo = modulo;
  pri.s = pri.s;
  uint32_t *key = &pri.s;
  if(mode)
  {
    // Encrypting....
    //*input = (input + key)%256;
    *input = (*input + *key)%modulo;
  }
  else
  {
    // Decrypting....
    ///*input = (input - key)%256;
    *input = (*input - *key)%modulo;
  }
}
void unprotect(uint32_t *input)
{
  protect(input, 0);
}

void print_variable(char name[], uint32_t *var)
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

void print_compare(uint32_t *var1, uint32_t *var2)
{
  Serial.print(*var1, BIN);
  Serial.print("\t");
  Serial.println(*var2, BIN);
}

#endif

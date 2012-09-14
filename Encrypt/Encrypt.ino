
void setup()
{
  // Ini ports
  
  Serial.begin(9600);
  Serial3.begin(9600);
  
}

int16_t key = 100;

void loop()
{
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


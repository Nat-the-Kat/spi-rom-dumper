#include <Arduino.h>
#include <SPI.h>

SPISettings s = SPISettings(10000000,MSBFIRST,SPI_MODE0);

void setup() {
  
  Serial.begin();
  SPI.setRX(4);
  pinMode(5,OUTPUT);
  digitalWrite(5,HIGH);
  SPI.setSCK(2);
  SPI.setTX(3);
  SPI.begin();
  while(!Serial);
  for(int i = 0; i < 16384; i++){
    char buf[260];
    buf[0]= 0x03;
    int top = i & 0xFF00;
    top = top >> 8;
    int bottom = i & 0x00FF;
    buf[1] = top;
    buf[2] = bottom;
    buf[3] = 0;

    digitalWrite(5,LOW);
    SPI.beginTransaction(s);
    SPI.transfer(buf,260);
    SPI.endTransaction();
    digitalWrite(5,HIGH);
    for(int e = 4; e < 260; e++){
      Serial.write(buf[e]);
    }
    delay(10);
    
  }
  Serial.println();Serial.println("done");
  while(true);
}

void loop() {

}



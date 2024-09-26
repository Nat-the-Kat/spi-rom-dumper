#include <Arduino.h>
#include <SPI.h>

SPISettings s = SPISettings(10000000,MSBFIRST,SPI_MODE0);

void setup() {
  
  Serial.begin();
  //rpi pico specific
  SPI.setRX(4);
  SPI.setSCK(2);
  SPI.setTX(3);

  pinMode(5,OUTPUT);
  digitalWrite(5,HIGH);
  SPI.begin();

  //wait for serial to connect
  while(!Serial);

  //4MB flash chip has 16384 pages of 256 bytes
  for(int i = 0; i < 16384; i++){
    char buf[260];
    buf[0]= 0x03;

    //calculate page address
    int top = i & 0xFF00;
    top = top >> 8;
    int bottom = i & 0x00FF;

    buf[1] = top;
    buf[2] = bottom;
    buf[3] = 0;

    //read from flash chip
    digitalWrite(5,LOW);
    SPI.beginTransaction(s);
    SPI.transfer(buf,260);
    SPI.endTransaction();
    digitalWrite(5,HIGH);

    //unload buffer into serial port
    for(int e = 4; e < 260; e++){
      Serial.write(buf[e]);
    }
    //give the serial port a chance to catch up so we don't overfill the buffer
    delay(10);
    
  }
  Serial.println("done");
}

//loop endlessly
void loop() {

}



#include <SoftwareSerial.h>
#define BT_RX 2
#define BT_TX 3

int p = 0;
int q = 0;

SoftwareSerial HM10(BT_RX,BT_TX);  // RX핀(2번)은 HM10의 TX에 연결 
                                   // TX핀(3번)은 HM10의 RX에 연결  
void setup() {  
  Serial.begin(9600);
  HM10.begin(9600);
}

void loop() {

  if (HM10.available()) {
    Serial.write(HM10.read());
  }
  
  if (Serial.available()) {
    HM10.write(Serial.read());
    }

  p = q;
  if((millis()/5) % 1000 == 0)
    {
      q=1;
      if(p == 0 && q == 1)     HM10.write("AT+CONNL");
    }
    else q = 0;

}


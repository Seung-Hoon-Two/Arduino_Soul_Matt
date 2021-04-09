#include <SoftwareSerial.h>

//블루투스모듈 HC-06(슬래이브만가능)으로 진행함 
//블루투스모듈 HC-05(슬래이브 마스터둘다가능)는 조금 코드가 다르다  
//HC-06 시리얼창에서 "line ending 없음" 설정할것

int Tx = 2; //전송 보내는핀  
int Rx = 3; //수신 받는핀

SoftwareSerial BtSerial(Tx,Rx);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("hello");
  BtSerial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BtSerial.available()) {       
    Serial.write(BtSerial.read());
  }
  if (Serial.available()) {         
    BtSerial.write(Serial.read());
  }


}

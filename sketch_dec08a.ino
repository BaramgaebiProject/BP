#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   9     // reset핀 설정
#define SS_PIN    10    // 데이터를 주고받는 역할의 핀( SS = Slave Selector )

MFRC522 mfrc(SS_PIN, RST_PIN);           // 이 코드에서 MFR522를 이용하기 위해 mfrc객체를 생성해 줍니다.

bool turn_on_camera = false;
void setup() {
  Serial.begin(9600);                     // 시리얼 통신, 속도는 9600
  SPI.begin();                             // SPI 초기화(SPI : 하나의 마스터와 다수의 SLAVE(종속적인 역활)간의 통신 방식)
}

void loop() {
  if ( ! mfrc.PICC_IsNewCardPresent() || ! mfrc.PICC_ReadCardSerial() ) {    //  태그 접촉이 되지 않았을때 또는 아이디가 읽혀지지 않았을때
    delay(500);        
    return;                                   // return
  }
    
  if(mfrc.uid.uidByte[0] == 244 && mfrc.uid.uidByte[1] == 181 
       && mfrc.uid.uidByte[2] == 249 && mfrc.uid.uidByte[3] == 233) {    // 2번 태그 ID가 맞을경우
    turn_on_camera = true;
    
  }
  if(mfrc.uid.uidByte[0] == 212 && mfrc.uid.uidByte[1] == 181 
       && mfrc.uid.uidByte[2] == 233 && mfrc.uid.uidByte[3] == 233){
    turn_on_camera = true;
  }  
}

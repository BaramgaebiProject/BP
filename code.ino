#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   9     // reset핀 설정
#define SS_PIN    10    // 데이터를 주고받는 역할의 핀( SS = Slave Selector )

enum Mode{
  SETTING, GOTOUSER, CHECKID, VOTE, TURNOFF;
}
int mode_state = 0;
MFRC522 mfrc(SS_PIN, RST_PIN);           // 이 코드에서 MFR522를 이용하기 위해 mfrc객체를 생성해 줍니다.
bool turn_on_camera = false;
bool get_paper = false;
int tag_id[2][4] = {{1,2,3,4,},{1,3,2,4}};



void sampling(){
  digitalWrite(8,0);
  digitalWrite(9,0);
  delayMicroseconds(2);
  digitalWrite(8,1);
  delayMicroseconds(10);
  digitalWrite(8,0);
  unsigned long duration=pulseIn(9,1);
  float distance=duration/5.8;
  int distint=int(distance);
  Serial.println(distint);
  return distint;
}
void dispenser(){
  digitalWrite(4,0);
  digitalWrite(5,1);
  analogWrite(3,255);
  delay(300);
  digitalWrite(4,0);
  digitalWrite(5,0);
  analogWrite(3,0);
}
void setup() {
  Serial.begin(9600);                     // 시리얼 통신, 속도는 9600
  SPI.begin();                             // SPI 초기화(SPI : 하나의 마스터와 다수의 SLAVE(종속적인 역활)간의 통신 방식)
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT); 
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
}

// CHECKID
void checkSerial(){ // 카드가 들어오면 등록된 tag_id에 있는지 찾아봄
  bool check_tag;
  for(int i = 0; i < 2; i++){ // 등록된 여러 카드 loop
    check_tag = false;
    for(int j = 0; j < 4; j++){
      if(mfrc.uid.uidByte[j] == tag_id[i][j]){  // 검사
      check_tag = true;
      }
      else{
        check_tag = false;  // 등록된 카드가 아님
        break;              // break
      }
    }
    if(check_tag){  // 등록된 카드일 경우
      turn_on_camera = true;
      return;
    }
  }
  return;
}
void CheckTag(){
  while(true){
    Serial.print("Tag your card on the borad");
    Serial.println();
    if(! mfrc.PICC_IsNewCardPresent() || ! mfrc.PICC_ReadCardSerial()){  //  태그 접촉이 되지 않았을때 또는 아이디가 읽혀지지 않았을때
      delay(500);
      continue;
    }
    else{
      checkSerial();
    }
      // 제대로 된 카드 요청
      Serial.print("This card is not registed. Please check your card");
      Serial.println();
      delay(500);
    }
  }
  return;
}
void CheckCamera(){
  if(turn_on_camera){
    // 드론에서 카메라 요청
    // 검사
  }
  return;
}

// VOTE
void dispenser(){
  digitalWrite(4,0);
  digitalWrite(5,1);
  analogWrite(3,255);
  delay(300);
  digitalWrite(4,0);
  digitalWrite(5,0);
  analogWrite(3,0);
  return;
}
void back(){}
void vote(){
  delay(10);
  dispenser();
  while(true){
    // if pin input
    // back()
  }
  delay(10);
  return;
}
      
void loop() {
  switch(mode_state){
    case SETTING:
    case GOTOUSER:
    case CHECKID:
      CheckTag();
      CheckCamera();
      break;
    case VOTE:
      vote();
      break;
    case TURNOFF:
  }  
}

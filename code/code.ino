#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   9     // reset핀 설정
#define SS_PIN    10    // 데이터를 주고받는 역할의 핀( SS = Slave Selector )

string RasPi = "";
bool moving = false;
MFRC522 mfrc(SS_PIN, RST_PIN);           // 이 코드에서 MFR522를 이용하기 위해 mfrc객체를 생성해 줍니다.
int tag_id[2][4] = {{1,2,3,4,},{1,3,2,4}};
int utrSncU;
int utrSncD;
int utrSncF;
int utrSncL;
int utrScnR;


void sampling(){
  digitalWrite(8,0);
  digitalWrite(9,0);
  delayMicroseconds(2);
  digitalWrite(8,1);
  delayMicroseconds(10);
  digitalWrite(8,0);
  unsigned long duration=pulseIn(9,1);
  float distance=duration/5.8;
  int utrSncU=int(distance);
  digitalWrite(6,0);
  digitalWrite(7,0);
  delayMicroseconds(2);
  digitalWrite(6,1);
  delayMicroseconds(10);
  digitalWrite(6,0);
  duration=pulseIn(7,1);
  distance=duration/5.8;
  int utrSncD=int(distance);
  digitalWrite(4,0);
  digitalWrite(5,0);
  delayMicroseconds(2);
  digitalWrite(4,1);
  delayMicroseconds(10);
  digitalWrite(4,0);
  duration=pulseIn(5,1);
  distance=duration/5.8;
  int utrSncF=int(distance);
  digitalWrite(2,0);
  digitalWrite(3,0);
  delayMicroseconds(2);
  digitalWrite(2,1);
  delayMicroseconds(10);
  digitalWrite(2,0);
  duration=pulseIn(3,1);
  distance=duration/5.8;
  int utrSncL=int(distance);
  digitalWrite(10,0);
  digitalWrite(11,0);
  delayMicroseconds(2);
  digitalWrite(10,1);
  delayMicroseconds(10);
  digitalWrite(10,0);
  duration=pulseIn(11,1);
  distance=duration/5.8;
  int utrSncR=int(distance);
  //return utrSncU,utrSncD,utrSncL,utrSncR,utrSncF;
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
      Serial.print('N%d', i);
      delay(100);
      return;
    }
  }
  return;
}
void CheckTag(){
  while(true){
    // Serial.print("Tag your card on the borad");
    // Serial.println();
    if(! mfrc.PICC_IsNewCardPresent() || ! mfrc.PICC_ReadCardSerial()){  //  태그 접촉이 되지 않았을때 또는 아이디가 읽혀지지 않았을때
      delay(500);
      continue;
    }
    else{
      checkSerial();
    }
      // Serial.print("This card is not registed. Please check your card");  // 제대로 된 카드 요청
      // Serial.println();
      delay(500);
  }
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
void inputPaper(){
  digitalWrite(4,1);
  digitalWrite(5,0);
  analogWrite(3,255);
  delay(500);
  digitalWrite(4,0);
  digitalWrite(5,0);
  analogWrite(3,0);
  delay(10);
  return;
}
void Vote(){
  delay(100);
  Serial.print("Pick one");
  Serial.println();
  dispenser();
  while(true){
    delay(10);
    if(){ // 버튼 입력시
      inputPaper();
      Serial.print('N');
      return;
    }
  }
  return;
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
  
void loop() {
  
  if(Serial.available()){
    RasPi = Serial.readStringUntil('\n');
  }
  if(Serial.available() == 0){
    if(RasPi == "CHECKID"){
      moving = false;
      CheckTag();
    }
    if(RasPi == "VOTE"){
      moving = false;
      Vote();
    }
    if(RasPi == "MOVE"){
      moving = true;
    }
  }
  if(moving){
    if(sampling<500){
      Serial.println("stop");
      if(utrSncU<500)
        Serial.println("GoDown");
      if(utrSncD<500)
        Serial.println("GoUp");
      if(utrSncF<500){
        if(utrSncR<500)
          Serial.println("TurnLeft");
        else if(utrSncL<500){
          if(utrSncR<500){
            Serial.println("TurnLeft");
            Serial.println("TurnLeft");
          }
          else{
            Serial.println("TurnRight");
          }
        }
      }
    }
  }
}

int sampling(){
  digitalWrite(8,0);
  digitalWrite(9,0);
  delayMicroseconds(2);
  digitalWrite(8,1);
  delayMicroseconds(10);
  digitalWrite(8,0);
  unsigned long duration=pulseIn(9,1);
  float distance=duration/5.8;
  int distint=int(distance);
  Serial.println(distance);
  return int(distance);
}
void dispenser(){
  digitalWrite(4,0);
  digitalWrite(5,1);
  analogWrite(3,255);
  delay(300);
  digitalWrite(4,0);
  digitalWrite(5,0);
  analogWrite(3,0);
  delay(10);
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
}
void setup(){  
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT); 
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
}
void loop(){
  int distint=sampling();
  delay(10);
  dispenser();
  delay(10);
  inputPaper();
  delay(10);
}

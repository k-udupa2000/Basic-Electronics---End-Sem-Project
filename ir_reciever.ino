#include<IRremote.h>
int recv_pin = 2;
int led1 = 10;
int led2 = 11;
int flag1 = 0;
int flag2 = 0;
int lsb = 4;
int msb = 5;
IRrecv irrecv(recv_pin);
decode_results results;
void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(lsb,OUTPUT);
  pinMode(msb,OUTPUT);
  digitalWrite(lsb,LOW);
  digitalWrite(msb,LOW);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
}

void loop() {
  if (irrecv.decode(&results)) 
  {
    Serial.println(results.value, HEX);
    if(results.value == 0xFF90666 && flag1 == 0){
      digitalWrite(led1,HIGH);
      delay(10);
      flag1 = 1;
      digitalWrite(lsb,HIGH);
      digitalWrite(msb, HIGH);
    }
    else if(results.value == 0xFF90666 && flag1 == 1){
      digitalWrite(led1,LOW);
      flag1 = 0;
      delay(10);
      digitalWrite(lsb,LOW);
      digitalWrite(msb,LOW);
    } 
    else if(results.value == 0xAA990FF && flag2 == 0){
      digitalWrite(led2,HIGH);
      flag2 = 1;
      delay(10);
      digitalWrite(lsb,HIGH);
      digitalWrite(msb,LOW);
    }
    else if(results.value == 0xAA990FF && flag2 == 1){
      digitalWrite(led2,LOW);
      flag2 = 0;
      delay(10);
      digitalWrite(lsb,LOW);
      digitalWrite(msb,HIGH);
    }
    irrecv.resume();
  }
}

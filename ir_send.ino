#include<IRremote.h>
int power_button = 9;
int button = 10;
char buttonState1 = LOW;
char buttonState2 = LOW;
IRsend irsend;
decode_results results;
void setup() {
  Serial.begin(9600);
  pinMode(power_button,INPUT);
  pinMode(button,INPUT);
}

void loop() {
  buttonState1 = digitalRead(power_button);
  buttonState2 = digitalRead(button);
  if(buttonState1 == HIGH){  
    irsend.sendNEC(0xFF90666, 32);
    Serial.println("button1");
  }
  else if(buttonState2 == HIGH){
    irsend.sendNEC(0xAA990FF, 32);
    Serial.println("button2");
  }
  delay(10);
}

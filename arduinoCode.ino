int relay1 = 12;
int relay2 = 11;
int relay3 = 10;
int relay4 = 9;
int ledMotor = 8;
int l1 = 6, l2 = 7;
int power1 = 4;
int power2 = 5;
#include<DS3231.h>
#include<SoftwareSerial.h>
DS3231 rtc(SDA, SCL);
int lightSensorPin = A0;
int analogValue;
String data;
String myTime;
SoftwareSerial recv(3, 2);

void setup()
{
  
  // Setup Serial connection
  Serial.begin(9600);
  recv.begin(9600);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(ledMotor, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(power1, INPUT);
  pinMode(power2, INPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  
  // Initialize the rtc object
  rtc.begin();
  
  //The following lines can be uncommented to set the date and time
  //rtc.setDOW(SATURDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(3, 58, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(26, 9, 2019);   // Set the date to January 1st, 2014
}
int flag = -1;
void loop()
{
  if(digitalRead(power1) == HIGH)
  {
    if(digitalRead(power2) == HIGH)
    {
          digitalWrite(relay1, HIGH);
          digitalWrite(relay2, HIGH);
          digitalWrite(relay3, HIGH);
          digitalWrite(relay4, HIGH);
          while(true)
          {
            if(digitalRead(power1) == LOW)
            {
              if(digitalRead(power2) == LOW)
              {
                 Serial.println("in");
                 break;
              }
             
            }
          }      
    }

  }
  if(digitalRead(power1) == HIGH)
  {
    if(digitalRead(power2) == LOW)
    {
      digitalWrite(relay4, LOW);
    }
  }
   if(digitalRead(power1) == LOW)
  {
    if(digitalRead(power2) == HIGH)
    {
      digitalWrite(relay4, HIGH);
    }
  }  

  // Light sensor section.
  analogValue = analogRead(lightSensorPin);
  if(analogValue > 850)
  {
    digitalWrite(relay1, LOW);
    delay(100);
  }
  else
  {
    digitalWrite(relay1, HIGH);
    delay(100);
  }
  Serial.println(analogValue);
  
  // Bluetooth section
  if(recv.available())
  {
    data = recv.readString();
    if(data.equals("o"))
    {
      motorRun();
    }
    else if(data.equals("a"))
    {
      digitalWrite(relay3, LOW);
    }
    else if(data.equals("d"))
    {
      digitalWrite(relay3, HIGH);
    }
    else
    {
      data.remove(5, 7);
      data.remove(0, 3);
      Serial.println(data);
    flag = 1;  
    }
    
  }


  // Time module section
  myTime = rtc.getTimeStr();
  myTime.remove(5, 7);
  myTime.remove(0, 3);
  //Serial.println(myTime);
  // Precision to minute level.
  if(myTime.equals(data))
  {
    if(flag == 1)
    
    {
      Serial.println("Turn ON");
      if(digitalRead(relay2) == HIGH)
      {
        digitalWrite(relay2, LOW);  
      }
      else
      {
        digitalWrite(relay2, HIGH);  
      }
      flag = -1;
    }
  }
}


void motorRun()
{
  digitalWrite(ledMotor, HIGH);
  digitalWrite(l1, HIGH);
  digitalWrite(l2, LOW);
  delay(4000);
  digitalWrite(l1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(ledMotor, LOW);
}

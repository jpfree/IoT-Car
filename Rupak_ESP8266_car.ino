/*
This code was written by- RUPAK PODDAR on 07 Arpil 2019

Arduino Json library (version 5)-
https://drive.google.com/open?id=1F3zRCSnTMndDP44HhHn3yBQWIsMyjET0

Firebase Arduino Library-
https://drive.google.com/open?id=1XIuJ6dJSZ7-DHwtLfm44CjZKT9JKqqdZ

Arduino Board Manager Link For ESP8266-
http://arduino.esp8266.com/stable/package_esp8266com_index.json

Play Store link to download the android app-
https://play.google.com/store/apps/details?id=com.rupak.IOTcar

Link for YouTube video-
https://www.youtube.com/watch?v=sqHQcd_BgLs

Link for my YouTube channel-
https://www.youtube.com/rupakpoddar
*/

#define m1a 5
#define m1b 4
#define m2a 14
#define m2b 12

int interval = 100;// turn left or right interval

#include<ESP8266WiFi.h>
#include<FirebaseArduino.h>
#define FIREBASE_HOST "YOUR URL"           //Google Firebase URL         
#define FIREBASE_AUTH "YOUR TOKEN"         //Firebase Token
#define WIFI_SSID "YOUR WIFI SSID"         //your WiFi SSID to which your NodeMCU connects
#define WIFI_PASSWORD "YOUR WIFI PASSWORD" //Password of your wifi network 

void setup() 
{
  Serial.begin(115200);

  pinMode(m1a, OUTPUT); //D1  output 1 for motor driver 
  pinMode(m1b, OUTPUT); //D2  output 2 for motor driver
  pinMode(m2a, OUTPUT); //D5  output 3 for motor driver
  pinMode(m2b, OUTPUT); //D6  output 4 for motor driver
  pinMode(13, OUTPUT);  //D7  output for status LED

  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
  digitalWrite(13, LOW);
  
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.setInt("cmd",0); //set initial state of tag to '0'
  
}

void loop() 
{
  if (Firebase.failed()) //if firebase connection is failed
      {
        digitalWrite(m1a, LOW);
        digitalWrite(m1b, LOW);
        digitalWrite(m2a, LOW);
        digitalWrite(m2b, LOW);
        digitalWrite(13, HIGH); //turn ON the status LED
      }
      
  int state = Firebase.getString("cmd").toInt();  //integer to store the value of TAG                                      
  
  if(state == 0)  //stop                                                       
     {
      digitalWrite(m1a, LOW);
      digitalWrite(m1b, LOW);
      digitalWrite(m2a, LOW);
      digitalWrite(m2b, LOW);
    }

   if(state == 1)  //forward motion                                                           
     {
      digitalWrite(m1a, HIGH);
      digitalWrite(m2a, HIGH);
      delay(300);
      digitalWrite(m1a, LOW);
      digitalWrite(m2a, LOW);
    }

   
   if(state == 2)  //backward motion                                                           
     {
      digitalWrite(m1b, HIGH);
      digitalWrite(m2b, HIGH);
      delay(300);
      digitalWrite(m1b, LOW);
      digitalWrite(m2b, LOW);
    }

   
   if(state == 3)//turn left                                                             
     {
      digitalWrite(m1b, HIGH);
      digitalWrite(m2a, HIGH);
      delay(interval);
      digitalWrite(m1b, LOW);
      digitalWrite(m2a, LOW);
      
    }

   
   if(state == 4) //turn right                                                            
     {
      digitalWrite(m1a, HIGH);
      digitalWrite(m2b, HIGH);
      delay(interval);
      digitalWrite(m1a, LOW);
      digitalWrite(m2b, LOW);
    }
    
}
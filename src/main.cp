#include <Arduino.h>

#define FIRMWARE 0.1
//variables


//functions
void requestEvent();
void measure();
void console();
void send();

//debug
bool debug = true;
bool send_all = false;
bool auto_send = true;
bool nitro = false; //For competition always true!!!!

void setup()
{
  Serial.begin(115200);
  for (int i; i < 8; i++)
  {
    pinMode(pEcho[i], INPUT);
    pinMode(pTrig[i], OUTPUT);
  }
  while(!Serial){
    digitalWrite(13,HIGH);
    delay(100);
    digitalWrite(13,LOW);
    delay(100);
    digitalWrite(13,HIGH);
    delay(100);
    digitalWrite(13,LOW);
    delay(300);
  }
  if(!nitro){
    Serial.println("Serial ready.");
    Serial.println("Enter debug?(y/n)");
    while(!Serial.available())
    if(Serial.read()=='y'){
      debug = true;
    }
    Serial.println("Send all data?(y/n)");
    while(!Serial.available())
    if(Serial.read()=='y'){
      send_all = true;
    }
    Serial.println("Turn off autosend?(y/n)");
    while(!Serial.available())
    if(Serial.read()=='y'){
      auto_send = false;
    }
  }else{
    digitalWrite(13,HIGH);
    delay(100);
    digitalWrite(13,LOW);
    delay(100);
    digitalWrite(13,HIGH);
    delay(100);
    digitalWrite(13,LOW);
    delay(100);
    digitalWrite(13,LOW);
    delay(100);
    digitalWrite(13,LOW);
  }
}

void loop()
{
  measure();
  Serial.println();
  if(debug){
    if(Serial.available()){
      console();
    }
    Serial.print("Time:");
    Serial.println(millis());
  }
  if(auto_send){
    send();
  }
}

void measure()
{
  for (int i; i < 8; i++)
  {
    digitalWrite(pTrig[i], LOW);
    delayMicroseconds(2);
    digitalWrite(pTrig[i], HIGH);
    delayMicroseconds(5);
    digitalWrite(pTrig[i], LOW);
    response[i] = pulseIn(pEcho[i], HIGH);
    distance[i] = response[i] / 58.31;
    // if(send_all and auto_send){
    //   Serial.print(i);
    //   Serial.print(": ");
    //   Serial.print(response[i]);
    //   Serial.print(" ; ");
    //   Serial.println(distance[i]);
    // }
    delay(50);
  }
  float max = distance[0];
  byte index = 0;
  for(int i = 1;i<8;i++){
    if(distance[i]<max){
      max = distance[i];
      index = i;
    }
  }
  nearest_distance = max;
  nearest_index = index;
}

void requestEvent()
{
}

void console(){
  String message = Serial.readStringUntil('\n');
  switch(message[0]){
    case 'f':
        Serial.print("Firmware version: ");
        Serial.println(FIRMWARE);
      break;
    case 'a':
        send_all = !send_all;
      break;
    case 's':
        auto_send = !auto_send;
      break;
    case 'n':
        send();
      break;
  }
}

void send(){
  if(send_all){
    for(int i=0;i<8;i++){
        Serial.print(i);
        Serial.print(": ");
        Serial.print(response[i]);
        Serial.print(" ; ");
        Serial.println(distance[i]);
    }
  }
  Serial.print(nearest_index);
  Serial.print(": ");
  Serial.println(nearest_distance);
}
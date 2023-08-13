#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

// defines variables for ultraSonic sensors
const int echoPin = 10; // attach pin D3 Arduino to pin Echo of HC-SR04
const int trigPin = 7; //attach pin D2 Arduino to pin Trig of HC-SR04
const int echoPin01 = 9; 
const int trigPin01 = 13;
//Variables for distance measurement
long distance, distance01; // variable for the distance measurement
//Variable for buzzer
const int Buzzer = 8;
//Variables for LED
// const int ledRed = 7;
// const int ledGreen = 8;
//Variables for Potentiometer
const int pot1 = A0;
const int pot2 = A1;
//Variables for LCD display
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin01, OUTPUT); 
  pinMode(echoPin01, INPUT); 
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  // pinMode(ledRed, OUTPUT);
  // pinMode(ledGreen, OUTPUT);
  pinMode(pot1, INPUT);
  pinMode(pot2, INPUT);
  pinMode(Buzzer, OUTPUT);
  // // set up the LCD's number of columns and rows:
  // lcd.begin(16, 2);

  // Serial Communication with NodeMCU and ultrasonic sensors
  Serial.begin(9600);

  delay(1000);
}


void loop() {
  //1st Sensor distance calculation
  distance = calcDist(trigPin,echoPin);
  //Serial.println(String(distance));

  //2nd Sensor distance calculation
  distance01 = calcDist(trigPin01,echoPin01);
  //Serial.println(String(distance01));
  
  int correctDist = analogRead(pot1);
  //Serial.println(String(correctDist)); //print correct distance in serial monitor

  int valueDelay = analogRead(pot2);
  int delaySec = valueDelay*1000;
  //Serial.println(String(valueDelay)); //print delay in serial monitor

    // Create a JSON object
  StaticJsonDocument<200> jsonDoc;

  // Add data to the JSON object
  jsonDoc["TopDistance"] = distance;
  jsonDoc["BottomDistance"] = distance01;
  jsonDoc["SetDistance"] = correctDist;
  jsonDoc["Delay"] = valueDelay;

  // Serialize the JSON object to a string
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Send the JSON string over Serial
  Serial.println(jsonString);

  // noTone(Buzzer);
  if(distance > correctDist || distance01 > correctDist) {

    delay(delaySec);
    tone(Buzzer,500);
    // digitalWrite(ledRed, HIGH);
    // digitalWrite(ledGreen, LOW);
    // lcd.print("Wrong posture!!");

  } else if(distance <= correctDist && distance01 <= correctDist){
    // int valueDelay = analogRead(pot2);
    // int delaySec = valueDelay*1000;
    delay(1000);
    noTone(Buzzer);
    // digitalWrite(ledGreen, HIGH);
    // digitalWrite(ledRed, LOW);
    //lcd.print("Correct posture!!");
  }

  delay(1000);
}


long calcDist(int trigPin, int echoPin) {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // At Trig pin we need to give a pulse of 10 microsecond to produce ultrasonic waves    
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  long distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  return distance;
}

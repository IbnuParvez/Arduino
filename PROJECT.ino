#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

//Configuration
LiquidCrystal_I2C lcd(0x27, 16, 2); 
SoftwareSerial btSerial(0, 1); // RX, TX (Connect BT TX to Pin 0, BT RX to Pin 1)

const int trigPin = 9; //pin 9 on the board
const int echoPin = 10; //pin 10 on the board
const int buzzerPin = 11; //pin 11 on the board

long duration;
int distance;
String incomingMessage = "Waiting for msg"; // Default text for LCD bottom row

// Timer variables to prevent flooding the phone with data
unsigned long previousMillis = 0;
const long interval = 1000; // Send data to phone every 1000ms (1 second)

void setup() {
  btSerial.begin(9600);//initialize ultrasonic sensor 
  btSerial.setTimeout(50); // Keep bluetooth reading fast

  lcd.init();
  lcd.backlight();
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("System Active");
  delay(1000);
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis();

  //SENSOR MEASUREMENT
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  //BUZZER SAFETY CHECK
  // If closer than 50cm, turn on buzzer
  if (distance > 0 && distance < 50) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  // --- 3. LCD UPDATES ---
  // Line 0: Distance
  lcd.setCursor(0, 0); 
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm   "); 

  // Line 1: Messages FROM your phone
  if (btSerial.available() > 0) {
    String received = btSerial.readString();
    received.trim();
    if (received.length() > 0) {
      incomingMessage = received;
      lcd.setCursor(0, 1);
      lcd.print("                "); // Clear line
    }
  }
  lcd.setCursor(0, 1);
  lcd.print(incomingMessage);

  //SEND DATA TO PHONE
  // We use a timer here so we don't spam the phone 10 times a second
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    btSerial.print("Distance: ");
    btSerial.print(distance);
    btSerial.println(" cm");
    
    // If danger, add a warning tag
    if (distance < 50) {
      btSerial.println("!!! WARNING !!!"); 
    }
  }
  
  delay(100); // Short delay for loop stability
}
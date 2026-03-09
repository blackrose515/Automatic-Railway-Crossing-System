#include <Servo.h>
Servo gateServo;

// Define sensor pins
int sensor1 = 6;  // Entry sensor 1
int sensor2 = 7;  // Entry sensor 2
int sensor3 = 8;  // Exit sensor
int servoPin = 9; // Servo motor pin
int redled=12;
int greenled=13;
#include <LiquidCrystal.h>
// LCD pins: rs, en, d4, d5, d6, d7
LiquidCrystal lcd(11, 10, 5, 4, 3, 2);

// Parameters
float distanceBetweenSensors = 0.05;  // 5 cm = 0.05 m
float distanceToGate = 0.15;          // 15 cm = 0.15 m
float gateCloseTime = 2.0;            // Gate takes 2 seconds to close
unsigned long t1 = 0, t2 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(greenled,OUTPUT);
  pinMode(redled,OUTPUT);
  lcd.begin(16, 2);

  // Show initial message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gate is Open");
  delay(5000);   

  gateServo.attach(servoPin);
  gateServo.write(0); // Gate open position
  delay(2000);
  gateServo.write(90);
  delay(2000);
  Serial.println("Automatic Railway Crossing Ready");
}

void loop() {
  // Wait for train detection at Sensor 1
  if (digitalRead(sensor1) == LOW) {
    Serial.println("Train detected at Sensor 1");
    t1 = micros();

    // Wait for train to reach Sensor 2
    while (digitalRead(sensor2) == HIGH);
    t2 = micros();
    Serial.println("Train detected at Sensor 2");

    // Calculate time difference and speed
    float timeTaken = (t2 - t1) / 1000000.0; // Convert to seconds
    float speed = distanceBetweenSensors / timeTaken; // m/s
    Serial.print("Train Speed: ");
    Serial.print(speed, 3);
    Serial.println(" m/s");

    // Calculate delay before closing gate based on speed
    float timeToGate = distanceToGate / speed;
    float safetyMargin;

    if (speed > 1.0) safetyMargin = 0.2;      // Very fast train
    else if (speed > 0.6) safetyMargin = 0.5; // Medium speed
    else safetyMargin = 1.0;                  // Slow train

    float closeDelay = timeToGate - gateCloseTime - safetyMargin;
    if (closeDelay < 0) closeDelay = 0;

    Serial.print("Gate will close in ");
    Serial.print(closeDelay);
    Serial.println(" seconds");

    delay(closeDelay * 1000);
    closeGate();

    // Wait until train passes output sensor
    Serial.println("Waiting for train to pass output sensor...");
    while (digitalRead(sensor3) == HIGH);  // Wait till train reaches output sensor
    Serial.println("Train detected at output sensor");

    while (digitalRead(sensor3) == LOW); // Wait till train leaves
    delay(1000); // Small delay after passing
    openGate();
  }
}

void closeGate() {
  Serial.println("Closing gate...");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gate is Closing");
  digitalWrite(greenled,LOW);
  digitalWrite(redled,HIGH);
  //for (int pos = 0; pos <= 90; pos++) {
   // gateServo.write(pos);
   // delay(15);
 // }
 gateServo.write(90);
  Serial.println("Gate closed.");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gate is Closed");
  
}

void openGate() {
  digitalWrite(greenled,HIGH);
  digitalWrite(redled,LOW);
  Serial.println("Opening gate...");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gate is Opening");
 // for (int pos = 90; pos >= 0; pos--) {
   // gateServo.write(pos);
    //delay(15);
  //}
  gateServo.write(0);
  Serial.println("Gate opened.");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gate is Opened");
}

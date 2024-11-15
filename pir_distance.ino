#include <NanitLib.h>

byte pir = P9_3;
byte triggerPin = P5_1;
byte echoPin = P5_4;
volatile bool isInterruptedState = false;

void setup() {
  Nanit_Base_Start();
  Serial.begin(9600);
  pinMode(pir, INPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(pir), pirISR, RISING);
}

void loop() {
  if(isInterruptedState == true) {
    Serial.println("Motion detected");
    Serial.print("The distance to the motion object is ");
    Serial.println(String(measureDistance()) + " cm.");
  }
  isInterruptedState = false;
  delay(500);

}

volatile int measureDistance() {
  digitalWrite(triggerPin, 1);
  delayMicroseconds(10);
  digitalWrite(triggerPin, 0);

  return pulseIn(echoPin, 1) / 58;
}

void pirISR(){
  isInterruptedState = true;
}
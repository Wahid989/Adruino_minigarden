#include "Adafruit_seesaw.h"

Adafruit_seesaw ss;
int pumpPin = 13;
int photoPin = 0;
float photoRead;
int LEDpin = 8;
float ledBrightness;

void setup() {
  // pinMode(11, OUTPUT);
  pinMode(A3, INPUT);
  Serial.begin(115200);
  pinMode(8, OUTPUT);
  pinMode(A0, INPUT);

  Serial.println("seesaw Soil Sensor example!");
 
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }
}

void loop() {
  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);
  photoRead = analogRead(photoPin);

  Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
  Serial.print("Capacitive: "); Serial.println(capread);
  Serial.print("Photocell Reading: ");
  Serial.println(photoRead);

  if (photoRead*17 > 1023) {
    photoRead = 1;
  }
  else{
    photoRead = 1023 - (photoRead*17);
  }
  Serial.print("New Photocell reading: ");
  Serial.println(photoRead);
  ledBrightness = (1/((1/photoRead)*255))*40;

   
  if (photoRead > 300) {
    ledBrightness = 250;   
  }
  Serial.print("LED brightness: ");
  Serial.println(ledBrightness);
  analogWrite(LEDpin, ledBrightness); 
  delay(500);
 
  if (capread > 500) {
    Serial.print("Motor on");
    analogWrite(A3, 200);
    // digitalWrite(11, HIGH);
    delay(1000);
   
    // digitalWrite(11, LOW);
    analogWrite(A3, 0);
    delay(2000);
    Serial.begin(115200);      
  } else {
    Serial.print("Motor off");
    analogWrite(A3, 0);
    //Serial.begin(115200);
    // digitalWrite(11, LOW);
  }

} 
}
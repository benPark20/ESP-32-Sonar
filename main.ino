// Now turn this trash into treasure!
#include <Servo.h>

Servo servo;

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

Adafruit_SSD1306 display(128, 64);

#define TRIGGER_PIN 3
#define ECHO_PIN 2
#define MAX_DISTANCE 400

#include <NewPing.h>

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

float distance;

#define ENCODER_CLK 7
#define ENCODER_DT  6
int value;

#define BUZZER_PIN 27

void setup() {
  Serial.begin(115200);
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  servo.attach(0);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(F("Booting..."));
  display.display();
  delay(2000);
  display.setCursor(0, 20);
  display.println(F("Done!"));
  display.display();
}

int lastClk = HIGH;

void loop() {
  float val;
  int lastDistance;
  distance = sonar.ping();
  int distanceInt = static_cast<int>(round(distance/10));
  if (distanceInt != lastDistance){
    display.clearDisplay();
    display.display();
    display.setTextSize(3);
    display.setCursor(3, 7);
    display.print(distanceInt);
    display.println("cm");
    display.display();
    lastDistance = distanceInt;
  }


  int newClk = digitalRead(ENCODER_CLK);
  if (newClk != lastClk) {
    lastClk = newClk;
    int dtValue = digitalRead(ENCODER_DT);
    if (newClk == LOW && dtValue == HIGH) {
      value += 15;
      if(value > 180){
        value = 180;
      }
    }
    if (newClk == LOW && dtValue == LOW) {
      value -= 15;
      if(value < 0){
        value = 0;
      }
    }
  }
  servo.write(value);


  static unsigned long LastTime;
  if (distance > 0 && distance < 50)
  { if (millis() - LastTime < 10000) {
      tone(BUZZER_PIN, 262, 250);
    }
  } else {
    LastTime = millis();
  }
}

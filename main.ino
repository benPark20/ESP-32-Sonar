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

void setup() {
  Serial.begin(115200);
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  servo.attach(0)

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
  distance = sonar.ping() / 10.00;



  int newClk = digitalRead(ENCODER_CLK);
  if (newClk != lastClk) {
      val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
      myservo.write(val);   
    lastClk = newClk;
    int dtValue = digitalRead(ENCODER_DT);
    if (newClk == LOW && dtValue == HIGH) {
      // turn right
    }
    if (newClk == LOW && dtValue == LOW) {
      //turn left
    }
  }
}

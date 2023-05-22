#pragma once
#include <Arduino.h>
#include <Ultrasonic.h>

#define LED_F 2 // led forward
#define LED_R 3 // led reverse
#define BTN 4   // button
#define IN_1 5  // input 1
#define IN_2 6  // input 2
#define ECHO 8  // sonar echo
#define TRIG 9  // sonar trig

#define BTN_DELAY 100 // delay to wait for button
#define DEBUG // For debug purpose, comment if not needed

#ifdef DEBUG
  #define PRINTLN(x) Serial.println(x)
  #define PRINT(x) Serial.print(x)
#else
  #define PRINTLN(x)
  #define PRINT(x)
#endif

namespace var_4 {
  void setup();
  void loop();
  void configure_leds();
  void configure_motor();
}

Ultrasonic sonar(TRIG, ECHO);
bool was_pressed = LOW;
bool straight = false;

byte speed = 0;
uint32_t btn_timer = 0, rot_time = 0, rot_start = 0;

struct mode {
  const uint32_t time;
  const byte speed;
}
m0 = { 0, 0 },
m1 = { 3000, 255 },
m2 = { 4000, 128 },
m3 = { 5000, 64 };

void var_4::setup() {

  #ifdef DEBUG
    Serial.begin(9600);
    Serial.setTimeout(15);
  #endif

  pinMode(LED_F, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BTN, INPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);

  configure_leds();
}

void var_4::loop() {
  uint16_t distance = sonar.read();
  
  if (speed == 0) {
    // motor is not spinning
    if (distance < 10) {
      speed = 255;
      rot_time = 3000;
    } else if (distance < 20) {
      speed = 128;
      rot_time = 4000;
    } else if (distance < 30) {
      speed = 64;
      rot_time = 5000;
    } else {
      speed = 0;
      rot_time = 0;
    }
    
    if (speed != 0) 
      // start spinning, save start time
      rot_start = millis();
  }

  if (millis() - rot_start > rot_time)
    speed = 0;
  configure_motor();

  bool pressed = digitalRead(BTN);
  if (!pressed && was_pressed && millis() - btn_timer > BTN_DELAY) {
    straight = !straight;
    btn_timer = millis();
    configure_leds();
    PRINTLN("Pressed");
  }
  was_pressed = pressed;
}

void var_4::configure_leds() {
  digitalWrite(LED_F, straight);
  digitalWrite(LED_R, !straight);
}

void var_4::configure_motor() {
  analogWrite(IN_1, speed * straight);
  analogWrite(IN_2, speed * !straight);
}
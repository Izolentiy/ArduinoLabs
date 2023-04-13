#pragma once
#include <Arduino.h>

#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11

#define POT_PIN A0
#define DEBUG  // Разкомментировать для включения режима отладки

#ifdef DEBUG
  #define PRINTLN(x) Serial.println(x)
  #define PRINT(x) Serial.print(x)
#else
  #define PRINTLN(x)
  #define PRINT(x)
#endif

namespace rgb_led {
  void setup();
  void loop();
}

uint8_t r, g, b;

void process_signal(uint8_t val) {
  if (val < 85) {
    r = (85 - val) * 3;
    g = val * 3;
    b = 0;
  } else if (val < 170) {
    r = 0;
    g = (170 - val) * 3;;
    b = (val - 85) * 3;
  } else {
    r = (val - 170) * 3;
    g = 0;
    b = (255 - val) * 3;
  }
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);

  PRINT(val); PRINT("  ");
  PRINT(r); PRINT(' ');
  PRINT(g); PRINT(' ');
  PRINT(b); PRINT('\n');
}

void rgb_led::setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);

#ifdef DEBUG
  Serial.begin(9600);
#endif
}

void rgb_led::loop() {
  uint8_t pot_val = analogRead(POT_PIN) >> 2; // ~ pot_val / 4 (но быстрее)
  process_signal(pot_val);
}


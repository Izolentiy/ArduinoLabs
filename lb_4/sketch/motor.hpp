#pragma once
#include <Arduino.h>

#define BTN_PIN 2
#define MOTOR_PIN_1 3
#define MOTOR_PIN_2 4
#define BTN_WAIT 200

namespace motor {
  void setup();
  void loop();
}

uint32_t btn_timer = 0;
bool was_pressed = false;

byte state = 0;

enum motor_state {
  stop = 0,
  reversed = 1,
  straight = 2
};

void configure_motors(bool in_1, bool in_2) {
  digitalWrite(MOTOR_PIN_1, in_1);
  digitalWrite(MOTOR_PIN_2, in_2);
}

void set_rotation(byte direction) {
  switch(direction) {
  case stop: configure_motors(0, 0); break;
  case straight: configure_motors(1, 0); break;
  case reversed: configure_motors(0, 1); break;
  default: state = 0; configure_motors(0, 0);
  }
}

void motor::setup() {
  pinMode(BTN_PIN, INPUT);
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  set_rotation(state);
  Serial.begin(9600);
}

void motor::loop() {
  bool btn_pressed = digitalRead(BTN_PIN);
  if (millis() - btn_timer > BTN_WAIT && btn_pressed && !was_pressed) {
    set_rotation(++state);
    btn_timer = millis();
  }
  was_pressed = btn_pressed;
}
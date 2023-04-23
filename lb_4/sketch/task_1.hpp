#pragma once
#include <Arduino.h>
#include "serial_utils.hpp"

#define RELAY_PIN_1 4
#define RELAY_PIN_2 5

#define ASCII_0 48
#define ASCII_1 49
#define ASCII_2 50

namespace task_1 {
  void setup();
  void loop();
}

void configure_motors(bool in_1, bool in_2) {
  digitalWrite(RELAY_PIN_1, in_1);
  digitalWrite(RELAY_PIN_2, in_2);
}

void task_1::setup() {
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  configure_motors(0, 0);
  Serial.setTimeout(25);
  Serial.begin(9600);
}

void task_1::loop() {
  if (Serial.available()) {
    switch(read_first_byte()) {
    case ASCII_0: configure_motors(0, 0); break;
    case ASCII_1: configure_motors(1, 0); break;
    case ASCII_2: configure_motors(0, 1); break;
    default: Serial.println("Incorrect input");
    }
  }
}
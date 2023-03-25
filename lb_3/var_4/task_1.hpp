#ifndef TASK_1_HPP
#define TASK_1_HPP

#include <Arduino.h>
#include "serial_utils.hpp"

#define ASCII_1 49
#define ASCII_0 48
#define LED_COUNT 5
#define TIMEOUT 50

namespace task_1 {
  void set_strip_state(bool state);
  void setup();
  void loop();
}

// Массив пинов к которым подключены светодиоды ленты
const byte led_arr[LED_COUNT] = {3, 4, 5, 6, 7};

void task_1::set_strip_state(bool state) {
  for (byte i = 0; i < LED_COUNT; ++i) {
    digitalWrite(led_arr[i], state);
  }
}

void task_1::setup() {
  Serial.begin(9600);  // Открытие последовательного порта
  Serial.setTimeout(TIMEOUT);  // Установка времени ожидания порта
  for (byte i = 0; i < LED_COUNT; ++i) {
    pinMode(led_arr[i], OUTPUT);
  }
}

void task_1::loop() {
  if (Serial.available()) { 
    // При выполнении условия гарантируется, что в буфере есть хотя 
    // бы один байт, поэтому read_first_byte() вернет корректный байт
    byte symbol = read_first_byte();
    // byte symbol = read_last_byte();
    // byte symbol = Serial.read();
    
    switch (symbol) {
    case ASCII_0:
      set_strip_state(LOW);
      break;
    case ASCII_1:
      set_strip_state(HIGH);
      break;
    default:
      Serial.println("Wrong signal");
      break;
    }
  }
}

#endif
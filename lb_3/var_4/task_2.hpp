#pragma once
#include <Arduino.h>
#include <Ultrasonic.h>

#define BTN_TIME 75

#define BTN_PIN 4
#define TRIG_PIN 3
#define ECHO_PIN 2

namespace task_2 {
  void setup();
  void loop();
}

Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

uint16_t distance;
uint32_t btn_timer;
bool prev = LOW;

void task_2::setup() {
  Serial.begin(9600);  // Открытие последовательного порта
  Serial.setTimeout(50);  // Установка времени ожидания порта
  pinMode(BTN_PIN, INPUT);
}

void task_2::loop() {
  bool btn_pressed = digitalRead(BTN_PIN);

  if (btn_pressed && prev == LOW && millis() - btn_timer > BTN_TIME) {
    distance = ultrasonic.read();
    Serial.println(String(distance) + " CM");

    btn_timer = millis();
  }
  
  prev = btn_pressed;
}
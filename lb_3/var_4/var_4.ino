#include "task_1.hpp"
#include "task_2.hpp"

void setup() {
  Serial.begin(9600);  // Открытие последовательного порта
  Serial.setTimeout(50);  // Установка времени ожидания порта
  // task_1_setup();
  task_2_setup();
}

void loop() {
  // task_1_loop();
  task_2_loop();
}
#pragma once
#include <Arduino.h>

/**
 * Чтение из буфера с учетом таймаута
 */
int16_t timedRead() {
  uint32_t start_millis = millis();
  do {
    int16_t b = Serial.read();
    if (b >= 0) return b;
  } while (millis() - start_millis < Serial.getTimeout());
  return -1; // Время ожидания истекло
}

/**
 * Чтение только самого первого байта из буфера остальные отбрасываются
 */
int16_t read_first_byte() {
  int16_t first_byte = timedRead();
  if (first_byte < 0) return -1; // Пустой буфер
  while (timedRead() >= 0);
  return first_byte;
}

/**
 * Чтение только самого последнего байта из буфера остальные отбрасываются
 */
int16_t read_last_byte() {
  int16_t last_byte, temp = timedRead();
  if (temp < 0) return -1; // Пустой буфер
  while (temp >= 0) {
    last_byte = temp;
    temp = timedRead();
  }
  return last_byte;
}
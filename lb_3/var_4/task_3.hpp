#include <Arduino.h>
#include "serial_utils.hpp"

#define ASCII_1 49
#define ASCII_2 50
#define ASCII_3 51

#define LED_COUNT 3
#define REFRESH_RATE 5

namespace task_3 {
  void setup();
  void loop();
}

namespace mode {
  void flickering();
  void running();
  void discrete();
}

const byte leds[LED_COUNT] = {};
uint32_t led_timer = 0;

typedef void (*mode_t)();
mode_t modes[] = { mode::flickering, mode::running, mode::discrete };

enum strip_mode { flickering = 0, running = 1, discrete = 2 };
strip_mode cur_mode = flickering;

void task_3::setup() {
  Serial.begin(9600);
  Serial.setTimeout(25);

  for (byte i = 0; i < LED_COUNT; ++i) {
    pinMode(leds[i], OUTPUT);
  }
}

void task_3::loop() {
  if (Serial.available()) {
    switch(read_first_byte()) {
    case ASCII_1: cur_mode = flickering; break;
    case ASCII_2: cur_mode = running; break;
    case ASCII_3: cur_mode = discrete; break;
    default: Serial.println("Incorrect input");
    }
  }
  modes[cur_mode](); // запуск в заданном режиме
}

/**
 * Неблокирующая реализация режима "Мерцание"
 */
void mode::flickering() {
  static byte i, desc;
  if (millis() - led_timer > REFRESH_RATE) {
    if (i == 255) desc = true;
    else if (i == 0) desc = false;
    if (desc) --i; else ++i;

    for (byte j = 0; j < LED_COUNT; ++j)
      analogWrite(leds[j], i);
  }
}

/**
 * Неблокирующая реализация режима "Бегущее мерцание"
 */
void mode::running() {
  static byte i, desc;
  if (millis() - led_timer > REFRESH_RATE) {
    if (i == 255) desc = true;
    else if (i == 0) desc = false;
    if (desc) --i; else ++i;

    for (byte j = 0; j < LED_COUNT; ++j)
      analogWrite(leds[j], i + j*10);
  }
}

/**
 * Неблокирующая реализация режима "Дискретный"
 */
void mode::discrete() {
  static byte i;
  if (millis() - led_timer > REFRESH_RATE)
    if (i < LED_COUNT-1) ++i;
    else i = 0;
    for (byte j = 0; j < LED_COUNT; ++j) {
      if (j != i)
        analogWrite(leds[j], 0);
      else
        analogWrite(leds[j], 255);
    }
}
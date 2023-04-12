
// Дополнительное задание
// Упралвлять углом поворота сервоприда с помощью двух потенциометров

#pragma once
#include <Arduino.h>
#include <Servo.h>

#define SERVO_PIN 3
#define POT_1_PIN 0
#define POT_2_PIN 1


namespace task_add {
    void setup();
    void loop();
}

Servo servo;

void task_add::setup() {
    servo.attach(SERVO_PIN);
    pinMode(POT_1_PIN, INPUT);
    pinMode(POT_2_PIN, INPUT);
    servo.write(0);
}

void task_add::loop() {
    uint16_t analog_data = analogRead(POT_1_PIN) + analogRead(POT_2_PIN);
    uint8_t angle = map(analog_data, 0, 2046, 0, 180);
    servo.write(angle);

    // Serial.println(angle);
}


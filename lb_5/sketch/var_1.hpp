#pragma once

#include <Arduino.h>
#include "Ultrasonic.h"

// #define LED_OK 4
// #define LED_ER 7
// #define IN_1 11
// #define IN_2 5
// #define EN_A 6
// #define BTN_RV 2
// #define BTN_SP 3
// #define TRIG 9
// #define ECHO 10

#define LED_OK 4
#define LED_ER 7
#define EN_A 11
#define IN_1 12
#define IN_2 13
#define BTN_RV 2
#define BTN_SP 3
#define TRIG 9
#define ECHO 10

Ultrasonic sonar(TRIG, ECHO); // наш сонар
bool increasing = true;       // флаг направления изменения скорости
bool direction = true;        // флаг направления вращения
bool ok = true;               // все ли в порядке
int speed = 0;                // скорость
int distance = 0;             // расстояние

bool brv_pressed = false;
bool bsp_pressed = false;

void setup()
{
    pinMode(LED_OK, OUTPUT);
    pinMode(LED_ER, OUTPUT);
    pinMode(BTN_RV, INPUT);
    pinMode(BTN_SP, INPUT);
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    pinMode(EN_A, OUTPUT);
}

void loop()
{
    distance = sonar.read(); // считываем дистацнию
    ok = distance > 10;
    digitalWrite(LED_ER, !ok);
    digitalWrite(LED_OK, ok);

    if (ok)
    {
        analogWrite(EN_A, speed);
        digitalWrite(IN_1, direction);
        digitalWrite(IN_2, !direction);
    }
    else analogWrite(EN_A, 0);
    
    if (digitalRead(BTN_RV))
    {
        if (!brv_pressed)
        {
            // нажатие на кнопку реверса
            delay(75);
            direction = !direction;
        }
        brv_pressed = true;
    }
    else brv_pressed = false;
    
    if (digitalRead(BTN_SP))
    {
        if (!bsp_pressed)
        {
            // нажатие на кнопку скорости
            delay(75);
            if (increasing)
            {
                if (speed += 5 > 255)
                {
                    speed = 255;
                }
            }
            else
            {
                if (speed -= 5 < 0)
                {
                    speed = 0;
                }
            }
        }
        bsp_pressed = true;
    }
    else bsp_pressed = false;
}
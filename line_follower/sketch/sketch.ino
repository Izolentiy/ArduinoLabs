#include "Arduino.h"
#define IN_A0 A3
#define IN_D0 8

void setup() {
    pinMode(IN_A0, INPUT);
    pinMode(IN_D0, INPUT);
    Serial.setTimeout(50);
    Serial.begin(9600);
}

bool dval;
int aval;

void loop() {
    dval = digitalRead(IN_D0);
    aval = analogRead(IN_A0);
    // Serial.print("Digit val: ");
    // Serial.println(dval);
    Serial.print("Analog val: ");
    Serial.println(aval);
}

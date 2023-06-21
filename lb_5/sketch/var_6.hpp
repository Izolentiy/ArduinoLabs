#include <Ultrasonic.h>
#define led 10 // шим
#define but1 2
#define but2 3
#define motorPin1 8 // шим
#define motorPin2 9 // шим

Ultrasonic glaza(12, 13);
int n = 1, f = 2, k = 3;
int distance = 0, motorSpeed = 0, timeWork = 0;
uint32_t sT = 0; // start time
bool flag_1 = 1, flag_2 = 1;
bool reverse = 0;

void setupMotor() {
    analogWrite(motorPin1, motorSpeed * reverse);
    analogWrite(motorPin2, motorSpeed * !reverse);
}

void setup()
{
    Serial.begin(9600);
    pinMode(led, OUTPUT);
    pinMode(but1, INPUT);
    pinMode(but2, INPUT);
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
}

void loop()
{
    // как минимум 3 символа есть в буфере порта
    if (Serial.available() >= 3)
    {
        // предполагается, что пользователь отправляет только цифры
        n = Serial.read() - '0';
        k = Serial.read() - '0';
        f = Serial.read() - '0';
    }
    distance = glaza.read();

    // вращается ли наш мотор
    if (motorSpeed == 0)
    {
        if (distance <= 10)
        {
            motorSpeed = 255;
            timeWork = n;
        }
        else if (distance < 20)
        {
            motorSpeed = 128;
            timeWork = k;
        }
        else if (distance < 30)
        {
            motorSpeed = 64;
            timeWork = f;
        }
        sT = millis(); // сохраняем момент начала вращения
    }

    if (millis() - sT > timeWork * 1000) {
        motorSpeed = 0;
        timeWork = 0;
    }
    setupMotor();
    analogWrite(led, motorSpeed);

    if (digitalRead(but1) == 1 && flag_1 == 1)
    {
        delay(100);
        flag_1 = 0;
        reverse = !reverse;
    }
    if (digitalRead(but1) == 0)
    {
        flag_1 = 1;
    }

    if (digitalRead(but2) == 1 && flag_2 == 1)
    {
        delay(100);
        flag_2 = 0;
        ++timeWork;
    }
    if (digitalRead(but2) == 0)
    {
        flag_2 = 1;
    }
}

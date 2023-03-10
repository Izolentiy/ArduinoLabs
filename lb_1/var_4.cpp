/**
 * Задание:
 * Осуществить управление светодиодами с помощью одной кнопки:
 * изначально все светодиоды горят, при первом нажатии должны погаснуть 1 и
 * 6 светодиоды, при втором нажатии должны погаснуть 2 и 5 светодиоды, затем
 * 3 и 4. После того, как все светодиоды погаснут, они должны все загореться
 * после нажатия кнопки. Светодиоды должны быть подключены в в один ряд.
*/

#define BTN 8

#define LED_1 2
#define LED_2 3
#define LED_3 4
#define LED_4 5
#define LED_5 6
#define LED_6 7

#define LED_COUNT 6

byte pins[LED_COUNT] = {LED_1, LED_2, LED_3, LED_4, LED_5, LED_6};
bool prev = LOW;

byte pair = 0;
bool flag = false;

void setup() {
    pinMode(BTN, INPUT);

    for (byte i = 0; i < LED_COUNT; i++) {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], HIGH);
    }
    
}

void loop() {
    if (digitalRead(BTN) == HIGH && prev == LOW) {
        prev = HIGH;
        delay(50);
    }
    if (digitalRead(BTN) == LOW && prev == HIGH) {
        prev = LOW;
        delay(50);

        // Основное задание по варианту
        if (pair < 3) {
            for (byte i = 0; i < LED_COUNT / 2; i++) {
                digitalWrite(pins[i], LOW);
                digitalWrite(pins[LED_COUNT - 1 - i], LOW);
            }
            pair++;
        } else {
            for (byte i = 0; i < LED_COUNT; i++) {
                digitalWrite(pins[i], HIGH);
            }
            pair = 0;
        }

        // Дополнительное задание от преподавателя
        // При нажатии на кнопку загораются 1, 2, 4 светодиоды
        // При повторном нажатии они отключаются и загораются 6, 5, 3
        
        digitalWrite(pins[0], flag);
        digitalWrite(pins[1], flag);
        digitalWrite(pins[3], flag);

        digitalWrite(pins[5], !flag);
        digitalWrite(pins[4], !flag);
        digitalWrite(pins[2], !flag);

        flag = !flag;
        
    }
}
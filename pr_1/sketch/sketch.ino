#define BTN 5

#define IMP_LEN 100
#define BTN_DELAY 100

#define DEBUG // debug purpose

#ifdef DEBUG
#define PRINT(x) Serial.print(x)
#define PRINTLN(x) Serial.println(x)
#else
#define PRINT(x)
#define PRINTLN(x)
#endif

uint32_t b_timer = 0, l_timer = 0;  // button/led timer
uint16_t pers[] = {500, 3333, 200}; // periods
uint8_t leds[] = {2, 3, 4};         // led pins
uint8_t cur_led = 0, cur_per = 0;   // current led/period
bool was_pressed = false;

void setup()
{
    for (byte i = 0; i < 3; ++i)
    {
        pinMode(leds[i], OUTPUT);
    }
    pinMode(BTN, INPUT);
#ifdef DEBUG
    Serial.begin(9600);
    Serial.setTimeout(25);
#endif
}

void loop()
{
    bool pressed = digitalRead(BTN);
    uint32_t b_elapsed = millis() - b_timer;
    uint32_t l_elapsed = millis() - l_timer;

    if (pressed && !was_pressed && b_elapsed > BTN_DELAY)
    {
        b_timer = millis();
    }
    if (!pressed && was_pressed && b_elapsed > BTN_DELAY)
    {
        if (b_elapsed < 1000)
        {
            // less than 1 second
            cur_led = (cur_led + 1) % 3;
            // turning off other leds
            for (byte i = 0; i < 3; ++i)
            {
                if (i != cur_led)
                {
                    digitalWrite(leds[i], 0);
                }
            }
            PRINTLN("SHORT PRESS");
        }
        else if (b_elapsed >= 2000)
        {
            // more than 2 seconds
            cur_per = (cur_per + 1) % 3;
            PRINTLN("LONG PRESS");
        }
        else
        {
            PRINTLN("PRESS");
        }
    }
    if (l_elapsed > pers[cur_per])
    {
        l_timer = millis();
    }
    digitalWrite(leds[cur_led], l_elapsed < IMP_LEN);
    was_pressed = pressed;
}

#define BTN_PIN 4
#define IN_1_PIN 5
#define IN_2_PIN 6
#define POT_PIN 14

#define BTN_WAIT 75

uint32_t btn_timer;
bool prev_btn = LOW;
bool straight = false;

void setup() {
  pinMode(BTN_PIN, INPUT);
  pinMode(POT_PIN, INPUT);
  pinMode(IN_1_PIN, OUTPUT);
  pinMode(IN_2_PIN, OUTPUT);
}

void set_rotation_speed(byte speed) {
  analogWrite(IN_1_PIN, speed * straight);
  analogWrite(IN_2_PIN, speed * !straight);
}

void loop() {
  bool curr_btn = digitalRead(BTN_PIN);
  if (prev_btn == LOW && curr_btn == HIGH && millis() - btn_timer > BTN_WAIT) {
    straight = !straight;
    btn_timer = millis();
  }
  byte pot_val = analogRead(POT_PIN) / 4;
  set_rotation_speed(pot_val);
  prev_btn = curr_btn;
}

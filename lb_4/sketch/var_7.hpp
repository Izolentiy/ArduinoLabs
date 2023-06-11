#define BTN_L 3
#define BTN_H 4
#define IN_1 5
#define IN_2 6

#define STEP 32
#define DEL 50

bool was_pressed_l = false, was_pressed_h = false;
int speed = 0; // > 0 - по часовой, < 0 - против
void set_rotation_speed() {
  if (speed > 0) {
    // крутится вперед
    analogWrite(IN_1, speed);
    analogWrite(IN_2, LOW);
  } else {
    // крутится назад
    analogWrite(IN_1, LOW);
    analogWrite(IN_2, abs(speed));
  }
}

void setup() {
  pinMode(BTN_L, INPUT);
  pinMode(BTN_H, INPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
}

void loop() {
  bool pressed_l = digitalRead(BTN_L);
  bool pressed_h = digitalRead(BTN_H);
  if (pressed_h && !was_pressed_h) {
    delay(DEL);
    speed += STEP;
    if (speed >= 255) speed = 255;
  }
  if (pressed_l && !was_pressed_l) {
    delay(DEL);
    speed -= STEP;
    if (speed <= -255) speed = -255;
  }
  set_rotation_speed();
}

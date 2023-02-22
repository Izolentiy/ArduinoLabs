#define pwmPin 3
#define modeBtnPin 4
#define levelBtnPin 2

void setup() {
  pinMode(pwmPin, OUTPUT);
  pinMode(modeBtnPin, INPUT);
  pinMode(levelBtnPin, INPUT);

  Serial.begin(9600);
}

unsigned char brightness = 0;
bool isAscending = HIGH;
bool previous = LOW;

void loop() {
  
  int modeButtonValue = digitalRead(modeBtnPin);
  int levelButtonValue = digitalRead(levelBtnPin);

  Serial.println(brightness);
  if (levelButtonValue == HIGH) {
    if (isAscending) {  
      if (brightness < 255) {
        ++brightness;
      }
    } else {
      if (brightness > 0) {
        --brightness;
      }
    }
    analogWrite(pwmPin, brightness);
  }

  if (modeButtonValue == HIGH && previous == LOW) {
    previous = HIGH;
    delay(50);
  }
  if (modeButtonValue == LOW && previous == HIGH) {
    isAscending = !isAscending;
    previous = LOW;
  }

}
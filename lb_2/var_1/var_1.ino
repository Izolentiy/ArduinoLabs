#define pwmPin 3
#define adcPin 2

void setup() {
  pinMode(pwmPin, OUTPUT);
  pinMode(adcPin, INPUT);

  Serial.begin(9600);
}

int mapFromAnalogToPwm(int val) {
  return val / 4;
}

void loop() {
  int value = analogRead(adcPin);
  value = mapFromAnalogToPwm(value);
  Serial.println(value);

  analogWrite(pwmPin, value);
}
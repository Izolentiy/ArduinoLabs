#include <Servo.h>
#include <Stepper.h>

#define pwmPin 3

#define pin4 8
#define pin3 9
#define pin2 10
#define pin1 11

Stepper stepper = Stepper(64, pin1, pin2, pin3, pin4);
Servo servo;

void servoSetup() {
  servo.attach(pwmPin);  // Указание пина к которому "подключен" сервопривод
}

void stepperSetup() {
  stepper.setSpeed(300);  // Задаем количество оборотов в минуту
}

void setup() {
  stepperSetup();
  
  Serial.begin(9600);  // Открытие последовательного порта
  Serial.setTimeout(50);  // Установка времени ожидания порта
  
}

void servoSmoothRotation() {
  for (int i = 0; i <= 180; i++) {    
    servo.write(i);
    delay(15);
  }
  for (int i = 180; i > 0; i--) {
    servo.write(i);
    delay(15);
  }
}

void loop() {

  stepper.step(20);
  delay(5000);
  
  // Serial.println("Iteration ended");

  // Плавное прокручивание сервопривода
  // servoSmoothRotation();

  // Serial.println(analogRead(pwmPin));
  // if (Serial.available()) {
  //   int val = Serial.parseInt();
  //   servo.write(val);
  //   Serial.println("Current angle: " + String(servo.read()));
  // }

}
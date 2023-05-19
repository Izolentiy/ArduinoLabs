byte leds[3] = {2, 3, 4};

namespace task_4 {
  void setup();
  void loop();
}

// выполняется один раз в самом начале
void task_4::setup() {
  for (byte i = 0; i < 3; ++i) {
    pinMode(leds[i], OUTPUT);
  }

  // открываем последовательный порт
  Serial.begin(9600);
  Serial.setTimeout(15);
}

bool flag = false; // address received
byte address, value;

// выполняется бесконечно
void task_4::loop() {
  // убеждаемся, что в буфере есть хотя бы один байт
  if (Serial.available()) {
    char rec = Serial.read(); // читает символ
    if (flag) {
      switch (rec) {
      case '0': value = 0; break;
      case '1': value = 1; break;
      default: Serial.println("Wrong value");
      }
      digitalWrite(address, value);
      flag = false;
    } else {
      switch (rec) {
      case '1': address = leds[0]; break;
      case '2': address = leds[1]; break;
      case '3': address = leds[2]; break;
      default: Serial.println("Wrong address");
      }
    }
  }
}
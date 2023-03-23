#define SIZE 1
#define ASCII_1 49
#define ASCII_0 48
#define LED_COUNT 5

byte led_arr[5] = {3, 4, 5, 6, 7};  // Массив пинов к которым подключены светодиоды ленты
byte buffer[SIZE] = { 0 }; // Буфер, в который будет считываться сигнал из монитора порта

void setup() {
  Serial.begin(9600);  // Открытие последовательного порта
  Serial.setTimeout(50);  // Установка времени ожидания порта
  for (byte i = 0; i < LED_COUNT; ++i) {
    pinMode(led_arr[i], OUTPUT);
  }
}

void set_state_to_strip(bool state) {
  for (byte i = 0; i < LED_COUNT; ++i) {
    digitalWrite(led_arr[i], state);
  }
}

void loop() {
  if (Serial.available()) {
    Serial.readBytes(buffer, SIZE); // Чтение в буфер определенного количества байтов
    Serial.println("Readed byte: [" + String(buffer[0]) + ']');
    switch (buffer[0]) {
    case ASCII_0:
      set_state_to_strip(LOW);
      break;
    case ASCII_1:
      set_state_to_strip(HIGH);
      break;
    default:
      Serial.println("Wrong signal");
      break;
    }
  }
}
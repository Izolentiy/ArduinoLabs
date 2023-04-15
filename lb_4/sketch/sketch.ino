// #include "h_brdige.hpp"
// #include "rgb_led.hpp"
#include "motor.hpp"

void setup() {
  // rgb_led::setup();
  motor::setup();
}

void loop() {
  // rgb_led::loop();
  motor::loop();
}
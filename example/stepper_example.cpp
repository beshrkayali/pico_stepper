#include "pico/stdlib.h"
#include "pico_stepper.hpp"

const PicoStepperConf conf = {
 pin1: 1,
 pin2: 2,
 pin3: 3,
 pin4: 4,
 total_steps: 200,
 initial_speed: 50
};

PicoStepper stepper(conf);

int main() {
  while (true) {
    stepper.step(200);
    sleep_ms(500);
    stepper.step(-200);
    sleep_ms(500);
  }
}

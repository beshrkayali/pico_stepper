/*
 * pico_stepper.cpp - Stepper library for Raspberry Pi Pico - Version 0.1
 *
 * Copyright (C) Beshr Kayali
 *
 * Based on Arduino Stepper Library
 * Copyright (C) Arduino LLC. Copyright (C) Sebastian Gassner. Copyright (c) Noah Shibley.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <cstdlib>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico_stepper.hpp"


PicoStepper::PicoStepper(PicoStepperConf conf) {
  this->total_steps = conf.total_steps;
  this->pin1 = conf.pin1;
  this->pin2 = conf.pin2;
  this->pin3 = conf.pin3;
  this->pin4 = conf.pin4;
  this->current_step = 0;
  this->dir = 0;
  this->last_step_us_time = 0;
  this->delay = 60L * 1000L * 1000L / this->total_steps / conf.initial_speed;
  gpio_init(this->pin1);
  gpio_init(this->pin2);
  gpio_init(this->pin3);
  gpio_init(this->pin4);
  gpio_set_dir(this->pin1, GPIO_OUT);
  gpio_set_dir(this->pin2, GPIO_OUT);
  gpio_set_dir(this->pin3, GPIO_OUT);
  gpio_set_dir(this->pin4, GPIO_OUT);
}

void PicoStepper::setSpeed(long speed) {
  this->delay = 60L * 1000L * 1000L / this->total_steps / speed;
}

void PicoStepper::step(int steps_to_move) {
  int steps_left = abs(steps_to_move);

  if (steps_to_move > 0) {
    this->dir = 1;
  } else {
    this->dir = 0;
  }

  while (steps_left > 0) {
    uint64_t now = to_us_since_boot(get_absolute_time());

    if (now - this->last_step_us_time >= this->delay) {
      this->last_step_us_time = now;

      if (this->dir == 1) {
        this->current_step++;

        if (this->current_step == this->total_steps) {
          this->current_step = 0;
        }
      } else {
        if (this->current_step == 0) {
          this->current_step = this->total_steps;
        }

        this->current_step--;
      }

      stepMotor(this->current_step % 4);
      steps_left--;
    }
  }
}

void PicoStepper::stepMotor(int step) {
  switch (step) {
  case 0:  // 1010
    gpio_put(this->pin1, 1);
    gpio_put(this->pin2, 0);
    gpio_put(this->pin3, 1);
    gpio_put(this->pin4, 0);
    break;

  case 1:  // 0110
    gpio_put(this->pin1, 0);
    gpio_put(this->pin2, 1);
    gpio_put(this->pin3, 1);
    gpio_put(this->pin4, 0);
    break;

  case 2:  // 0101
    gpio_put(this->pin1, 0);
    gpio_put(this->pin2, 1);
    gpio_put(this->pin3, 0);
    gpio_put(this->pin4, 1);
    break;

  case 3:  // 1001
    gpio_put(this->pin1, 1);
    gpio_put(this->pin2, 0);
    gpio_put(this->pin3, 0);
    gpio_put(this->pin4, 1);
    break;
  }
}


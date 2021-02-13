/*
 * pico_stepper.hpp - Stepper library for Raspberry Pi Pico - Version 0.1
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

#pragma once

struct PicoStepperConf {
  int pin1;
  int pin2;
  int pin3;
  int pin4;
  int total_steps;
  long initial_speed;
};

class PicoStepper {
 public:
  PicoStepper (PicoStepperConf conf);

  void setSpeed(long speed);

  void step(int total_steps);

 private:
  void stepMotor(int step);

  int dir;
  unsigned long delay;
  int total_steps;
  int current_step;

  int pin1;
  int pin2;
  int pin3;
  int pin4;

  unsigned long last_step_us_time;
};

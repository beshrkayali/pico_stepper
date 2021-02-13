cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(stepper_example C CXX ASM)
pico_sdk_init()
add_executable(stepper_example
  stepper_example.cpp
  )
add_subdirectory(../pico_stepper build)
pico_add_extra_outputs(stepper_example)
target_link_libraries(stepper_example pico_stdlib pico_stepper)

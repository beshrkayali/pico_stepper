add_library(pico_stepper INTERFACE)

target_sources(pico_stepper INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/pico_stepper.cpp
)

target_include_directories(pico_stepper INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Pull in pico libraries that we need
target_link_libraries(pico_stepper INTERFACE pico_stdlib pico_time)

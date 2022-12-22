# What CMake to start at
cmake_minimum_required(VERSION 3.12)

# Include the subsidiary .cmake file to get the SDK
include(pico_sdk_import.cmake)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION "0.0.0")

# Set the name and version of the project
project(TIUsbKeeb VERSION 1.0.0)

# Link the Project to a source file (step 4.6)
add_executable(TIUsbKeeb main.c)

# Link the Project to an extra library (pico_stdlib)
target_link_libraries(TIUsbKeeb pico_stdlib)

# Initalise the SDK
pico_sdk_init()

# Enable USB, UART output
pico_enable_stdio_usb(TIUsbKeeb 1)
pico_enable_stdio_uart(TIUsbKeeb 1)

# Enable extra outputs (SWD?)
pico_add_extra_outputs(TIUsbKeeb)

cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# this makes macOS on arm64 happy /shrug
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION "0.0.0")

pico_sdk_init()

project(TIUsbKeeb VERSION 1.0.0)

add_executable(TIUsbKeeb)

target_sources(TIUsbKeeb PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/keyboard.cpp
)

target_link_libraries(TIUsbKeeb pico_stdlib)

pico_enable_stdio_usb(TIUsbKeeb 1)
pico_enable_stdio_uart(TIUsbKeeb 1)

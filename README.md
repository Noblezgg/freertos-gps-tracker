## Why

This is an attempt to redo a hacky GPS tracker I put together with Arduino and learn some cool industry-used RTOS stuff. Opted for FreeRTOS because the ESP32-idf already uses it, I can learn more about FreeRTOS (and maybe even ZephyrOS) as I go.

## To Do
Current project flow is:

UART GPS module works (done)
I2C module works (done)
I2C module displays GPS coordinates (active WIP)
ESP32 BLE works (done)
ESP32 BLE can connect to my transmitter and recieve data (NYI)
I2C module display GPS coordinates of both the drone and the station (blocked)
ESP32 can control a servo motor and stepper motor (blocked)
ESP32 can use the servo motor and stepper motor to point an antenna in the general direction of the target UAV (blocked)

## Folder Contents

The below is the current planned source code tree contents.

I'll try to keep this up to date as I make more progress in different feaeture branches.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   ├── main.c
│   ├── uart-gps
│   │     ├── nmea.c
│   │     └── nmea.h
│   ├── i2c-oled
│   │     ├── i2c-oled.c
│   │     └── i2c-oled.h
│   └── Kconfig.projbuild
└── README.md                  This is the file you are currently reading
```

# ECUAL Layer – Embedded Control Unit Abstraction Layer

## Overview
The ECUAL (Embedded Control Unit Abstraction Layer) provides high-level drivers for external peripherals connected to the microcontroller.  
This layer abstracts low-level GPIO handling and exposes simple, readable APIs for application-level development.

## Supported Drivers
- Character LCD (HD44780) – `ecu_Chr_lcd`
- Button – `ecu_button`
- LED – `ecu_led`
- 7-Segment Display – `ecu_7Seg`
- Matrix Keypad – `ecu_keypad`
- DC Motor – `ecu_DC_motor`
- Relay – `ecu_relay`

## Layer Information
- Layer Name: ECUAL
- Target MCU: PIC18F4620
- Required Layer: HAL (GPIO)
- Programming Language: C
- Driver Style: Blocking, polling-based
- Author: Abdelmoniem Ahmed
- LinkedIn: https://www.linkedin.com/in/abdelmoniem-ahmed/
- Year: 2026

## Directory Structure
```
ECUAL/
│
├── ecu_led/
├── ecu_button/
├── ecu_7Seg/
├── ecu_Chr_lcd/
├── ecu_keypad/
├── ecu_DC_motor/
└── ecu_relay/
```

## How to Use
1. Include the required ECUAL driver header file in your application source file.
   ```c
   #include "ecu_led.h"
   ```

2. Create and configure the driver configuration structure.

3. Call the initialization function once during system startup.

4. Use the provided APIs to control the peripheral during runtime.

## Notes
- All ECUAL drivers depend on the GPIO HAL driver.
- No direct access to microcontroller registers is performed in this layer.
- All drivers use polling (no interrupts).
- Configuration is done using structures defined in each driver header.
- The ECUAL layer is intended to simplify application development.

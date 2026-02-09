# LED Driver – ECUAL

## Overview
The LED driver provides simple APIs to control LEDs using GPIO pins.  
It supports initialization, turning LEDs ON, OFF, and toggling their state.

## Driver Features
- GPIO-based LED control
- Supports active-high LEDs
- Simple and lightweight API
- No timers or interrupts used

## Configuration
The LED is configured using the `led_t` structure:
- LED port
- LED pin
- Initial LED state

## Provided APIs
- `led_initialize()`
- `led_turn_on()`
- `led_turn_off()`
- `led_turn_toggle()`

## Dependencies
- GPIO HAL Driver (`hal_gpio.h`)

## Notes
- The driver does not perform state tracking internally.
- Each API call directly accesses the GPIO HAL.
- LED behavior depends on correct GPIO configuration.

# Matrix Keypad Driver – ECUAL

## Overview
The Matrix Keypad driver provides functionality to interface with a 4x4 keypad using GPIO pins.  
It scans rows and columns using polling to detect pressed keys.

## Driver Features
- Supports 4x4 matrix keypad
- Polling-based scanning
- GPIO-only implementation
- Configurable row and column pins

## Keypad Layout
The keypad mapping is fixed inside the driver:
```
7  8  9  /
4  5  6  *
1  2  3  -
#  0  =  +
```

## Configuration
The keypad is configured using the `keypad_t` structure:
- Array of row pins
- Array of column pins

## Provided APIs
- `keypad_initialize()`
- `keypad_get_value()`

## Dependencies
- GPIO HAL Driver (`hal_gpio.h`)

## Notes
- No key debouncing is implemented.
- If multiple keys are pressed, the last detected key is returned.
- Application-level debouncing is recommended.
- The function continuously scans until completion.

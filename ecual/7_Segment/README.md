# 7-Segment Display Driver – ECUAL

## Overview
The 7-Segment driver provides control for a single 7-segment display using GPIO pins.  
It allows displaying numeric digits by controlling segment lines directly.

## Driver Features
- GPIO-based segment control
- Supports common cathode configuration
- Simple digit display logic
- Polling-based implementation

## Configuration
The display is configured using GPIO pin mappings for each segment.

## Provided APIs
- Segment initialization function
- Digit display function

## Dependencies
- GPIO HAL Driver (`hal_gpio.h`)

## Notes
- Only numeric digits are supported.
- Multiplexing is not implemented.
- Timing control must be handled by the application if required.


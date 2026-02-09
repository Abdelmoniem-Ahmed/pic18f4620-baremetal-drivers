# Relay Driver – ECUAL

## Overview
The Relay driver allows control of an external relay module using a GPIO pin.  
It supports initialization, ON, OFF, and toggle operations.

## Driver Features
- GPIO-based relay control
- Simple ON/OFF switching
- Supports active-high relay modules
- Lightweight implementation

## Configuration
The relay is configured using the `relay_t` structure:
- Relay port
- Relay pin
- Initial relay state

## Provided APIs
- `relay_initialize()`
- `relay_turn_on()`
- `relay_turn_off()`
- `relay_turn_toggle()`

## Dependencies
- GPIO HAL Driver (`hal_gpio.h`)

## Notes
- The driver assumes an active-high relay.
- No timing delays or protection logic are included.
- Electrical isolation depends on the external relay module.

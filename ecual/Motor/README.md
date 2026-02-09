# DC Motor Driver – ECUAL

## Overview
The DC Motor driver provides basic control for a DC motor using two GPIO pins.  
It supports forward rotation, backward rotation, and stopping the motor.

## Driver Features
- Direction control using two GPIO pins
- Simple ON/OFF logic
- Suitable for H-Bridge motor drivers
- Polling-based control

## Configuration
The motor is configured using the `dc_motor_t` structure:
- Two GPIO pins representing motor control inputs

## Motor Control Logic
- Forward: PIN1 = HIGH, PIN2 = LOW
- Backward: PIN1 = LOW, PIN2 = HIGH
- Stop: PIN1 = LOW, PIN2 = LOW

## Provided APIs
- `dc_motor_initialize()`
- `dc_motor_move_forward()`
- `dc_motor_move_backward()`
- `dc_motor_stop()`

## Dependencies
- GPIO HAL Driver (`hal_gpio.h`)

## Notes
- Speed control is not supported.
- PWM control must be implemented separately if needed.
- No protection or fault detection is implemented.

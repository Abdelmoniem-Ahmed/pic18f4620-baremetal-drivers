# GPIO MCAL Driver – PIC18F4620

## Overview
This module provides a **GPIO driver** for the PIC18F4620 microcontroller.
It abstracts GPIO hardware registers and exposes simple APIs for pin-level
and port-level control.

The driver is intended to be used only by ECUAL or application layers through
its public interface.

---

## Features
- GPIO pin direction configuration
- GPIO pin logic write, read, and toggle
- GPIO port direction configuration
- GPIO port logic write, read, and toggle
- Compile-time enable/disable of features

---

## File Structure

hal_gpio.h → Public interface
hal_gpio.c → Driver implementation
hal_gpio_cfg.h → Compile-time configuration

---

## Driver Usage
- All GPIO configuration is performed using configuration structures
- Direct register access is hidden inside the driver
- APIs perform parameter validation before hardware access

---

## Configuration
The driver supports compile-time configuration through `hal_gpio_cfg.h`.

Examples:
- Enable or disable pin-level APIs
- Enable or disable port-level APIs

This allows excluding unused functionality to reduce code size.

---

## Notes
- The driver is microcontroller-specific
- Higher layers must not access GPIO registers directly

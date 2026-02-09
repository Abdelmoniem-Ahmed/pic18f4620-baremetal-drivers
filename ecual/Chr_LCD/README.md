# Character LCD Driver (ECUAL)

## Overview
This module implements an ECUAL (ECU Abstraction Layer) driver for
HD44780-compatible character LCD displays.

The driver provides high-level APIs for controlling the LCD without
direct hardware register access and depends only on the GPIO MCAL driver.

---

## Supported Features
- 4-bit LCD interface mode
- 8-bit LCD interface mode
- Character and string display
- Cursor positioning
- Custom character (CGRAM) support
- Display control commands

---

## Architecture
- Layer: ECUAL
- Dependency: GPIO MCAL driver only
- Register access: Not allowed in this layer

---

## Design Decisions
- Blocking (polling-based) implementation
- Fixed delays are used instead of busy-flag reading
- No dynamic memory allocation
- Hardware configuration passed using configuration structures

---

## Limitations
- No interrupt-driven or non-blocking operation
- Timing accuracy depends on system clock configuration
- Busy flag is not read from LCD hardware

---

## Configuration
LCD pin connections are configured using:
- `chr_lcd_4bit_t` for 4-bit mode
- `chr_lcd_8bit_t` for 8-bit mode

All GPIO pins used by the LCD must be configured as output pins.

---

## File Structure
- `ecu_Chr_lcd.h`      : Driver interface
- `ecu_Chr_lcd.c`      : Driver implementation
- `ecu_Chr_lcd_cfg.h`  : Configuration file (reserved for future use)

---

## Error Handling
- APIs return `E_NOT_OK` in case of invalid parameters
- No internal error recovery mechanism is implemented

---

## Notes
- Clock configuration must be performed at application level
- This driver assumes HD44780-compatible timing behavior

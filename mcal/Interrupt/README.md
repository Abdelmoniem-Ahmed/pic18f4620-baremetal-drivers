# MCAL Interrupt Driver – PIC18F4620

## Overview

The MCAL Interrupt Driver provides a centralized and configurable mechanism for handling **external and internal interrupts** on the PIC18F4620 microcontroller.

This driver is responsible for:

- Enabling and disabling interrupt sources
- Configuring interrupt priorities (when enabled)
- Dispatching interrupt events to the correct ISR
- Calling user-defined callback functions

> The interrupt driver **does not implement peripheral-specific logic**. Each peripheral driver (ADC, Timers, CCP, EUSART, MSSP, etc.) owns and implements its own ISR behavior.

---

## Supported Interrupt Types

### External Interrupts

- INT0
- INT1
- INT2
- PORTB Change Interrupts (RB4 – RB7)

### Internal (Peripheral) Interrupts

- ADC
- Timer0 / Timer1 / Timer2 / Timer3
- CCP1 / CCP2
- EUSART TX / RX
- MSSP SPI
- MSSP I2C
- MSSP I2C Bus Collision

> Internal interrupt service routines are implemented inside their respective peripheral drivers.  
> The Interrupt Manager only routes and dispatches interrupt events.

---

## Driver Responsibilities

The Interrupt MCAL layer handles:

- Global interrupt control
- Peripheral interrupt enable/disable
- Interrupt priority configuration (optional)
- External interrupt configuration (edge, pin, priority)
- Interrupt source detection
- Callback invocation from ISR context

The driver **does not**:

- Perform peripheral register configuration
- Implement ADC / Timer / UART logic
- Handle application-level behavior

---

## Features

- Compile-time configurable interrupt enable/disable
- Optional priority-based interrupt handling
- Callback-based ISR execution
- Clear separation between interrupt routing and peripheral logic
- Support for INTx and RBx external interrupts
- Designed to support non-blocking drivers

---

## Directory Structure

```text
MCAL/Interrupt/
│
├── mcal_interrupt_config.h
├── mcal_interrupt_gen_cfg.h
├── mcal_externl_interrupt.h
├── mcal_externl_interrupt.c
├── mcal_internal_interrupt.h
├── mcal_interrupt_manager.h
├── mcal_interrupt_manager.c
└── README.md

## File Descriptions

### `mcal_interrupt_gen_cfg.h`

- Compile-time configuration file
- Enables or disables interrupt sources
- Controls feature inclusion using preprocessor macros

### `mcal_interrupt_config.h`

- Global interrupt control macros
- Priority configuration macros
- Common interrupt-related data types

### `mcal_externl_interrupt.h` / `mcal_externl_interrupt.c`

- External interrupt driver (INT0, INT1, INT2, RBx)
- Configures edge detection (rising/falling)
- Configures interrupt priority (if enabled)
- Allows callback function registration for ISR execution

### `mcal_internal_interrupt.h`

- Provides macros for enabling/disabling internal peripheral interrupts
- No `.c` source file is required
- Peripheral drivers implement their own ISR logic

### `mcal_interrupt_manager.h` / `mcal_interrupt_manager.c`

- Central interrupt dispatcher
- Detects active interrupt sources at runtime
- Calls corresponding ISR functions
- Handles RBx change interrupt logic for pins RB4 – RB7

## Interrupt Flow Architecture

1. Hardware interrupt occurs
2. Interrupt Manager identifies the interrupt source
3. Corresponding ISR function is executed
4. Registered callback function is invoked
5. Peripheral driver processes the interrupt event

This architecture ensures:

- Clear ownership of interrupt logic
- Low coupling between drivers
- Scalable and maintainable design

---

## Priority Configuration

Interrupt priority levels are optional and controlled using:

```c
#define INTERRUPT_PRIORITY_LEVELS_ENABLE
- When enabled: High and Low priority interrupts are supported using separate vectors
- When disabled: All interrupts operate in compatibility mode

---

## Usage Notes

- External interrupt pins must be configured as inputs
- Callback functions must be short and non-blocking
- Interrupt flags are cleared in software
- Peripheral drivers must implement their own ISR logic
- Global interrupts must be enabled during system initialization

---

## Design Notes

- Blocking operations inside ISR context are discouraged
- Designed to support future non-blocking peripheral drivers
- No RTOS dependency
- No dynamic memory allocation

---

## Dependencies

- `xc.h`
- `std_types.h`
- GPIO HAL driver (`hal_gpio.h`)

---

## Author

**Abdelmoniem Ahmed**  
Embedded Systems Engineer  
[LinkedIn](https://www.linkedin.com/in/abdelmoniem-ahmed/)

**Year:** 2026

---

## Status

- MCAL Interrupt Driver: Completed
- Peripheral Drivers Documentation: In progress
- Non-blocking Support: Enabled via callbacks

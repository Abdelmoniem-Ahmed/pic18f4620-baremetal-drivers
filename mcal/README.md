# 🟢 MCAL – Microcontroller Abstraction Layer

![MCAL](https://img.shields.io/badge/Layer-MCAL-blue)

## Overview
The **MCAL (Microcontroller Abstraction Layer)** contains **hardware-dependent drivers** that provide a clean and consistent API to higher layers, while encapsulating direct access to the PIC18F4620 hardware registers.

The MCAL layer:

- Is fully hardware-specific
- Handles low-level peripheral control
- Exposes reusable APIs for ECUAL and Application layers
- Ensures safe and maintainable access to microcontroller peripherals

> ⚠️ Application code **must not** directly access MCU registers. All hardware interaction should go through MCAL drivers.

---

## Responsibilities

MCAL is responsible for:

- Direct interaction with MCU registers
- Peripheral initialization and configuration
- Providing hardware abstraction for ECUAL and Application layers
- Defensive programming and parameter validation
- Supporting both polling and interrupt-driven operation where applicable

---

## Available Drivers

| Peripheral 			   | Status      | Description |
|--------------------------|-------------|-------------|
| GPIO       			   | ✅ Complete | Digital input/output control with configurable pin direction and output level |
| Interrupt Manager 	   | ✅ Complete | Centralized interrupt management for MCU peripherals |
| ADC        			   | ✅ Complete | Blocking and interrupt-based analog-to-digital conversion |
| Timer0     			   | ✅ Complete | 8/16-bit timer with prescaler support |
| Timer1     			   | ✅ Complete | 16-bit timer with interrupt support |
| Timer2     			   | ✅ Complete | Timer with prescaler and postscaler configuration |
| Timer3     			   | ✅ Complete | 16-bit timer module with interrupt support |
| CCP        			   | ✅ Complete | Capture, Compare, and PWM functionality |
| EUSART     			   | ✅ Complete | Asynchronous and synchronous serial communication |
| MSSP – SPI 			   | ✅ Complete | Master/Slave SPI communication |
| MSSP – I2C 			   | ✅ Complete | I2C Master mode with configurable speed |

> All drivers are **fully documented** using Doxygen-style comments and configurable via dedicated configuration headers.

---

## Design Guidelines

- No direct register access outside MCAL
- Clear separation between interface and implementation
- Hardware configuration handled via dedicated headers
- Consistent API naming across all drivers
- Modular and scalable design for easy reuse
- Support for both polling and interrupt-driven operation

---

## Getting Started

1. Include the required MCAL driver header in your ECUAL or application code:

```c
#include "mcal/gpio/gpio.h"
```

2. Initialize the peripheral using the provided initialization structures:

```c
gpio_config_t led_pin = {
    .port = PORTB_INDEX,
    .pin  = PIN0,
    .direction = GPIO_OUTPUT,
    .initial_state = GPIO_LOW
};

gpio_initialize(&led_pin);
```

3. Use the exposed API functions to control the peripheral.

---

## Notes

MCAL is **hardware-specific**: changing the target MCU requires rewriting this layer.
All ECUAL and Application-level drivers depend on **MCAL**.
Following these design principles ensures **maintainable, reusable, and portable code** within the **PIC18F4620** ecosystem.

## 👤 Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer – MCU & Low-Level Systems  

🔗 LinkedIn:  
https://www.linkedin.com/in/abdelmoniem-ahmed/

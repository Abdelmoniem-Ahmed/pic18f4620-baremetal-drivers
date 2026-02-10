# PIC18F4620 Bare‑Metal Drivers (MCAL + ECUAL)

![C](https://img.shields.io/badge/language-C-blue)
![XC8](https://img.shields.io/badge/compiler-XC8-green)
![PIC18F4620](https://img.shields.io/badge/mcu-PIC18F4620-orange)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)

Bare‑metal drivers for the **PIC18F4620** microcontroller using **MPLAB X + XC8 compiler**, following a clean layered architecture (**MCAL → ECUAL → Application**).  
The goal is **hardware abstraction, maintainable code, separation of concerns, and reusable components** for real embedded projects.

---

## 🧠 Architecture Overview

Application / Business Logic
↓
ECUAL (Hardware‑independent services)
↓
MCAL (Register & peripheral abstraction)
↓
PIC18F4620 Hardware


- **MCAL** → Microcontroller Abstraction Layer (register‑level control, chip‑specific).
- **ECUAL** → ECU Abstraction Layer (easy‑to‑use hardware components: LED, Button, LCD…).
- **Application** → Demo code showing usage of MCAL/ECUAL drivers.

---

## 🚧 Project Status (Updated February 2026)

| Layer | Component                     | Status          | Documentation | Notes                                                                |
|-------|-------------------------------|----------------|---------------|-----------------------------------------------------------------------|
| MCAL  | GPIO                          | ✓ Complete      | ✓             | Fully tested                                                         |
| MCAL  | Interrupt Manager             | ✓ Complete      | ✓             | ADC interrupt implemented; other ISRs commented for future drivers   |
| MCAL  | Timer / CCP / EUSART          | ✗ Not yet       | —             | Drivers not uploaded; ISRs commented for future integration          |
| MCAL  | ADC                           | ✓ Complete      | ✓             | Blocking + interrupt;                                                |
| ECUAL | LED                           | ✓ Complete      | ✓             | Tested in app blink example                                          |
| ECUAL | Button                        | ✗ Not yet       | ✓             | Planned; debounce support to be added                                |
| ECUAL | LCD (4‑bit/8-bit)             | ✓ Complete      | ✓             | Basic text working;                                                  |
| APP   | Example: LED blink            | ✓ Complete      | —             | Shows basic ECUAL + GPIO usage                                       |

> ✅ All current drivers are implemented and documented. Unimplemented ISRs (Timer, CCP, EUSART, EXTI, etc.) are commented for future driver integration. ADC ISR is fully implemented. Stubs removed.

---

## 📁 Folder Structure

pic18f4620-baremetal-drivers/
├── common/ # Shared types, macros, bit helpers
├── mcal/ # MCU driver modules
│ ├── GPIO/
│ ├── Interrupt/
│ ├── ADC/
│ └── ...
├── ecual/ # High‑level components (LED, Button, LCD…)
├── application/ # main application + examples
├── .gitignore
└── README.md


---

## 🚀 Getting Started

### Prerequisites

Before building/run:

- **MPLAB X IDE** (v6.15+ recommended)
- **XC8 compiler** (v2.40+)
- **PIC18F4620 datasheet** (Microchip)
- Any PIC programmer/debugger (PICkit, ICD, etc.)

### Build & Flash

1. Clone the repo.
2. Open `MPLAB X` and load the project.
3. Adjust configuration bits (config headers).
4. Build & program to your board.

---

## 📌 Usage Example — LED Blink (in `application/application.c`)

```c
#include "application.h"

led_t red_led = {
    .port_name = PORTB_INDEX,
    .pin = PIN0,
    .led_status = GPIO_PIN_LOW
};

int main(void) {
    application_initialize();

    while (1) {
        led_turn_toggle(&red_led);
        __delay_ms(250);
    }
    return 0;
}

void application_intialize(void) {
    led_initialize(&red_led);
}
```

This simple example initializes the LED and toggles it every 250 ms using the ECUAL LED driver.

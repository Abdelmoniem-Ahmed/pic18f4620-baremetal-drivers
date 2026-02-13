# PIC18F4620 Bare‑Metal Drivers (MCAL + ECUAL)

![C](https://img.shields.io/badge/language-C-blue)
![XC8](https://img.shields.io/badge/compiler-XC8-green)
![PIC18F4620](https://img.shields.io/badge/mcu-PIC18F4620-orange)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)

Bare‑metal drivers for the **PIC18F4620** microcontroller using **MPLAB X + XC8 compiler**, following a clean layered architecture (**Application → ECUAL → MCAL → Hardware**).  
The goal is **hardware abstraction, maintainable code, separation of concerns, and reusable components** for real embedded projects.

---

## Overview

This repository contains a complete **bare-metal driver framework** for the **PIC18F4620** microcontroller using **MPLAB X IDE** and the **XC8 compiler**.

The project follows a clean layered architecture:

`Application → ECUAL → MCAL → Hardware`

- **MCAL** → Microcontroller Abstraction Layer (register‑level control, chip‑specific).
- **ECUAL** → ECU Abstraction Layer (easy‑to‑use hardware components: LED, Button, LCD…).
- **Application** → Demo code showing usage of MCAL/ECUAL drivers.

All implemented drivers are documented using **Doxygen-style comments**, and API documentation is available.

## 🎯 Why This Project?

This project demonstrates:

- Strong understanding of microcontroller architecture
- Register-level peripheral control
- Interrupt-driven design
- Hardware abstraction design patterns
- Scalable embedded firmware structure


## Project Status

### MCAL – Microcontroller Abstraction Layer

All major PIC18F4620 peripherals are implemented and documented.

| Peripheral 					 | Status       | Description    				   		  | 
|--------------------------------|--------------|-----------------------------------------|
| GPIO  	  	 				 | ✅ Complete	| Digital input/output control     	      |
| Interrupt Manager  	 		 | ✅ Complete 	| Centralized interrupt handling          |
| ADC  	  	 					 | ✅ Complete	| Blocking & interrupt-based conversion   |
| Timer0 	 					 | ✅ Complete  | 8/16-bit timer support                  |
| Timer1 	 					 | ✅ Complete  | 16-bit timer with interrupt support     |
| Timer2 	 					 | ✅ Complete  | Timer with prescaler/postscaler         | 
| Timer3 	 					 | ✅ Complete  | 16-bit timer module                     |
| CCP (Capture/Compare/PWM)   	 | ✅ Complete  | Capture, Compare, and PWM modes         |
| EUSART  	 					 | ✅ Complete  | Asynchronous & synchronous communication|
| MSSP – SPI 	 			     | ✅ Complete  | Master/Slave SPI communication          |
| MSSP – I2C 	 				 | ✅ Complete  | I2C Master mode support                 |

All MCAL drivers:

- Configurable via initialization structures
- Support interrupt and polling modes (where applicable)
- Follow consistent API naming conventions
- Fully documented with Doxygen comments

---

## ✅ ECUAL – External Component Abstraction Layer

The ECUAL layer provides reusable drivers for common external hardware components built on top of the MCAL layer.

| Component        | Status       | Description 						   |
|------------------|--------------|----------------------------------------|
| LED              | ✅ Complete  | On / Off / Toggle control 			   |
| 7-Segment        | ✅ Complete  | BCD and direct segment control support |
| Character LCD    | ✅ Complete  | 4-bit and 8-bit mode support 		   |
| Matrix Keypad    | ✅ Complete  | Row/Column scanning with debouncing    |
| DC Motor         | ✅ Complete  | Direction and enable control  		   |
| Relay            | ✅ Complete  | Digital control for switching loads    |

All ECUAL drivers:

- ✔ Built on top of the MCAL layer  
- ✔ Hardware-independent configuration  
- ✔ Clean and reusable APIs  
- ✔ Configurable using initialization structures  
- ✔ Fully documented with Doxygen-style comments  


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

void application_initialize(void) {
    led_initialize(&red_led);
}
```

This simple example initializes the LED and toggles it every 250 ms using the ECUAL LED driver.


## Documentation

- Doxygen-style comments in all header files
- Clear API descriptions
- Parameter explanations
- Usage examples in the Application layer

## Design Principles

- Bare-metal development (no RTOS)
- Layered architecture (MCAL / ECUAL)
- Modular and scalable structure
- Reusable driver design
- Clear separation between hardware and application logic
- Embedded software best practices

## Development Environment

- IDE: MPLAB X
- Compiler: XC8
- Target MCU: PIC18F4620
- Language: C

## Repository Structure

```text
pic18f4620-baremetal-drivers/
│
├── mcal/
│   ├── GPIO/
│   ├── ADC/
│   ├── Interrupt/
│   ├── Timer0/
│   ├── Timer1/
│   ├── Timer2/
│   ├── Timer3/
│   ├── CCP/
│   ├── EUSART/
│   ├── I2C/
│   └── SPI/
│
├── ecual/
│   ├── LED/
│   ├── Matrix_Keypad/
│   ├── Chr_LCD/
│   ├── 7_Segment/
│   ├── Motor/
│   └── Relay/
│
│
└── common/
```

## ✨ Key Features

- Full peripheral coverage of PIC18F4620
- Structured MCAL/ECUAL layered architecture
- Interrupt-driven and polling support
- Configurable via initialization structures
- Doxygen-documented APIs
- Reusable and scalable driver design

## Future Improvements

- Additional example applications
- Unit testing framework


## 👤 Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer – MCU & Low-Level Systems  

🔗 LinkedIn:  
https://www.linkedin.com/in/abdelmoniem-ahmed/

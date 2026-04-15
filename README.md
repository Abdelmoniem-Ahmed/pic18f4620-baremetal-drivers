# PIC18F4620 Bare‑Metal Drivers (MCAL + ECUAL)

![C](https://img.shields.io/badge/language-C-blue)
![XC8](https://img.shields.io/badge/compiler-XC8-green)
![PIC18F4620](https://img.shields.io/badge/mcu-PIC18F4620-orange)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)

## 🎥 Project Demo

[![Driver Demo](https://img.youtube.com/vi/RqG13C6xlhg/0.jpg)](https://youtu.be/RqG13C6xlhg)

👉 https://youtu.be/RqG13C6xlhg

This demo demonstrates:
- LCD driver (4-bit mode)
- Keypad input handling
- I2C communication
- Timer-based scheduling
- Modular MCAL/ECUAL integration



Bare‑metal drivers for the **PIC18F4620** microcontroller using **MPLAB X + XC8 compiler**, following a clean layered architecture 

`Application → ECUAL → MCAL → Hardware`.  

The repository contains **MCAL & ECUAL drivers** and **example applications** demonstrating usage of each driver, with full control over hardware abstraction and reusable components.

---

## Overview

- **MCAL (Microcontroller Abstraction Layer)**: Register-level peripheral control (GPIO, Timer, ADC, CCP, EUSART, SPI/I2C, Interrupt Manager)
- **ECUAL (ECU Abstraction Layer)**: Easy-to-use drivers for LEDs, 7-Segment, LCD, Keypad, DC Motors, Relays
- **Application Layer**: Main entry point (`application.c`) orchestrates demo examples using MCAL & ECUAL

This layered design ensures:

- Maintainable code
- Separation of concerns
- Easy-to-use hardware abstraction
- Reusable examples
 
---

## 🧩 Example Applications

All example applications are included in `Example_projects/` and can be enabled via macros in `application.h`:

| **Example** 					  | **Description**                      | **Drivers Used**    				   	   | **Macro in** `application.h` | 
|---------------------------------|--------------------------------------|-----------------------------------------|------------------------------|
| LED Blink  	  	 			  | LED patterns & toggle	             | LED, GPIO     	                       | `LED_BLINK_APP`              |
| Character LCD  	 		      | 4-bit LCD, custom characters 	     | LCD                                     | `CHR_LCD_APP`                |
| Matrix Keypad  	  	 		  | Key input scanning & display	     | Keypad, LCD, Timer                      | `MATRIX_KEYPAD_APP`          |
| Seven Segment 	 			  | Display numbers or scrolling digits  | 7-Segment, Timer                        | `SEVEN_SEGMENT_APP`          |
| Smart Home (Master + Slave MCU) | Complete system simulation           | Keypad, LCD, I2C, PWM, RTC, EEPROM, LED |  `SMART_HOME_APP`            |

> Only one example runs at a time based on the `WORKING_APPLICATION` macro in `application.h`

## 🧠 Main Application (application.c)

The **main function** dynamically selects the working application:

```c
#include "application.h"

int main(void) {
    application_intialize();

#if SMART_HOME_APP == WORKING_APPLICATION
    #if SMART_HOME_SLAVE_BUILD == SMART_HOME_NODE
        slave_mcu_main_app();
    #endif
    #if SMART_HOME_MASTER_BUILD == SMART_HOME_NODE
        Smart_Home_App();
    #endif
#endif

#if MATRIX_KEYPAD_APP == WORKING_APPLICATION
    Matrix_Keypad_Led_App();
#endif

#if SEVEN_SEGMENT_APP == WORKING_APPLICATION
    Seven_Segment_app();
#endif

#if CHR_LCD_APP == WORKING_APPLICATION
    Chr_LCD_app();
#endif

#if LED_BLINK_APP == WORKING_APPLICATION
    Led_Blink_app();
#endif

    while(1) { }
    return 0;
}
```

- `application_initialize()` sets up all MCU peripherals and ECUAL drivers
- Easily switch which example runs by changing macros in `application.h`

---

## 🚀 Getting Started

### Prerequisites

- **MPLAB X IDE** (v6.15+ recommended)
- **XC8 compiler** (v2.40+)
- **PIC18F4620 datasheet** (Microchip)
- PIC programmer/debugger (PICkit, ICD, etc.)

### Build & Flash

1. Clone the repo.
2. Open `MPLAB X` and load the project.
3. Configure the macros in `application.h` for the desired example
4. Build & program to your board.

---

## Repository Structure

```text
pic18f4620-baremetal-drivers/
│
├── mcal/                  # Microcontroller Abstraction Layer
├── ecual/                 # ECU Abstraction Layer
├── Example_projects/      # Application examples
│   ├── LED/
│   ├── Character_LCD/
│   ├── Matrix_Keypad/
│   ├── 7_Segment/
│   ├── Smart_Home/
│   │   ├── Smart_Home_app.h/c
│   │   └── Slave_MCU/
├── common/                # Common headers and types
├── application.h/c        # Main application layer
└── README.md
```

## ✨ Key Features

- Full peripheral coverage of PIC18F4620
- Structured MCAL/ECUAL layered architecture
- Interrupt-driven and polling support
- Configurable via initialization structures
- Doxygen-documented APIs
- Reusable and scalable driver design

## 💡 Notes

- Each example includes:
  - Source and header files
  - Proteus simulation (where applicable)
  - Pre-built debug files (`.cof`) for MPLAB X
- Adjust **pins and addresses** in each header for your hardware
- The **Smart Home example** demonstrates full master-slave I2C communication

## 👤 Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer – MCU & Low-Level Systems  

🔗 LinkedIn:  
https://www.linkedin.com/in/abdelmoniem-ahmed/

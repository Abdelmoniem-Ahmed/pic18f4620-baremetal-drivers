# Seven Segment Display Example – PIC18F4620

![C](https://img.shields.io/badge/language-C-blue)
![ECUAL](https://img.shields.io/badge/layer-ECUAL-yellow)
![MCU](https://img.shields.io/badge/mcu-PIC18F4620-orange)

This example demonstrates the use of the **7-Segment ECUAL driver** to display numbers on both **common cathode** and **common anode** 7-segment displays using a **PIC18F4620** microcontroller.  
It highlights **hardware abstraction**, **GPIO handling**, and **basic timing control**.

---


## 📁 Folder Structure

```text
Seven_Segment/
│
├── 7_segment_app.h         # Application header
├── 7_segment_app.c         # Application source
├── Proteus/                # Proteus simulation project files
└── Builds/                  # Compiled .cof/debug files for MPLAB X
```

---

## Pin Configuration

### Common Cathode Display

| Segment | Port      | Pin  | 
|---------|-----------|------|
| SEG0    | PORTC     | 0    | 
| SEG1    | PORTC     | 1    | 
| SEG2    | PORTC     | 2    | 
| SEG3    | PORTC     | 3    | 
 
### Common Anode Display

| Segment | Port      | Pin  | 
|---------|-----------|------|
| SEG0    | PORTD     | 0    | 
| SEG1    | PORTD     | 1    | 
| SEG2    | PORTD     | 2    | 
| SEG3    | PORTD     | 3    | 

---

## Features

- Demonstrates **dual 7-segment display control** (common cathode & anode)
- Uses **ECUAL 7-Segment driver APIs**:
  - `seven_segment_initialize()`
  - `seven_segment_write_number()`
- Supports **0–9 counting**
- Delay-based update using `__delay_ms()`
- Simple modular design for easy integration into other projects

---

## 📌 Usage

1. Include the application header in your main application:

```c
#include "7_segment_app.h"
```

2. Call the `Seven_Segment_app()` function in your main:

```c
int main(void) {
    Seven_Segment_app();
    return 0;
}
```

3. The counter will:

- Increment from 0 to 9 on the **common cathode display**
- Display the complement (9–0) on the **common anode display**
- Update every 500 ms

---

## 💡 Notes

- Make sure **ECUAL layer** is initialized before calling this application.
- Adjust **GPIO pins** in `7_segment_app.c` if your hardware wiring differs.
- Proteus simulation files are provided for quick verification.
- `.cof` files in the `build` folder can be loaded into **MPLAB X** for debugging.

## 👤 Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer – MCU & Low-Level Systems  

🔗 LinkedIn:  
https://www.linkedin.com/in/abdelmoniem-ahmed/

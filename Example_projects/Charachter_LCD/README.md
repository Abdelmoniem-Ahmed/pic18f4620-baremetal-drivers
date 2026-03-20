# Character LCD Example – PIC18F4620

![C](https://img.shields.io/badge/language-C-blue)
![ECUAL](https://img.shields.io/badge/layer-ECUAL-yellow)
![MCU](https://img.shields.io/badge/mcu-PIC18F4620-orange)

This example demonstrates the use of the **Character LCD ECUAL driver** (HD44780-based, 4-bit mode) with a PIC18F4620 microcontroller.  
It shows **string display**, **custom characters**, and **dynamic updates**, simulating a **battery charging/discharging display** with **Wi-Fi** and **Bluetooth indicators**.

---


## 📁 Folder Structure

```text
Seven_Segment/
│
├── Chr_LCD_app.h           # Application header
├── Chr_LCD_app.c           # Application source
├── Proteus/                # Proteus simulation project files
└── Builds/                 # Compiled .cof/debug files for MPLAB X
```

---

## Pin Configuration

### Data Pins (4-bit Mode)

| LCD Pin | Port      | Pin  | 
|---------|-----------|------|
| D4      | PORTD     | PIN0 | 
| D5      | PORTD     | PIN1 | 
| D6      | PORTD     | PIN2 | 
| D7      | PORTD     | PIN3 | 
 
### Control Pins

| LCD Pin | Port      | Pin  | 
|---------|-----------|------|
| RS      | PORTC     | 6    | 
| EN      | PORTC     | 7    | 

>Ensure these pins match your hardware wiring. Adjust the `Chr_LCD_4Bit` struct in `Chr_LCD_app.c` if necessary.

---

## Features

- **4-bit LCD interface**
- **Display strings** at specific rows and columns
- **Custom characters**:
  - Full, 80%, 50%, 20%, and empty battery icons
  - Wi-Fi and Bluetooth icons
- **Dynamic animations**:
  - Display shifting left/right
  - Simulated battery charging/discharging
- Uses **ECUAL LCD driver APIs**:
  - `lcd_4bit_initialize()`
  - `lcd_4bit_send_string_pos()`
  - `lcd_4bit_send_custom_char()`
  - `lcd_4bit_send_command()`

---

## 📌 Usage

1. Include the application header in your main application:

```c
#include "Chr_LCD_app.h"
```

2. Call the `Chr_LCD_app()` function in your main:

```c
int main(void) {
    Chr_LCD_app();
    return 0;
}
```

3. The application will:

- Initialize the LCD in 4-bit mode
- Display user name and title
- Show battery, Wi-Fi, and Bluetooth custom icons
- Animate display left/right
- Simulate battery discharge and charging cycles with custom characters

---

## 💡 Notes

- **ECUAL layer initialization** must be done before running the application if integrating with other modules.
- **Delays** (`__delay_ms`) are used for timing; adjust as needed.
- Proteus simulation files are included for testing without hardware.
- `.cof`files in the `Builds` folder can be loaded into MPLAB X for debugging.
- Maximum string length per line: 20 characters (`Chr_Lcd_MAX_LEN`).

## 👤 Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer – MCU & Low-Level Systems  

🔗 LinkedIn:  
https://www.linkedin.com/in/abdelmoniem-ahmed/

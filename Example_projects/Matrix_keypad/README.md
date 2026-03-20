# Matrix Keypad Example – PIC18F4620

![C](https://img.shields.io/badge/language-C-blue)
![ECUAL](https://img.shields.io/badge/layer-ECUAL-yellow)
![MCU](https://img.shields.io/badge/mcu-PIC18F4620-orange)

This example demonstrates the use of a **4x4 Matrix Keypad ECUAL driver** with a **Character LCD ECUAL driver** on a PIC18F4620 microcontroller.  
It reads key presses from the keypad and displays the corresponding character on the LCD. A **10ms Timer1 interrupt** is used for keypad scanning.

---

## 📁 Folder Structure

```text
Matrix_Keypad/
│
├── Matrix_Keypad_app.h        # Application header
├── Matrix_Keypad_app.c        # Application source
├── Proteus/                   # Proteus simulation project files
└── Builds/                    # Compiled .cof/debug files for MPLAB X
```

---

## Pin Configuration

### Keypad (4x4 Matrix)

| Row     | Port      | Pin  | Direction |
|---------|-----------|------|-----------|
| R0      | PORTC     | PIN0 | Output    |
| R1      | PORTC     | PIN1 | Output    | 
| R2      | PORTC     | PIN2 | Output    |
| R3      | PORTC     | PIN3 | Output    |
 
| Column  | Port      | Pin  | Direction |
|---------|-----------|------|-----------|
| C0      | PORTC     | PIN4 | Input     |
| C1      | PORTC     | PIN5 | Input     |
| C2      | PORTC     | PIN6 | Input     |
| C3      | PORTC     | PIN7 | Input     |
 
### Character LCD (4-bit Mode)

| LCD Pin | Port      | Pin  |
|---------|-----------|------|
| D4      | PORTB     | PIN4 |
| D5      | PORTB     | PIN5 |
| D6      | PORTB     | PIN6 |
| D7      | PORTB     | PIN7 |
| RS      | PORTD     | PIN5 |
| EN      | PORTD     | PIN4 |
 
 
> Ensure the pins match your hardware wiring. Adjust `matrix_keypad` and `Chr_Lcd_4Bit` structs in `Matrix_Keypad_app.c` if needed. 

---

## Features

- **4x4 Matrix Keypad scanning**
- **Character LCD 4-bit interface**
- **Display pressed key on LCD**
- **Timer1-based polling** (10ms) for debounce handling
- **Modular and reusable ECUAL drivers**:
  - `keypad_initialize()`
  - `Keypad_Update()`
  - `lcd_4bit_initialize()`
  - `lcd_4bit_send_char_data()`

---

## 📌 Usage

1. Include the application header in your main application:

```c
#include "Matrix_Keypad_app.h"
```

2. Call the `Matrix_Keypad_Led_App()` function in your main:

```c
int main(void) {
    Matrix_Keypad_Led_App();
    return 0;
}
```

3. The application will:

- Initialize the keypad and LCD
- Continuously scan for pressed keys using Timer1 interrupt
- Display the corresponding character on the LCD when a key is pressed

---

## 💡 Notes

- **Timer1** is configured for a 10ms interrupt to handle keypad scanning and debounce.
- Only one key press is displayed at a time.
- Proteus simulation files are included for testing without hardware.
- `.cof` files in the `Builds` folder can be loaded into MPLAB X for debugging.

---

## 👤 Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer – MCU & Low-Level Systems  

🔗 LinkedIn:  
https://www.linkedin.com/in/abdelmoniem-ahmed/

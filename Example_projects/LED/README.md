# LED Blink Example – PIC18F4620

![C](https://img.shields.io/badge/language-C-blue)
![ECUAL](https://img.shields.io/badge/layer-ECUAL-yellow)
![MCU](https://img.shields.io/badge/mcu-PIC18F4620-orange)

This example demonstrates the use of the **LED ECUAL driver** and **HAL GPIO** to blink LEDs connected to PORTC of the PIC18F4620 microcontroller.  
It includes **two approaches**: using the ECUAL LED driver and a more **efficient direct HAL GPIO port write** method.

---

## 📁 Folder Structure

```text
LED_Blink/
│
├── Led_Blink_app.h        # Application header
├── Led_Blink_app.c        # Application source
├── Proteus/               # Proteus simulation project files
└── Builds/                # Compiled .cof/debug files for MPLAB X
```

---

## Pin Configuration

| LED Pin | Port      | Pin  | 
|---------|-----------|------|
| LED0    | PORTC     | PIN0 | 
| LED1    | PORTC     | PIN1 | 
| LED2    | PORTC     | PIN2 |  
| LED3    | PORTC     | PIN3 | 
| LED4    | PORTC     | PIN4 | 
| LED5    | PORTC     | PIN5 | 
| LED6    | PORTC     | PIN6 |  
| LED7    | PORTC     | PIN7 | 
 
> Ensure these pins match your hardware wiring. The LEDs are initialized in `Led_Blink_app.c`. 

---

## Features

- **LED control using ECUAL driver** (`led_initialize`, `led_turn_on`, `led_turn_off`, `led_turn_toggle`)
- **Direct GPIO port control** for faster and efficient LED blinking
- **Multiple blink patterns**:  
  - Alternating LEDs (0, 2, 4, 6)
  - Full port toggling
  - Sequential LED running lights
- **Delay-based timing** using `__delay_ms()`

---

## 📌 Usage

1. Include the application header in your main application:

```c
#include "Led_Blink_app.h"
```

2. Call the `Led_Blink_app()` function in your main:

```c
int main(void) {
    // Using ECUAL LED driver
    Led_Blink_app();
    
    // Or, using more efficient HAL GPIO method
    // Led_Blink_Hal_app();
    
    return 0;
}
```

3. The application will:

- Initialize all 8 LEDs on PORTC
- Execute different blink sequences continuously
- Demonstrate both the ECUAL driver and direct GPIO port write efficiency

---

## 💡 Notes

- **ECUAL layer** must be initialized if integrating with other modules.
- The HAL GPIO approach is **faster** than toggling each LED individually using the driver.
- Proteus simulation files are included for testing without hardware.
- `.cof` files in the `Builds` folder can be loaded into MPLAB X for debugging.

## 👤 Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer – MCU & Low-Level Systems  

🔗 LinkedIn:  
https://www.linkedin.com/in/abdelmoniem-ahmed/

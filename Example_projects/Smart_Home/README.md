# Smart Home Master MCU – PIC18F4620

> 🚀 A complete embedded systems project demonstrating real-time control, communication, and data logging using PIC18F4620.

<p align="center">
  <img src="media/smart_home_project.gif" width="600">
</p>

## 🎥 Demo

- 📹 Full Demo: [Watch Video](media/smart_home_full_demo.mp4)
- ⚡ Short Demo: [Watch Video](media/smart_home_short_demo.mp4)

![C](https://img.shields.io/badge/language-C-blue)
![ECUAL](https://img.shields.io/badge/layer-ECUAL-yellow)
![MCU](https://img.shields.io/badge/mcu-PIC18F4620-orange)

This project demonstrates a **Smart Home System Master MCU** using a PIC18F4620. 
It simulates a **distributed embedded system** with real-time communication between multiple microcontrollers. 
The master reads **temperature**, **date & time**, and **keypad input**, displays info on a **Character LCD**, logs data to **EEPROM**, and communicates with a **Slave MCU** via **I2C**.  
It also features **password authentication** and **real-time monitoring**.

## 🚀 Highlights

- 🔐 Secure password system with lockout protection
- ⏱️ Real-time scheduling using Timer0
- 🔁 Master-Slave I2C architecture
- 💾 Persistent EEPROM data logging
- 🧩 Fully layered architecture (MCAL / ECUAL / APP)

## 🧩 Key Concepts Demonstrated

- Embedded state machines (password system)
- Interrupt-driven design (Timer0, I2C)
- Real-time scheduling (multi-rate tasks)
- Inter-MCU communication (I2C Master/Slave)
- Hardware abstraction layering (MCAL / ECUAL)

---


## 📁 Folder Structure

```text
Smart_Home/
│
├── smart_home_app.h          # Master application header
├── smart_home_app.c          # Master application source
├── Proteus/                  # Proteus simulation project files
├── Master_Builds/            # Compiled .cof/debug files for MPLAB X
├── media/
│   ├── smart_home_full_demo.mp4
│   ├── smart_home_short_demo.mp4
│   └── smart_home_project.gif
├── Slave_MCU/
│   ├── Slave_MCU_main_app.h
│   ├── Slave_MCU_main_app.c
│   └── Slave_Builds/
```

---

## 🧠 System Architecture

- **Master MCU (PIC18F4620):**
  - Handles user input (Keypad)
  - Displays data (LCD)
  - Reads sensors (TC74, DS1307)
  - Logs data to EEPROM
  - Sends temperature to Slave MCU

- **Slave MCU (PIC18F4620):**
  - Receives temperature via I2C
  - Controls motor (fan) using PWM
  - Provides real-time response to environment

- **Communication:**
  - I2C (Master → Slave)
  - UART (Debugging output)

---

## Features

- **Password-protected system** (3 attempts max, 30s lockout)
- **4x4 Matrix Keypad input**
- **Character LCD 4-bit interface** (time, date, temperature)
- **Temperature monitoring** via TC74 sensor
- **Real-time clock** with DS1307
- **Data logging** to EEPROM (last, max, min temperature)
- **I2C communication** to Slave MCU
- **Timer0-based flags** for 1s, 5s, 10s tasks
- Modular **ECUAL** and **MCAL drivers**:
  - `keypad_initialize()`, `Keypad_Update()`
  - `lcd_4bit_initialize()`, `lcd_4bit_send_string_pos()`, `lcd_4bit_send_custom_char()`
  - `MSSP_I2C_Init()`, `MSSP_I2C_Master_Write_Blocking()`
  - `EUSART_ASYNC_Init()`, `EUSART_ASYNC_Write_String_Blocking()`
  - `TempSensor_TC74_Read_Temp()`
  - `RealTimeClock_DS1307_Get_Date_Time()`

---

## Pin Configuration

### Keypad (4x4 Matrix)

| Row     | Port      | Pin  | Direction |
|---------|-----------|------|-----------|
| R0      | PORTD     | PIN0 | Output    |
| R1      | PORTD     | PIN1 | Output    | 
| R2      | PORTD     | PIN2 | Output    |
| R3      | PORTD     | PIN3 | Output    |
 
| Column  | Port      | Pin  | Direction |
|---------|-----------|------|-----------|
| C0      | PORTD     | PIN4 | Input     |
| C1      | PORTD     | PIN5 | Input     |
| C2      | PORTD     | PIN6 | Input     |
| C3      | PORTD     | PIN7 | Input     |
 
### Character LCD (4-bit Mode)

| LCD Pin | Port      | Pin  |
|---------|-----------|------|
| D4      | PORTB     | PIN4 |
| D5      | PORTB     | PIN5 |
| D6      | PORTB     | PIN6 |
| D7      | PORTB     | PIN7 |
| RS      | PORTA     | PIN3 |
| EN      | PORTA     | PIN2 |
 
 
> Adjust pins in `smart_home_app.c` if your hardware wiring differs.

---

## 📌 Usage (Master MCU)

1. Include the application header in your main application:

```c
#include "smart_home_app.h"
```

2. Call the `Smart_Home_App()` function in your main:

```c
int main(void) {
    Smart_Home_App();
    return 0;
}
```

3. Application flow:

- Prompt user for **password** (max 3 attempts)
- Display **welcome messages** on LCD
- Continuously read:
  - **Temperature**
  - **Date & Time**
- Update LCD and send **temperature** to **Slave MCU** via I2C
- Log temperature values to **EEPROM** every 10 seconds
- Send debug data via **UART** every 5 seconds

---

## 🔄 Slave MCU Integration

The Slave MCU works as a secondary control node:

- Receives temperature data via I2C
- Controls a DC motor (fan) using PWM
- Adjusts speed based on temperature ranges
- Provides over-temperature alert via LED

📁 Location:
- `Slave_MCU/` folder contains full implementation

➡ See Slave README for full details

---

## 💡 Notes

- **Timer0** flags control 1s, 5s, and 10s tasks (LCD update, UART, EEPROM logging).
- **EEPROM addresses**:
  - `EEPROM1_ADDRESS`: every temperature value
  - `EEPROM2_ADDRESS`: max, min, last temperature
- Adjust **password**, **I2C addresses**, and **EEPROM addresses** in the header file.
- Proteus simulation files are included for testing without hardware.
- `.cof` files in **Master_Builds/** and **Slave_Builds/** can be loaded into MPLAB X for debugging.

---

## 👤 Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer – MCU & Low-Level Systems  

🔗 LinkedIn:  
https://www.linkedin.com/in/abdelmoniem-ahmed/

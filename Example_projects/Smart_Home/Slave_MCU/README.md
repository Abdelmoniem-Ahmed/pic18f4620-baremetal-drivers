# Smart Home Slave MCU – PIC18F4620

![C](https://img.shields.io/badge/language-C-blue)
![ECUAL](https://img.shields.io/badge/layer-ECUAL-yellow)
![MCU](https://img.shields.io/badge/mcu-PIC18F4620-orange)

This project implements the **Slave MCU** in a Smart Home system using a PIC18F4620.  
It receives **temperature data via I2C** from the Master MCU and controls a **DC motor (fan)** using **PWM** based on temperature levels.  
It also uses an **LED indicator** for high-temperature alerts.

---


## 📁 Folder Structure

```text
Slave_MCU/
│
├── Slave_MCU_main_app.h      # Slave application header
├── Slave_MCU_main_app.c      # Slave application source
└── Slave_Builds/             # Compiled .cof/debug files for MPLAB X
```

---

## Features

- **I2C Slave communication** with Master MCU
- **Interrupt-driven data reception**
- **Temperature-based control system**
- **PWM-based motor control (fan simulation)**
- **DC motor direction control**
- **Real-time response to external MCU commands**
- **Over-temperature LED alert**
- Uses **MCAL** and **ECUAL drivers**:
  - `MSSP_I2C_Init()`
  - `CCP_PWM_Start()`, `CCP_PWM_Set_Duty()`
  - `dc_motor_initialize()`, `dc_motor_move_forward()`, `dc_motor_move_backward()`
  - `timer2_init()`
  - `led_initialize()`, `led_turn_on()` , `led_turn_off()`

---

## 🔗 Communication Overview

- **Protocol:** I2C (MSSP module)
- **Mode:** Slave
- **Slave Address:** `0x70`
- **Interrupt Handling:** Enabled (with clock stretching)
- **Data Received:** Temperature value (°C) from Master MCU

---

## System Behavior

The Slave MCU receives temperature from the Master via I2C and reacts as follows:

| **Temperature Range (°C)** | **Action**                         | **PWM Duty** |
|----------------------------|------------------------------------|--------------|
| 5 < Temp < 20              | Motor backward (low-speed cooling) | 40%          |
| 20 ≤ Temp < 35             | Motor forward                      | 40%          |
| 35 ≤ Temp < 45             | Motor forward                      | 50%          |
| 45 ≤ Temp < 50             | Motor forward                      | 80%          |
| Temp ≥ 50                  | Motor forward + LED ON             | 100%         |

---

## Pin Configuration

### I2C (Slave Mode)

| Signal  | Description     |
|---------|-----------------|
| SDA     | I2C Data line   |
| SCL     | I2C Clock line  |
| Address | `0x70`          |
 
### DC Motor 
 
| Motor Pin  | Port    | Pin  |
|------------|---------|------|
| IN1        | PORTC   | PIN0 |
| IN2        | PORTC   | PIN1 |
 
### PWM Output (CCP1)

| Function   | Port    | Pin  |
|------------|---------|------|
| PWM        | PORTC   | PIN2 |
 
### LED Indicator 
 
| LED        | Port    | Pin  |
|------------|---------|------|
| Warning    | PORTD   | PIN0 | 
 
 
> Adjust pins in `Slave_MCU_main_app.c` if your hardware wiring differs.

---

## 📌 Usage

1. Include the application header in your main application:

```c
#include "Slave_MCU_main_app.h"
```

2. Call the `slave_mcu_main_app()` function in your main:

```c
int main(void) {
    slave_mcu_main_app();
    return 0;
}
```

## How It Works

1. **Initialization Phase**
  - I2C initialized in **Slave mode**
  - LED initialized
  - System waits for the first communication from the Master MCU

2. **Interrupt Handling**
  - I2C interrupt receives temperature value
  - Clock stretching ensures safe data reception
  - System initialization flag is set after first valid communication
  
3. **Main Loop**
  - PWM and motor initialized after communication starts
  - Temperature is continuously evaluated
  - Motor speed and direction adjusted dynamically
  - LED turns ON at high temperature (≥ 50°C)

--- 

## 🔄 Integration with Master MCU

This Slave MCU is designed to work with the Smart Home Master application:

- Receives temperature data via I2C
- Reacts in real-time to environmental changes
- Acts as a control node in a distributed embedded system

Ensure the Master MCU is configured with:
- Matching I2C address (`0x70`)
- Periodic temperature transmission

---

## 💡 Notes

- **Clock Stretching** is used in I2C to ensure reliable communication.
- PWM frequency is set to **5 kHz** using **Timer2** + **CCP1**.
- The system is **fully interrupt-driven for communication**.
- The Slave MCU depends on the Master MCU for temperature updates.
- `.cof` files in `Slave_Builds/` can be used for debugging in MPLAB X.
- Designed to work with the Smart Home Master project.

---

## 👤 Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer – MCU & Low-Level Systems  

🔗 LinkedIn:  
https://www.linkedin.com/in/abdelmoniem-ahmed/

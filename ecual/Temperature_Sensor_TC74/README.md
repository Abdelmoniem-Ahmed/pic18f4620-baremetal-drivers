# TC74 Digital Temperature Sensor Driver – ECUAL

## Overview
This driver provides a **high-level ECUAL interface** for interacting with the **Microchip TC74 digital temperature sensor** over I2C using the **MSSP I2C driver** on the **PIC18F4620**.

The TC74 sensor returns temperature as an **8-bit signed value** in **degrees Celsius**, making it easy to integrate into embedded applications.

---

## ✅ Key Capabilities

- Read temperature as an 8-bit signed value (°C)
- Built on the **MSSP I2C driver** (polling or interrupt-based)
- Transparent I2C communication with proper start/stop sequences
- Supports custom I2C slave addresses

---

## 🎯 Target MCU & Toolchain

- **MCU** : PIC18F4620
- **Compiler** : XC8 (MPLAB X IDE compatible)
- **Layer** : ECUAL
- **Communication** : I2C (via MSSP driver)

---

## ⚙️ Features

- Single-byte temperature read  
- Uses proper I2C sequence: START → WRITE → REGISTER → REPEATED START → READ → STOP  
- Compatible with sensor I2C address `0x4D` by default  
- Returns `E_OK` or `E_NOT_OK` for robust error handling

---

## 📚 API Functions

### Read Temperature

```c
Std_ReturnType TempSensor_TC74_Read_Temp(
    uint8 sensor_address,  // I2C slave address of TC74
    sint8 *temp            // Pointer to store temperature in °C
);
```

**Notes**:

- Reads the **temperature register (0x00)** from the TC74 sensor
- Returns `E_OK` on success, `E_NOT_OK` on failure or if pointer is `NULL`.
- Temperature value is **signed 8-bit**, representing degrees Celsius

---

## Example Usage

```c
#include "Temperature_Sensor_TC74.h"
#include "I2C_APIs.h"

mssp_i2c_t i2c_master = {
    .i2c_clock = 100000, // 100 kHz
    .i2c_cfg = {
        .i2c_mode = MSSP_I2C_MASTER_MODE,
        .i2c_slew_rate = I2C_SLEW_RATE_ENABLE_100kHZ,
        .i2c_SMBus_Control = I2C_SMBUS_DISABLE
    }
};

sint8 temperature;

int main(void){
    // Initialize I2C master
    MSSP_I2C_Init(&i2c_master);

    // Read temperature from TC74 sensor
    if(TempSensor_TC74_Read_Temp(TEMP_SENSOR_ADDRESS, &temperature) == E_OK){
        // Successfully read temperature
        // Use 'temperature' variable here
    }

    while(1);
}
```

**Notes**:

- Make sure **MSSP I2C driver** is initialized before reading temperature
- Returned value is **signed**: negative temperatures are supported
- Always check return values (`E_OK` / `E_NOT_OK`) for robust error handling
- Default I2C address is `0x4D`, but it can be configured if your sensor uses a different address

---

## Error Handling

- `E_OK` – Temperature read successfully
- `E_NOT_OK` – Communication failure or NULL pointer

## Dependencies
- MSSP I2C driver (`I2C_APIs.h`)
- Standard types (`std_types.h`)


## Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer – MCU & Low-Level Systems

🔗 **LinkedIn**  
https://www.linkedin.com/in/abdelmoniem-ahmed/

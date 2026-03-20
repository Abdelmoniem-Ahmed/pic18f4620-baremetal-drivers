# 24C02C I2C EEPROM Driver – ECUAL

## Overview
This driver provides a **high-level ECUAL** interface for interacting with the **24C02C EEPROM** over I2C using the **MSSP I2C driver** on the **PIC18F4620**.

It simplifies reading and writing **single bytes** to specific memory addresses, making EEPROM integration fast and reliable for embedded projects.


## ✅ Key Capabilities

- Write a single byte to any memory address (0x00–0xFF)
- Read a single byte from any memory address (0x00–0xFF)
- Built on the **MSSP I2C driver** (polling or interrupt-based)
- Handles I2C communication transparently

---

## 🎯 Target MCU & Toolchain

- **MCU** : PIC18F4620
- **Compiler** : XC8 (MPLAB X IDE compatible)
- **Layer** : ECUAL
- **Communication** : I2C (via MSSP driver)

---

## ⚙️ Features

- **Write Byte**: Writes a single byte to a given memory address with internal cycle delay.
- **Read Byte**: Reads a single byte from a given memory address.
- Fully compatible with **0x50 / 0x51 I2C addresses**.
- Returns `E_OK` or `E_NOT_OK` for error handling.

---

## 📚 API Functions

### Write a Byte

```c
Std_ReturnType EEPROM_24C02C_Write_Byte(
    uint8 eeprom_address,  // I2C address: 0x50 or 0x51
    uint8 mem_address,     // Memory address inside EEPROM: 0x00–0xFF
    uint8 data             // Byte to write
);
```

**Notes**:

- Adds a small delay (~5 ms) to allow EEPROM internal write cycle to complete.
- Returns `E_OK` on success, `E_NOT_OK` on failure.

### Read a Byte

```c
Std_ReturnType EEPROM_24C02C_Read_Byte(
    uint8 eeprom_address,  // I2C address: 0x50 or 0x51
    uint8 mem_address,     // Memory address inside EEPROM: 0x00–0xFF
    uint8 *data            // Pointer to store read byte
);
```

**Notes**:

- Reads a single byte from the EEPROM.
- Returns `E_OK` on success, `E_NOT_OK` on failure.

---

## Example Usage

```c
#include "EEPROM_24C02C.h"
#include "I2C_APIs.h"

mssp_i2c_t i2c_master = {
    .i2c_clock = 100000, // 100 kHz
    .i2c_cfg = {
        .i2c_mode = MSSP_I2C_MASTER_MODE,
        .i2c_slew_rate = I2C_SLEW_RATE_ENABLE_100kHZ,
        .i2c_SMBus_Control = I2C_SMBUS_DISABLE
    }
};

uint8 data;

int main(void){
    // Initialize I2C Master
    MSSP_I2C_Init(&i2c_master);

    // Write 0xAB to EEPROM address 0x10
    EEPROM_24C02C_Write_Byte(0x50, 0x10, 0xAB);

    // Read back the value
    EEPROM_24C02C_Read_Byte(0x50, 0x10, &data);

    while(1);
}
```

--- 

## Notes & Tips

- Ensure the **MSSP I2C driver** is initialized before using EEPROM functions.
- EEPROM write cycles are slow (~5 ms max for 24C02C). For high-speed applications, consider adding polling or write-complete checks.
- Always check return values (`E_OK` / `E_NOT_OK`) for robust error handling.

---

## Error Handling

- `E_OK` – Operation successful
- `E_NOT_OK` – Communication failure or invalid pointer

## Dependencies
- MSSP I2C driver (`I2C_APIs.h`)
- Standard types (`std_types.h`)


## Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer – MCU & Low-Level Systems

🔗 **LinkedIn**  
https://www.linkedin.com/in/abdelmoniem-ahmed/

# DS1307 Real-Time Clock (RTC) Driver – ECUAL

## Overview
This driver provides a **high-level ECUAL interface** for interacting with the **DS1307 Real-Time Clock (RTC)** over I2C using the **MSSP I2C driver** on the **PIC18F4620**.

It allows reading the current **date and time** from the DS1307 device. All values are returned in **BCD format**, making it easy to convert to decimal in the application layer if needed.

---

## ✅ Key Capabilities

- Read current **time**: hours, minutes, seconds  
- Read current **date**: day, month, year  
- Built on the **MSSP I2C driver** (polling or interrupt-based)  
- Transparent I2C communication with proper start/stop sequences  
- Robust error handling with `E_OK` / `E_NOT_OK` return values  

---

## 🎯 Target MCU & Toolchain

- **MCU** : PIC18F4620
- **Compiler** : XC8 (MPLAB X IDE compatible)
- **Layer** : ECUAL
- **Communication** : I2C (via MSSP driver)

---

## ⚙️ Features

- Reads **all key RTC registers**: seconds, minutes, hours, day, month, year  
- Values returned exactly as stored in DS1307 (BCD format)  
- Uses MSSP I2C driver for communication  
- Returns `E_OK` on success or `E_NOT_OK` on failure  

---

## 📚 API Functions

### Read Date & Time

```c
Std_ReturnType RealTimeClock_DS1307_Get_Date_Time(
    RealTimeClock_DS1307_t *time  // Pointer to structure to store RTC values
);
```

**Notes**:

- Reads the following DS1307 registers:
  - Seconds (0x00)
  - Minutes (0x01)
  - Hours (0x02)
  - Day (0x04)
  - Month (0x05)
  - Year (0x06)
- Values are in **BCD format**; conversion to decimal is application-dependent.
- Returns `E_NOT_OK` if the pointer is `NULL` or if I2C communication fails.

---

## Example Usage

```c
#include "RealTimeClock_DS1307.h"
#include "I2C_APIs.h"

mssp_i2c_t i2c_master = {
    .i2c_clock = 100000, // 100 kHz
    .i2c_cfg = {
        .i2c_mode = MSSP_I2C_MASTER_MODE,
        .i2c_slew_rate = I2C_SLEW_RATE_ENABLE_100kHZ,
        .i2c_SMBus_Control = I2C_SMBUS_DISABLE
    }
};

RealTimeClock_DS1307_t rtc_data;

int main(void){
    // Initialize I2C Master
    MSSP_I2C_Init(&i2c_master);

    // Read date and time from DS1307 RTC
    if(RealTimeClock_DS1307_Get_Date_Time(&rtc_data) == E_OK){
        // Successfully read RTC
        // Use rtc_data.Hours, rtc_data.Minutes, rtc_data.Seconds
        // Use rtc_data.Day, rtc_data.Month, rtc_data.Year
    }

    while(1);
}
```

**Notes**:

- Make sure **MSSP I2C driver** is initialized before reading RTC data.
- Returned values are in **BCD format**; convert to decimal if needed
- Always check return values (`E_OK` / `E_NOT_OK`) for robust error handling
- Default I2C address is `0x68` for DS1307

---

## Error Handling

- `E_OK` – Date and time read successfully
- `E_NOT_OK` – Communication failure or NULL pointer

## Dependencies
- MSSP I2C driver (`I2C_APIs.h`)
- Standard types (`std_types.h`)


## Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer – MCU & Low-Level Systems

🔗 **LinkedIn**  
https://www.linkedin.com/in/abdelmoniem-ahmed/

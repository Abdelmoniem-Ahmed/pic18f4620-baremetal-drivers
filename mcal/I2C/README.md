# 🟢 MSSP I2C Driver – PIC18F4620

## 📌 Overview

This driver provides a clean and configurable **MCAL interface** for the **MSSP peripheral in I2C mode** on the **PIC18F4620** microcontroller.  

It supports:

- **Master mode** and **Slave mode** (7-bit / 10-bit addressing)  
- Start / Repeated Start / Stop generation  
- ACK / NACK control  
- Blocking read/write operations  
- Optional **interrupt support** with callback mechanism  
- Bus collision detection  

The driver follows **bare-metal embedded best practices** and can be used in **polling-based** or **interrupt-driven** applications.  

---

## 🎯 Target MCU & Toolchain

- **MCU:** PIC18F4620  
- **Compiler:** XC8 (MPLAB X IDE compatible)  
- **Layer:** MCAL  

---

## ⚙️ Features

### Master Mode

- Clock frequency configuration  
- Blocking write and read operations  
- Start / Repeated Start / Stop condition generation  
- Optional interrupts for transfer completion  

### Slave Mode

- 7-bit or 10-bit address configuration  
- General Call enable/disable  
- Interrupts for receive, overflow, and write collision  

### Interrupt Support

- Default interrupt handler for receive/overflow events  
- Bus collision interrupt handler  
- Optional interrupt priority configuration  

---

## 🧩 Pin Mapping

| I2C Pin | PIC18F4620 Pin | Description |
|---------|----------------|-------------|
| SDA     | RC4            | Serial Data Line |
| SCL     | RC3            | Serial Clock Line |

> The pins are configured as **inputs** by default. The driver controls the direction automatically.

---

## 📚 Data Structures

### `i2c_config_t`

Holds low-level configuration parameters:

```c
typedef struct{
    MSSP_I2C_Mode_Select  i2c_mode_cfg;
    uint8 i2c_slave_address;  
    uint8 i2c_mode : 1;
    uint8 i2c_slew_rate : 1;
    uint8 i2c_SMBus_Control : 1;
    uint8 i2c_general_call : 1;
    uint8 i2c_master_receive_mode : 1;
    uint8 i2c_reserved : 3;
} i2c_config_t;
```

### `mssp_i2c_t`

Holds high-level configuration including clock, addresses, and interrupt callbacks:

```c
typedef struct{
    uint32 i2c_clock; // Master clock frequency
    i2c_config_t i2c_cfg;

#if INTERRUPT_FEATURE_ENABLE == MSSP_I2C_INTERRUPT_FEATURE_ENABLE
    void (*MSSP_I2C_DEFAULT_INTERRUPT_HANDLER)(void);
    void (*MSSP_I2C_REPORT_RECEIVE_OVERFLOW)(void);
#endif

#if INTERRUPT_FEATURE_ENABLE == MSSP_I2C_BUS_COL_INTERRUPT_FEATURE_ENABLE
    void (*MSSP_I2C_REPORT_WRITE_COLLISION)(void);
#endif

#if INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE
    INTERRUPT_Priority_cfg mssp_i2c_int_priority_level;
    INTERRUPT_Priority_cfg mssp_i2c_Bus_COL_int_priority_level;
#endif

} mssp_i2c_t;
```

## API Functions

### Initialization & Deinitialization

```c
Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj);
```

- Configures master/slave mode, clock, slave address, slew rate, SMBus, and interrupts.
- Deinitialization disables module and interrupts

### Master Mode Operations

- **Write/Read Blocking**: waits for transmission/reception to complete.
- **ACK/NACK**: master can control acknowledge for received bytes.
- **Start/Stop**: generates proper bus conditions according to I2C protocol.

## Example Usage

```c
#include "I2C_APIs.h"

mssp_i2c_t i2c_master = {
    .i2c_clock = 100000, // 100 kHz
    .i2c_cfg = {
        .i2c_mode = MSSP_I2C_MASTER_MODE,
        .i2c_slew_rate = I2C_SLEW_RATE_ENABLE_100kHZ,
        .i2c_SMBus_Control = I2C_SMBUS_DISABLE
    }
};

uint8 ack;
uint8 data;

int main(void){
    MSSP_I2C_Init(&i2c_master);

    MSSP_I2C_Master_Send_Start(&i2c_master);
    MSSP_I2C_Master_Write_Blocking(&i2c_master, 0x50, &ack);
    MSSP_I2C_Master_Read_Blocking(&i2c_master, I2C_MASTER_SEND_NOT_ACK, &data);
    MSSP_I2C_Master_Send_Stop(&i2c_master);

    MSSP_I2C_DeInit(&i2c_master);
    return 0;
}
```

## Notes & Tips

- Make sure `_XTAL_FREQ` is defined in your project for correct clock calculations.
- For **non-blocking operation**, a state machine with interrupt callbacks can be implemented.
- Always check `ACK` after writes to ensure proper communication.
- Supports both **polling and interrupt-driven** modes.

## Error Handling

- All APIs validate input pointers
- Return values:
  - `E_OK` on success
  - `E_NOT_OK` on invalid parameters

## Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer

🔗 **LinkedIn**  
https://www.linkedin.com/in/abdelmoniem-ahmed/

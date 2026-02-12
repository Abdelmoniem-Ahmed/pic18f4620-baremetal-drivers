# HAL EUSART Driver – PIC18F4620

## Overview

The **HAL EUSART (Enhanced Universal Synchronous Asynchronous Receiver Transmitter) Driver** provides a clean and configurable **MCAL interface** for the **EUSART peripheral** of the **PIC18F4620** microcontroller.  

It supports:

- Asynchronous and synchronous modes  
- 8-bit and 16-bit baud rate generation  
- High-speed and low-speed asynchronous modes  
- 9-bit data transmission and reception  
- Interrupt-driven TX/RX handling  
- Framing and overrun error detection  

The driver follows **bare-metal embedded best practices** and is designed for **MCAL-layer integration**.

**Author:** Abdelmoniem Ahmed  
**LinkedIn:** [https://www.linkedin.com/in/abdelmoniem-ahmed/]

---

## Features

- **EUSART Modes:** Synchronous / Asynchronous  
- **Baud Rate Generator:** 8-bit / 16-bit, High / Low Speed  
- **Transmission:** 8-bit / 9-bit data, blocking and non-blocking  
- **Reception:** 8-bit / 9-bit data, blocking and non-blocking  
- **Interrupts:** TX, RX, Framing Error (FERR), Overrun Error (OERR)  
- **Error Detection:** Framing error, overrun error  
- **MCAL Layer Compliant:** Clean separation of hardware abstraction  

---

## Files

| File			 | Description           										|
|----------------|--------------------------------------------------------------|
| `hal_eusart.h` | Header file: data types, macros, and function declarations   |
| `hal_eusart.c` | Source file: function implementations and interrupt handlers |

---

## Data Types

### `baudrate_gen_t`
Enumeration for baud rate generator configuration:

- `BAUDRATE_ASYNC_8BIT_LOW_SPEED`
- `BAUDRATE_ASYNC_8BIT_HIGH_SPEED`
- `BAUDRATE_ASYNC_16BIT_LOW_SPEED`
- `BAUDRATE_ASYNC_16BIT_HIGH_SPEED`
- `BAUDRATE_SYNC_8BIT`
- `BAUDRATE_SYNC_16BIT`

### `usart_tx_cfg_t`
Transmitter configuration:

- `usart_tx_enable` – Enable/Disable TX  
- `usart_tx_9bit_enable` – Enable/Disable 9-bit TX  
- `usart_tx_interrupt_enable` – Enable/Disable TX interrupt  
- `eusart_tx_int_priority` – Interrupt priority (Low/High)  

### `usart_rx_cfg_t`
Receiver configuration:

- `usart_rx_enable` – Enable/Disable RX  
- `usart_rx_9bit_enable` – Enable/Disable 9-bit RX  
- `usart_rx_interrupt_enable` – Enable/Disable RX interrupt  
- `eusart_rx_int_priority` – Interrupt priority (Low/High)  

### `usart_error_status_t`
Union to track error status:

- `usart_frame_error_ferr` – Framing error detected/cleared  
- `usart_overrun_error_oerr` – Overrun error detected/cleared  

### `usart_t`
Main EUSART configuration object:

- `baudrate` – Desired baud rate (bps)  
- `baudrate_cfg` – `baudrate_gen_t` mode  
- `usart_tx_cfg` – TX configuration  
- `usart_rx_cfg` – RX configuration  
- `error_status` – Current error flags  
- Callback functions:  
  - `EUSART_TX_DefaultInterruptHandler`  
  - `EUSART_RX_DefaultInterruptHandler`  
  - `EUSART_FERR_DefaultInterruptHandler`  
  - `EUSART_OERR_DefaultInterruptHandler`  

---

## Functions

All functions are declared in `hal_eusart.h`:

### Initialization
```c
Std_ReturnType EUSART_ASYNC_Init(usart_t *_usart_obj);
Std_ReturnType EUSART_ASYNC_DeInit(usart_t *_usart_obj);
```

### Data Reception
```c
Std_ReturnType EUSART_ASYNC_Read_Byte_Blocking(uint8 *_data);
Std_ReturnType EUSART_ASYNC_Read_Byte_NonBlocking(uint8 *_data);
```
### Data Transmission
```c
Std_ReturnType EUSART_ASYNC_Write_Byte_Blocking(uint8 _data);
Std_ReturnType EUSART_ASYNC_Write_String_Blocking(uint8 *_data, uint16 str_length);
Std_ReturnType EUSART_ASYNC_Write_Byte_NonBlocking(uint8 _data);
Std_ReturnType EUSART_ASYNC_Write_String_NonBlocking(uint8 *_data, uint16 str_length);
```

**Note**: For detailed behavior, see the function descriptions in the header file.

### Usage Example

```c
#include "hal_eusart.h"

void main(void) {
    usart_t my_usart;

    /* Configure USART object */
    my_usart.baudrate = 9600;
    my_usart.baudrate_cfg = BAUDRATE_ASYNC_8BIT_LOW_SPEED;
    
    my_usart.usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE;
    my_usart.usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE;
    my_usart.usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE;

    my_usart.usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE;
    my_usart.usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE;
    my_usart.usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;

    my_usart.EUSART_TX_DefaultInterruptHandler = tx_callback;
    my_usart.EUSART_RX_DefaultInterruptHandler = NULL;
    my_usart.EUSART_FERR_DefaultInterruptHandler = NULL;
    my_usart.EUSART_OERR_DefaultInterruptHandler = NULL;

    /* Initialize USART */
    if(EUSART_ASYNC_Init(&my_usart) == E_OK) {
        // USART initialized successfully
    }
}
```

### Notes

- Ensure **TRISC pins** are configured for RX/TX according to hardware.
- Interrupt feature macros (`EUSART_TX_INTERRUPT_FEATURE_ENABLE`, etc.) control ISR integration.
- This driver is **bare-metal** and **MCAL-layer compliant**, suitable for embedded projects and microcontroller abstraction.

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

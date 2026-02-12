# SPI Driver – PIC18F4620

## Overview

This driver provides a clean and configurable **MCAL interface** for the **MSSP (Master Synchronous Serial Port)** peripheral configured in **SPI mode** of the **PIC18F4620** microcontroller.

It supports:

- **SPI Master mode**
- **SPI Slave mode**
- Configurable clock polarity (CKP) 
- Configurable clock edge (CKE) 
- Configurable sampling control (SMP) 
- Full-duplex byte transmission  
- Optional interrupt-driven communication  

The driver is implemented following:

- Bare-metal embedded systems best practices 
- MCAL layered architecture 
- Clear separation between configuration, control, and runtime services 
- Callback-based interrupt handling mechanism  
- Datasheet-compliant register access  

**Author:** Abdelmoniem Ahmed  
**LinkedIn:** [https://www.linkedin.com/in/abdelmoniem-ahmed/]

---

## Features

- ✅ Master mode (Fosc/4, Fosc/16, Fosc/64, Timer2/2)
- ✅ Slave mode (SS pin enabled / disabled)  
- ✅ Configurable clock polarity (Idle High / Idle Low)  
- ✅ Configurable transmit edge selection
- ✅ Master sampling configuration
- ✅ Full-duplex communication (Transmit & Receive)
- ✅ Interrupt support (optional)
- ✅ Interrupt priority support (if enabled)
- ✅ Callback-based ISR handling
- ✅ GPIO abstraction for SPI pins
- ✅ Write collision detection
- ✅ Receive overflow detection
- ✅ Modular and reusable API design

---

## Driver Layer

| Item			 | Description           					  |
|----------------|--------------------------------------------|
| Layer 		 | MCAL (Microcontroller Abstraction Layer)   |
| MCU 			 | PIC18F4620 								  |
| Compiler 		 | XC8										  |
| Peripheral 	 | MSSP (SPI Mode) 							  |

---

## SPI Hardware Mapping

| Signal		 | MCU Pin               					  |
|----------------|--------------------------------------------|
| SDO 		     | RC5   									  | 
| SDI 			 | RC4 			   					          |
| SCK 		     | RC3										  |
| SS 	         | RA5		     							  |

## Configuration Structure

The driver is configured using the `mssp_spi_t` structure:

```c
typedef struct{

#if (INTERRUPT_FEATURE_ENABLE == MSSP_SPI_INTERRUPT_FEATURE_ENABLE)
    void (* MSSP_SPI_DefaultInterruptHandler)(void);
#if (INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE)
    INTERRUPT_Priority_cfg mssp_spi_int_priority_level;
#endif
#endif

    SPI_Modes_Select_t spi_master_slave_select;

    uint8 spi_transmit_enable            : 1;
    uint8 spi_receive_enable             : 1;
    uint8 spi_clock_polarity_select      : 1;
    uint8 spi_clock_transmit_edge_select : 1;
    uint8 spi_master_sample_at_select    : 1;

} mssp_spi_t;
```

## Functions

All functions are declared in `SPI_APIs.h`:

### Initialization Example

**Master Mode Example** 

```c
void MSSP_SPI_Interrupt_Handler_App(void){
    /* Application logic */
}

mssp_spi_t spi_obj = {
    .spi_master_slave_select      = SPI_Master_CLK_FOSC_DIV4,
    .spi_clock_polarity_select    = SPI_CLK_POL_IDLE_LOW_CFG,
    .spi_clock_transmit_edge_select = SPI_CLKE_TRANSMISSION_IDLE_TO_ACTIVE_CFG,
    .spi_master_sample_at_select  = SPI_MASTER_SAMPLE_AT_MIDDLE_CFG,
    .spi_transmit_enable          = SPI_TRANSMIT_ENABLE_CFG,
    .spi_receive_enable           = SPI_RECEIVE_ENABLE_CFG,
    .MSSP_SPI_DefaultInterruptHandler = MSSP_SPI_Interrupt_Handler_App
};

MSSP_SPI_Init(&spi_obj);
```
**Transmit / Receive Example**

```c
uint8 tx_data = 0x50;
uint8 rx_data = 0;

MSSP_SPI_Transmit_Receive_Byte(tx_data, &rx_data);
```

### Runtime APIs

| Function		          			  | Description             				   |
|-------------------------------------|--------------------------------------------|
| `MSSP_SPI_Init()` 	  			  | Initialize SPI peripheral   			   | 
| `MSSP_SPI_DeInit()` 	   			  | Disable SPI and interrupt 				   |
| `MSSP_SPI_Transmit_Receive_Byte()`  | Send and receive one byte 				   |
| `MSSP_SPI_ISR()` 	  		          | SPI interrupt service routine			   |

## SPI Operation Modes

### Master Mode

Supported clock configurations:
- Fosc / 4
- Fosc / 16
- Fosc / 64
- Timer2 / 2

Master controls:
- SCK generation
- Data transmission timing
- Slave selection (external logic)

### Slave Mode

- Can operate with SS pin enabled or disabled
- SCK is externally driven
- SMP bit automatically cleared as required by datasheet

## Clock Configuration

**SPI** timing is controlled using:
- **CKP** → Clock polarity
- **CKE** → Data transmission edge
- **SMP** → Sample timing (Master only)

This allows implementation of SPI modes 0, 1, 2, and 3.

## Interrupt Handling

- ISR function: `MSSP_SPI_ISR()`
- Clears interrupt flag internally
- Calls user-defined callback if registered
- Supports:
  - High priority interrupts
  - Low priority interrupts
  - Optional priority feature

### Callback Mechanism

The driver uses a function pointer:

```c
void (* MSSP_SPI_DefaultInterruptHandler)(void);
```

This ensures:
- Application logic remains outside MCAL
- Clean architectural separation
- Reusable and portable driver design

## Important Technical Notes

### Full-Duplex Communication

Writing to `SSPBUF`:
- Starts transmission
- Simultaneously triggers reception

Reading `SSPBUF`:
- Retrieves received data
- Clears BF flag

### Status Flags

The driver handles:
- Write Collision (WCOL)
- Receive Overflow (SSPOV)
- Buffer Full (BF)

Flags are cleared before transmission to ensure safe operation.

### Pin Direction Handling

- Master mode:
  - SCK → Output
  - SDO → Output
  - SDI → Input
- Slave mode:
  - SCK → Input
  - SDO → Output (if enabled)
  - SDI → Input
  - SS → Input (if enabled) 
  
Handled internally using GPIO abstraction layer.

### SPI is Blocking (Polling-Based)

Current implementation performs single-byte exchange.
The application layer is responsible for managing polling behavior and
transfer synchronization when interrupt mode is not used.

Timeout handling is not included to keep driver lightweight.

## Design Philosophy

The SPI driver is designed to be:

- Lightweight
- Deterministic
- Hardware-focused
- Easily extendable
- Fully compliant with PIC18F4620 datasheet

Higher-level protocol handling (e.g., Display drivers)
should be implemented at the ECUAL layer.


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

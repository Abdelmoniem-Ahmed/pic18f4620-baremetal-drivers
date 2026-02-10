# ADC Driver – PIC18F4620 (MCAL)

## Overview

The **ADC (Analog-to-Digital Converter) driver** provides a clean **hardware abstraction** for the internal ADC module of the **PIC18F4620** microcontroller.

This driver belongs to the **MCAL (Microcontroller Abstraction Layer)** and is designed following a **layered embedded architecture**:

- Direct register-level control
- Clear separation between configuration, control, and application logic
- Portable, reusable, and maintainable design

---

## Features

- Supports all PIC18F4620 ADC channels (**AN0 → AN12**)
- Configurable:
  - Acquisition time (TAD)
  - Conversion clock source
  - Result justification (Left / Right)
  - Voltage reference (Internal / External)
- Blocking (polling) conversion mode
- Interrupt-based conversion mode (callback-driven)
- Compile-time interrupt enable / disable
- No dynamic memory allocation
- No RTOS dependency

---

## ADC Operating Modes

### 1. Blocking (Polling) Mode

- CPU waits until conversion completes
- Simple and deterministic
- Suitable for low-frequency sampling

**API:**

```c
ADC_GetConversion_Blocking();
```

### 2. Interrupt Mode

- Conversion completion triggers the ADC interrupt
- A user-defined callback function is executed inside the ISR
- Suitable for non-blocking and event-driven designs

### API

```c
ADC_StartConversion_Interrupt();
```

> **Note:**  
> Interrupt functionality depends on enabling ADC interrupts at compile time in  
> `mcal_interrupt_gen_cfg.h`

---

## File Structure

```text
mcal/adc/
│
├── hal_adc.h        # ADC driver interface & configuration types
├── hal_adc.c        # ADC driver implementation
└── README.md        # ADC driver documentation
```

## Configuration & Usage Guide

### Configuration Options

### Analog / Digital Port Configuration

Use one of these macros to configure analog functionality on the port pins:

```c
ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN0_ANALOG_FUNCTIONALITY);
```

### Available configurations:

- `ADC_ALL_DIGITAL_FUNCTIONALITY`  
- `ADC_AN0_ANALOG_FUNCTIONALITY`  
- `ADC_AN4_ANALOG_FUNCTIONALITY`  
- `ADC_AN12_ANALOG_FUNCTIONALITY`

> **Note**  
> Selecting `ADC_AN4_ANALOG_FUNCTIONALITY` configures **AN0 → AN4** as analog inputs (AN5 and above remain digital).

### Result Format / Justification

- `ADC_RESULT_RIGHT`  
- `ADC_RESULT_LEFT`

### Voltage Reference

- `ADC_VOLTAGE_REFERENCE_ENABLE`  
- `ADC_VOLTAGE_REFERENCE_DISABLE`

## Data Types

### ADC Channel Selection

```c
typedef enum {
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12
} adc_channel_select_t;
```

### ADC Configuration Structure

```c
typedef struct {
#if INTERRUPT_FEATURE_ENABLE == ADC_INTERRUPT_FEATURE_ENABLE
    void (*ADC_InterruptHandler)(void);                    // User callback function
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_Priority_cfg priority;                       // High or Low priority
#endif
#endif
    adc_acquisition_time_t  acquisition_time;              // Acquisition time select
    adc_conversion_clock_t  conversion_clock;              // Conversion clock source
    adc_channel_select_t    adc_channel;                   // Selected ADC channel
    uint8 result_format     : 1;                           // 1 = Right, 0 = Left justified
    uint8 voltage_reference : 1;                           // 0 = Disabled, 1 = Enabled
    uint8 adc_reserved      : 6;                           // Reserved for future use / alignment
} adc_conf_t;
```

## API Functions

### Initialization & Deinitialization

```c
Std_ReturnType ADC_Init(const adc_conf_t *adc);
Std_ReturnType ADC_DeInit(const adc_conf_t *adc);
```

### Channel & Conversion Control

```c
Std_ReturnType ADC_Select_Channel(adc_channel_select_t channel);
Std_ReturnType ADC_Start_Conversion(const adc_conf_t *adc);
```

### Polling (Blocking) Mode APIs

```c
Std_ReturnType ADC_IsConversionDone(
    const adc_conf_t *adc,
    uint8 *status
);

Std_ReturnType ADC_GetConversionResult(
    const adc_conf_t *adc,
    adc_result_t *result
);

Std_ReturnType ADC_GetConversion_Blocking(
    const adc_conf_t *adc,
    adc_channel_select_t channel,
    adc_result_t *result
);
```
### Interrupt Mode API

```c 
Std_ReturnType ADC_StartConversion_Interrupt(
    const adc_conf_t *adc,
    adc_channel_select_t channel
);
```
## Usage Examples

### Blocking Mode (Polling)

```c
adc_conf_t adc1 = {
    .acquisition_time  = ADC_0_TAD,
    .conversion_clock  = ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    .adc_channel       = ADC_CHANNEL_AN0,
    .result_format     = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_VOLTAGE_REFERENCE_DISABLE
};

adc_result_t adc_value = 0;

ADC_Init(&adc1);
ADC_GetConversion_Blocking(&adc1, ADC_CHANNEL_AN0, &adc_value);
```
### Interrupt Mode

```c
void ADC_Callback(void)
{
    /* Read ADC result, process data, clear flag, etc. */
}

adc_conf_t adc1 = {
    .acquisition_time     = ADC_0_TAD,
    .conversion_clock     = ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    .adc_channel          = ADC_CHANNEL_AN0,
    .result_format        = ADC_RESULT_RIGHT,
    .voltage_reference    = ADC_VOLTAGE_REFERENCE_DISABLE,
    .ADC_InterruptHandler = ADC_Callback
    /* .priority = HIGH_PRIORITY;   // if priority levels are enabled */
};

ADC_Init(&adc1);
ADC_StartConversion_Interrupt(&adc1, ADC_CHANNEL_AN0);
```

## Design Notes

- **Analog channel pins** are automatically configured as inputs during `ADC_Init()`
- **Conversion complete flags** are cleared automatically in software (no manual clearing needed)
- The ISR **only dispatches** to the user-provided callback — keep interrupt handlers **short and fast**
- **Never** call any blocking ADC functions (e.g. `ADC_GetConversion_Blocking`) from inside an ISR
- The driver architecture is intentionally modular and designed to be easily extended by **ECUAL-level** or application-specific layers

## Dependencies

- `xc.h`
- `std_types.h`
- GPIO MCAL driver
- Interrupt MCAL driver (only required when using interrupt-driven mode)

## Author

**Abdelmoniem Ahmed**  
Embedded Software Engineer  

- LinkedIn: https://www.linkedin.com/in/abdelmoniem-ahmed/

**Year:** 2026
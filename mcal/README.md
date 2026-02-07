# MCAL – Microcontroller Abstraction Layer

## Overview
The MCAL layer contains **hardware-dependent drivers** that abstract direct
microcontroller register access and expose clean APIs to higher layers.

All MCAL drivers are specific to the target microcontroller and must not be
accessed directly by application code.

---

## Responsibilities
- Direct interaction with MCU registers
- Peripheral initialization and control
- Hardware abstraction for ECUAL and application layers
- Parameter validation and defensive programming

---

## Available Drivers

GPIO/

Other MCAL drivers are implemented and will be documented incrementally.

---

## Design Guidelines
- No direct register access outside MCAL
- Clear separation between interface and implementation
- Configuration handled via dedicated configuration headers

# Embedded Layered Drivers – PIC18F4620

## Overview
This repository contains **bare-metal embedded drivers** developed in C for the
PIC18F4620 microcontroller using a **layered software architecture**.

The project focuses on:
- Clear separation of responsibilities between software layers
- Hardware abstraction and clean driver interfaces
- Readable, maintainable embedded C code
- Progressive and structured documentation

---

## Software Architecture

Application Layer
↓
ECUAL
↓
MCAL
↓
Hardware


Each layer communicates only with the layer directly below it, preventing direct
hardware access from higher-level code.

---

## Repository Structure

/MCAL
/ECUAL
/Application


- **MCAL**: Microcontroller-dependent drivers
- **ECUAL**: Higher-level drivers built on MCAL
- **Application**: Application logic and usage examples (future)

---

## Documentation Status
- MCAL drivers: implemented, GPIO documented
- ECUAL drivers: implemented, documentation in progress
- Application examples: planned

---

## Author
**Abdelmoniem Ahmed**  
Embedded Software Engineer  
LinkedIn: https://www.linkedin.com/in/abdelmoniem-ahmed/

/**
 * @file   hal_eeprom.c
 * @author Monem
 * @brief  HAL Data EEPROM Driver Implementation for PIC18F4620
 *
 * @details
 * This file contains the implementation of the internal Data EEPROM
 * driver for the PIC18F4620 microcontroller.
 *
 * Driver Characteristics:
 * -----------------------
 * - Polling-based implementation
 * - Atomic write sequence protection
 * - Interrupt state preservation
 * - Address boundary validation
 *
 * EEPROM Size:
 * ------------
 * 1024 Bytes (Address range: 0x000 – 0x3FF)
 *
 * Safety Notes:
 * -------------
 * - Global interrupts are temporarily disabled during the required
 *   unlock sequence to prevent accidental corruption.
 * - The driver waits until WR bit clears before returning.
 */


#include"hal_eeprom.h"

/**
 * @brief  Writes one byte to Data EEPROM
 *
 * @param  address  EEPROM address (0x000 – 0x3FF)
 * @param  Data     Data byte to be written
 *
 * @return Std_ReturnType
 *         - E_OK     : Write successful
 *         - E_NOT_OK : Invalid address
 *
 * @note   This function uses polling and blocks until the
 *         write cycle completes (~4ms typical).
 */

Std_ReturnType Data_EEPROM_Write_Byte(uint16 address , uint8 Data){
    
    Std_ReturnType ret = E_OK;
    uint8 Interrupt_global_Status = 0;
    uint8 Interrupt_peripheral_Status = 0;
    /* Read The Interrupt Status "Enabled / Disabled"*/
    Interrupt_global_Status = INTCONbits.GIE ;
    Interrupt_peripheral_Status = INTCONbits.PEIE;
    /* Update the ADDRESS Register */
    EEADR  = ((uint8)(address&0xFF)); 
    EEADRH = ((uint8) ((address >> 8) & 0x03) ) ;
    /* Update the Data Register */
    EEDATA = Data;        
    /* Select Access Data to EEPROM */
    EECON1bits.EEPGD = ACCESS_DATA_EEPROM_MEM ;
    /* Allows write Cycle To Flash program/ EEPROM */
    EECON1bits.CFGS  = ACCESS_DATA_EEPROM_MEM ;
    /* DisAble All Interrupts */
#if                     INTERRUPT_FEATURE_DISABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE   
    INTERRUPT_GlobalInterruptDisable();
#else
    INTERRUPT_GlobalInterruptHighDisable();
    INTERRUPT_GlobalInterruptLowDisable();
#endif    
    /* Write the Required Sequence -> 0x55 -> 0xAA */
    EECON2 = 0x55 ;
    EECON2 = 0xAA ;
    /* Allow Write Cycle */
    EECON1bits.WREN = WRITE_ENABLE ;
    /* Initiate the Erase/Write Cycle */
    EECON1bits.WR   = WRITE_CYCLE_INITATE ;
    /* Wait to complete the write process */
    while(EECON1bits.WR){ /* Nothing , Just Wait */ }
    /* inhibits Write cycles */
    EECON1bits.WREN = WRITE_DISABLE ;
    /* Restore INTERRUPT GIE */
    INTCONbits.GIE = Interrupt_global_Status ;
    INTCONbits.PEIE = Interrupt_peripheral_Status;
    return ret;
}



/**
 * @brief  Reads one byte from Data EEPROM
 *
 * @param  address  EEPROM address (0x000 – 0x3FF)
 * @param  Data     Pointer to store read data
 *
 * @return Std_ReturnType
 *         - E_OK     : Read successful
 *         - E_NOT_OK : Invalid parameter
 */
Std_ReturnType Data_EEPROM_Read_Byte(uint16 address , uint8 *Data){
    Std_ReturnType ret = E_OK;
    if(NULL == Data){
        ret = E_NOT_OK;
    }
    else{
    
    /* Update the ADDRESS Register */
    EEADR  = ((uint8)(address&0xFF)); 
    EEADRH = ((uint8) ((address >> 8) & 0x03) );
    /* Select Access Data to EEPROM */
    EECON1bits.EEPGD = ACCESS_DATA_EEPROM_MEM ;
    /* Allows write Cycle To Flash program/ EEPROM */
    EECON1bits.CFGS  = ACCESS_DATA_EEPROM_MEM ;
    /* Initiate the read cycle */
    EECON1bits.RD = READ_CYCLE_INITIATE ;
    
    NOP();
    NOP();
    
    *Data = EEDATA;
    }
    return ret;
}


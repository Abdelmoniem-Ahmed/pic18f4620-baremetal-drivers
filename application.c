/**
 * @file application.c
 * @brief Application layer source file.
 *
 * This file contains the main entry point of the system
 * and the implementation of application initialization.
 *
 * The application layer is responsible for coordinating
 * system startup and calling lower-layer drivers.
 *
 * @author Abdelmoniem Ahmed
 * @linkedin <- https://www.linkedin.com/in/abdelmoniem-ahmed/ ->
 */

#include "application.h"


int main() { 
    Std_ReturnType ret = E_NOT_OK;
    
    application_initialize(); 
    
#if SMART_HOME_APP == WORKING_APPLICATION               /* @ APPLICATION_H file */ 
    
  #if     SMART_HOME_SLAVE_BUILD == SMART_HOME_NODE     /* @ MCAL_INTERRUPT_GEN_CFG_H file */ 
    slave_mcu_main_app();
  #endif

  #if     SMART_HOME_MASTER_BUILD == SMART_HOME_NODE    /* @ MCAL_INTERRUPT_GEN_CFG_H file */ 
    Smart_Home_App();
  #endif
    
#endif
    
#if     MATRIX_KEYPAD_APP == WORKING_APPLICATION        /* @ APPLICATION_H file */ 
    Matrix_Keypad_Led_App();
#endif    
    
#if     SEVEN_SEGMENT_APP == WORKING_APPLICATION        /* @ APPLICATION_H file */ 
    Seven_Segment_app();
#endif      
    
#if     CHR_LCD_APP == WORKING_APPLICATION              /* @ APPLICATION_H file */ 
    Chr_LCD_app();
#endif      
    
#if     LED_BLINK_APP == WORKING_APPLICATION            /* @ APPLICATION_H file */  
    Led_Blink_Hal_app();
#endif     
    
#if     LED_BLINK_APP == WORKING_APPLICATION            /* @ APPLICATION_H file */ 
    Led_Blink_app();
#endif   
    
    while(1){
        
    }
    return (EXIT_SUCCESS);
}

void application_initialize(void){
    Std_ReturnType ret = E_NOT_OK;

}
  


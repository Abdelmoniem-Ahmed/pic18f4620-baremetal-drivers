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
    application_intialize();

    while(1){
        
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    
}



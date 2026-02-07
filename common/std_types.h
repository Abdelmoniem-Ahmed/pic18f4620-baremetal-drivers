/**
 * @file std_types.h
 * @brief  -> standard Data Types 
 * @author Abdelmoniem Ahmed
 * @linkedin <- https://www.linkedin.com/in/abdelmoniem-ahmed/ ->
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section : Includes */

#include "std_libraries.h"
#include "compiler.h"

/* Section : Macro Functions Declarations */

/* Section : Data Types Declarations */

typedef unsigned char      uint8   ;
typedef unsigned int       uint16  ;
typedef unsigned long int  uint32  ;
typedef unsigned long long uint64  ;
typedef signed char        sint8   ;
typedef signed int         sint16  ;
typedef signed long int    sint32  ;
typedef signed long long   sint64  ;

typedef uint8 Std_ReturnType ; 

/* Section : Macro Declaration */

#define STD_HIGH        0X01
#define STD_LOW         0X00

#define STD_ON          0X01
#define STD_OFF         0X00

#define STD_ACTIVE      0X01
#define STD_IDLE        0X00

#define E_OK            (Std_ReturnType)0X01
#define E_NOT_OK        (Std_ReturnType)0X00

#define ZERO_INIT 0x00

/* Section : Function Declarations */



#endif	/* MCAL_STD_TYPES_H */


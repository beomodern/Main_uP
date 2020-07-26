/*******************************************************************************
* File Name: MOSI_1.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_MOSI_1_H) /* Pins MOSI_1_H */
#define CY_PINS_MOSI_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MOSI_1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    MOSI_1_Write(uint8 value) ;
void    MOSI_1_SetDriveMode(uint8 mode) ;
uint8   MOSI_1_ReadDataReg(void) ;
uint8   MOSI_1_Read(void) ;
uint8   MOSI_1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MOSI_1_DRIVE_MODE_BITS        (3)
#define MOSI_1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MOSI_1_DRIVE_MODE_BITS))

#define MOSI_1_DM_ALG_HIZ         (0x00u)
#define MOSI_1_DM_DIG_HIZ         (0x01u)
#define MOSI_1_DM_RES_UP          (0x02u)
#define MOSI_1_DM_RES_DWN         (0x03u)
#define MOSI_1_DM_OD_LO           (0x04u)
#define MOSI_1_DM_OD_HI           (0x05u)
#define MOSI_1_DM_STRONG          (0x06u)
#define MOSI_1_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define MOSI_1_MASK               MOSI_1__MASK
#define MOSI_1_SHIFT              MOSI_1__SHIFT
#define MOSI_1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MOSI_1_PS                     (* (reg32 *) MOSI_1__PS)
/* Port Configuration */
#define MOSI_1_PC                     (* (reg32 *) MOSI_1__PC)
/* Data Register */
#define MOSI_1_DR                     (* (reg32 *) MOSI_1__DR)
/* Input Buffer Disable Override */
#define MOSI_1_INP_DIS                (* (reg32 *) MOSI_1__PC2)


#if defined(MOSI_1__INTSTAT)  /* Interrupt Registers */

    #define MOSI_1_INTSTAT                (* (reg32 *) MOSI_1__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define MOSI_1_DRIVE_MODE_SHIFT       (0x00u)
#define MOSI_1_DRIVE_MODE_MASK        (0x07u << MOSI_1_DRIVE_MODE_SHIFT)


#endif /* End Pins MOSI_1_H */


/* [] END OF FILE */

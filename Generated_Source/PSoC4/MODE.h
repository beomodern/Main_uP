/*******************************************************************************
* File Name: MODE.h  
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

#if !defined(CY_PINS_MODE_H) /* Pins MODE_H */
#define CY_PINS_MODE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MODE_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    MODE_Write(uint8 value) ;
void    MODE_SetDriveMode(uint8 mode) ;
uint8   MODE_ReadDataReg(void) ;
uint8   MODE_Read(void) ;
uint8   MODE_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MODE_DRIVE_MODE_BITS        (3)
#define MODE_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MODE_DRIVE_MODE_BITS))

#define MODE_DM_ALG_HIZ         (0x00u)
#define MODE_DM_DIG_HIZ         (0x01u)
#define MODE_DM_RES_UP          (0x02u)
#define MODE_DM_RES_DWN         (0x03u)
#define MODE_DM_OD_LO           (0x04u)
#define MODE_DM_OD_HI           (0x05u)
#define MODE_DM_STRONG          (0x06u)
#define MODE_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define MODE_MASK               MODE__MASK
#define MODE_SHIFT              MODE__SHIFT
#define MODE_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MODE_PS                     (* (reg32 *) MODE__PS)
/* Port Configuration */
#define MODE_PC                     (* (reg32 *) MODE__PC)
/* Data Register */
#define MODE_DR                     (* (reg32 *) MODE__DR)
/* Input Buffer Disable Override */
#define MODE_INP_DIS                (* (reg32 *) MODE__PC2)


#if defined(MODE__INTSTAT)  /* Interrupt Registers */

    #define MODE_INTSTAT                (* (reg32 *) MODE__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define MODE_DRIVE_MODE_SHIFT       (0x00u)
#define MODE_DRIVE_MODE_MASK        (0x07u << MODE_DRIVE_MODE_SHIFT)


#endif /* End Pins MODE_H */


/* [] END OF FILE */

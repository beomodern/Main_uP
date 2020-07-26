/*******************************************************************************
* File Name: PWR_OK.h  
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

#if !defined(CY_PINS_PWR_OK_H) /* Pins PWR_OK_H */
#define CY_PINS_PWR_OK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PWR_OK_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PWR_OK_Write(uint8 value) ;
void    PWR_OK_SetDriveMode(uint8 mode) ;
uint8   PWR_OK_ReadDataReg(void) ;
uint8   PWR_OK_Read(void) ;
uint8   PWR_OK_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PWR_OK_DRIVE_MODE_BITS        (3)
#define PWR_OK_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PWR_OK_DRIVE_MODE_BITS))

#define PWR_OK_DM_ALG_HIZ         (0x00u)
#define PWR_OK_DM_DIG_HIZ         (0x01u)
#define PWR_OK_DM_RES_UP          (0x02u)
#define PWR_OK_DM_RES_DWN         (0x03u)
#define PWR_OK_DM_OD_LO           (0x04u)
#define PWR_OK_DM_OD_HI           (0x05u)
#define PWR_OK_DM_STRONG          (0x06u)
#define PWR_OK_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PWR_OK_MASK               PWR_OK__MASK
#define PWR_OK_SHIFT              PWR_OK__SHIFT
#define PWR_OK_WIDTH              2u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWR_OK_PS                     (* (reg32 *) PWR_OK__PS)
/* Port Configuration */
#define PWR_OK_PC                     (* (reg32 *) PWR_OK__PC)
/* Data Register */
#define PWR_OK_DR                     (* (reg32 *) PWR_OK__DR)
/* Input Buffer Disable Override */
#define PWR_OK_INP_DIS                (* (reg32 *) PWR_OK__PC2)


#if defined(PWR_OK__INTSTAT)  /* Interrupt Registers */

    #define PWR_OK_INTSTAT                (* (reg32 *) PWR_OK__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PWR_OK_DRIVE_MODE_SHIFT       (0x00u)
#define PWR_OK_DRIVE_MODE_MASK        (0x07u << PWR_OK_DRIVE_MODE_SHIFT)


#endif /* End Pins PWR_OK_H */


/* [] END OF FILE */

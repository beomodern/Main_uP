/*******************************************************************************
* File Name: BT_PAIRING.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_BT_PAIRING_ALIASES_H) /* Pins BT_PAIRING_ALIASES_H */
#define CY_PINS_BT_PAIRING_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BT_PAIRING_0			(BT_PAIRING__0__PC)
#define BT_PAIRING_0_PS		(BT_PAIRING__0__PS)
#define BT_PAIRING_0_PC		(BT_PAIRING__0__PC)
#define BT_PAIRING_0_DR		(BT_PAIRING__0__DR)
#define BT_PAIRING_0_SHIFT	(BT_PAIRING__0__SHIFT)
#define BT_PAIRING_0_INTR	((uint16)((uint16)0x0003u << (BT_PAIRING__0__SHIFT*2u)))

#define BT_PAIRING_INTR_ALL	 ((uint16)(BT_PAIRING_0_INTR))


#endif /* End Pins BT_PAIRING_ALIASES_H */


/* [] END OF FILE */

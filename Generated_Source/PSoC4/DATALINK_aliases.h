/*******************************************************************************
* File Name: DATALINK.h  
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

#if !defined(CY_PINS_DATALINK_ALIASES_H) /* Pins DATALINK_ALIASES_H */
#define CY_PINS_DATALINK_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DATALINK_0			(DATALINK__0__PC)
#define DATALINK_0_PS		(DATALINK__0__PS)
#define DATALINK_0_PC		(DATALINK__0__PC)
#define DATALINK_0_DR		(DATALINK__0__DR)
#define DATALINK_0_SHIFT	(DATALINK__0__SHIFT)
#define DATALINK_0_INTR	((uint16)((uint16)0x0003u << (DATALINK__0__SHIFT*2u)))

#define DATALINK_INTR_ALL	 ((uint16)(DATALINK_0_INTR))


#endif /* End Pins DATALINK_ALIASES_H */


/* [] END OF FILE */

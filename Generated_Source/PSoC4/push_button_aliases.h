/*******************************************************************************
* File Name: push_button.h  
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

#if !defined(CY_PINS_push_button_ALIASES_H) /* Pins push_button_ALIASES_H */
#define CY_PINS_push_button_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define push_button_0			(push_button__0__PC)
#define push_button_0_PS		(push_button__0__PS)
#define push_button_0_PC		(push_button__0__PC)
#define push_button_0_DR		(push_button__0__DR)
#define push_button_0_SHIFT	(push_button__0__SHIFT)
#define push_button_0_INTR	((uint16)((uint16)0x0003u << (push_button__0__SHIFT*2u)))

#define push_button_INTR_ALL	 ((uint16)(push_button_0_INTR))


#endif /* End Pins push_button_ALIASES_H */


/* [] END OF FILE */

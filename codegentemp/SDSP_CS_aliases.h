/*******************************************************************************
* File Name: SDSP_CS.h  
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

#if !defined(CY_PINS_SDSP_CS_ALIASES_H) /* Pins SDSP_CS_ALIASES_H */
#define CY_PINS_SDSP_CS_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SDSP_CS_0			(SDSP_CS__0__PC)
#define SDSP_CS_0_PS		(SDSP_CS__0__PS)
#define SDSP_CS_0_PC		(SDSP_CS__0__PC)
#define SDSP_CS_0_DR		(SDSP_CS__0__DR)
#define SDSP_CS_0_SHIFT	(SDSP_CS__0__SHIFT)
#define SDSP_CS_0_INTR	((uint16)((uint16)0x0003u << (SDSP_CS__0__SHIFT*2u)))

#define SDSP_CS_INTR_ALL	 ((uint16)(SDSP_CS_0_INTR))


#endif /* End Pins SDSP_CS_ALIASES_H */


/* [] END OF FILE */

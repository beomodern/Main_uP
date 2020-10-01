/*******************************************************************************
* File Name: DISP_CS.h  
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

#if !defined(CY_PINS_DISP_CS_ALIASES_H) /* Pins DISP_CS_ALIASES_H */
#define CY_PINS_DISP_CS_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DISP_CS_0			(DISP_CS__0__PC)
#define DISP_CS_0_PS		(DISP_CS__0__PS)
#define DISP_CS_0_PC		(DISP_CS__0__PC)
#define DISP_CS_0_DR		(DISP_CS__0__DR)
#define DISP_CS_0_SHIFT	(DISP_CS__0__SHIFT)
#define DISP_CS_0_INTR	((uint16)((uint16)0x0003u << (DISP_CS__0__SHIFT*2u)))

#define DISP_CS_INTR_ALL	 ((uint16)(DISP_CS_0_INTR))


#endif /* End Pins DISP_CS_ALIASES_H */


/* [] END OF FILE */

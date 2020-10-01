/*******************************************************************************
* File Name: PWR_DISP.h  
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

#if !defined(CY_PINS_PWR_DISP_ALIASES_H) /* Pins PWR_DISP_ALIASES_H */
#define CY_PINS_PWR_DISP_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PWR_DISP_0			(PWR_DISP__0__PC)
#define PWR_DISP_0_PS		(PWR_DISP__0__PS)
#define PWR_DISP_0_PC		(PWR_DISP__0__PC)
#define PWR_DISP_0_DR		(PWR_DISP__0__DR)
#define PWR_DISP_0_SHIFT	(PWR_DISP__0__SHIFT)
#define PWR_DISP_0_INTR	((uint16)((uint16)0x0003u << (PWR_DISP__0__SHIFT*2u)))

#define PWR_DISP_INTR_ALL	 ((uint16)(PWR_DISP_0_INTR))


#endif /* End Pins PWR_DISP_ALIASES_H */


/* [] END OF FILE */

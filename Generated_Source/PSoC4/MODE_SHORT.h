/*******************************************************************************
* File Name: MODE_SHORT.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_MODE_SHORT_H)
#define CY_ISR_MODE_SHORT_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void MODE_SHORT_Start(void);
void MODE_SHORT_StartEx(cyisraddress address);
void MODE_SHORT_Stop(void);

CY_ISR_PROTO(MODE_SHORT_Interrupt);

void MODE_SHORT_SetVector(cyisraddress address);
cyisraddress MODE_SHORT_GetVector(void);

void MODE_SHORT_SetPriority(uint8 priority);
uint8 MODE_SHORT_GetPriority(void);

void MODE_SHORT_Enable(void);
uint8 MODE_SHORT_GetState(void);
void MODE_SHORT_Disable(void);

void MODE_SHORT_SetPending(void);
void MODE_SHORT_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the MODE_SHORT ISR. */
#define MODE_SHORT_INTC_VECTOR            ((reg32 *) MODE_SHORT__INTC_VECT)

/* Address of the MODE_SHORT ISR priority. */
#define MODE_SHORT_INTC_PRIOR             ((reg32 *) MODE_SHORT__INTC_PRIOR_REG)

/* Priority of the MODE_SHORT interrupt. */
#define MODE_SHORT_INTC_PRIOR_NUMBER      MODE_SHORT__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable MODE_SHORT interrupt. */
#define MODE_SHORT_INTC_SET_EN            ((reg32 *) MODE_SHORT__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the MODE_SHORT interrupt. */
#define MODE_SHORT_INTC_CLR_EN            ((reg32 *) MODE_SHORT__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the MODE_SHORT interrupt state to pending. */
#define MODE_SHORT_INTC_SET_PD            ((reg32 *) MODE_SHORT__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the MODE_SHORT interrupt. */
#define MODE_SHORT_INTC_CLR_PD            ((reg32 *) MODE_SHORT__INTC_CLR_PD_REG)



#endif /* CY_ISR_MODE_SHORT_H */


/* [] END OF FILE */

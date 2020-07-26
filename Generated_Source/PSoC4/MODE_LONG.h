/*******************************************************************************
* File Name: MODE_LONG.h
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
#if !defined(CY_ISR_MODE_LONG_H)
#define CY_ISR_MODE_LONG_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void MODE_LONG_Start(void);
void MODE_LONG_StartEx(cyisraddress address);
void MODE_LONG_Stop(void);

CY_ISR_PROTO(MODE_LONG_Interrupt);

void MODE_LONG_SetVector(cyisraddress address);
cyisraddress MODE_LONG_GetVector(void);

void MODE_LONG_SetPriority(uint8 priority);
uint8 MODE_LONG_GetPriority(void);

void MODE_LONG_Enable(void);
uint8 MODE_LONG_GetState(void);
void MODE_LONG_Disable(void);

void MODE_LONG_SetPending(void);
void MODE_LONG_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the MODE_LONG ISR. */
#define MODE_LONG_INTC_VECTOR            ((reg32 *) MODE_LONG__INTC_VECT)

/* Address of the MODE_LONG ISR priority. */
#define MODE_LONG_INTC_PRIOR             ((reg32 *) MODE_LONG__INTC_PRIOR_REG)

/* Priority of the MODE_LONG interrupt. */
#define MODE_LONG_INTC_PRIOR_NUMBER      MODE_LONG__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable MODE_LONG interrupt. */
#define MODE_LONG_INTC_SET_EN            ((reg32 *) MODE_LONG__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the MODE_LONG interrupt. */
#define MODE_LONG_INTC_CLR_EN            ((reg32 *) MODE_LONG__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the MODE_LONG interrupt state to pending. */
#define MODE_LONG_INTC_SET_PD            ((reg32 *) MODE_LONG__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the MODE_LONG interrupt. */
#define MODE_LONG_INTC_CLR_PD            ((reg32 *) MODE_LONG__INTC_CLR_PD_REG)



#endif /* CY_ISR_MODE_LONG_H */


/* [] END OF FILE */

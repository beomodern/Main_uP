/*******************************************************************************
* File Name: SwInt.h
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
#if !defined(CY_ISR_SwInt_H)
#define CY_ISR_SwInt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void SwInt_Start(void);
void SwInt_StartEx(cyisraddress address);
void SwInt_Stop(void);

CY_ISR_PROTO(SwInt_Interrupt);

void SwInt_SetVector(cyisraddress address);
cyisraddress SwInt_GetVector(void);

void SwInt_SetPriority(uint8 priority);
uint8 SwInt_GetPriority(void);

void SwInt_Enable(void);
uint8 SwInt_GetState(void);
void SwInt_Disable(void);

void SwInt_SetPending(void);
void SwInt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the SwInt ISR. */
#define SwInt_INTC_VECTOR            ((reg32 *) SwInt__INTC_VECT)

/* Address of the SwInt ISR priority. */
#define SwInt_INTC_PRIOR             ((reg32 *) SwInt__INTC_PRIOR_REG)

/* Priority of the SwInt interrupt. */
#define SwInt_INTC_PRIOR_NUMBER      SwInt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable SwInt interrupt. */
#define SwInt_INTC_SET_EN            ((reg32 *) SwInt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the SwInt interrupt. */
#define SwInt_INTC_CLR_EN            ((reg32 *) SwInt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the SwInt interrupt state to pending. */
#define SwInt_INTC_SET_PD            ((reg32 *) SwInt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the SwInt interrupt. */
#define SwInt_INTC_CLR_PD            ((reg32 *) SwInt__INTC_CLR_PD_REG)



#endif /* CY_ISR_SwInt_H */


/* [] END OF FILE */

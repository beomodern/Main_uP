/*******************************************************************************
* File Name: PWR_OK_LONG.h
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
#if !defined(CY_ISR_PWR_OK_LONG_H)
#define CY_ISR_PWR_OK_LONG_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void PWR_OK_LONG_Start(void);
void PWR_OK_LONG_StartEx(cyisraddress address);
void PWR_OK_LONG_Stop(void);

CY_ISR_PROTO(PWR_OK_LONG_Interrupt);

void PWR_OK_LONG_SetVector(cyisraddress address);
cyisraddress PWR_OK_LONG_GetVector(void);

void PWR_OK_LONG_SetPriority(uint8 priority);
uint8 PWR_OK_LONG_GetPriority(void);

void PWR_OK_LONG_Enable(void);
uint8 PWR_OK_LONG_GetState(void);
void PWR_OK_LONG_Disable(void);

void PWR_OK_LONG_SetPending(void);
void PWR_OK_LONG_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the PWR_OK_LONG ISR. */
#define PWR_OK_LONG_INTC_VECTOR            ((reg32 *) PWR_OK_LONG__INTC_VECT)

/* Address of the PWR_OK_LONG ISR priority. */
#define PWR_OK_LONG_INTC_PRIOR             ((reg32 *) PWR_OK_LONG__INTC_PRIOR_REG)

/* Priority of the PWR_OK_LONG interrupt. */
#define PWR_OK_LONG_INTC_PRIOR_NUMBER      PWR_OK_LONG__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable PWR_OK_LONG interrupt. */
#define PWR_OK_LONG_INTC_SET_EN            ((reg32 *) PWR_OK_LONG__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the PWR_OK_LONG interrupt. */
#define PWR_OK_LONG_INTC_CLR_EN            ((reg32 *) PWR_OK_LONG__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the PWR_OK_LONG interrupt state to pending. */
#define PWR_OK_LONG_INTC_SET_PD            ((reg32 *) PWR_OK_LONG__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the PWR_OK_LONG interrupt. */
#define PWR_OK_LONG_INTC_CLR_PD            ((reg32 *) PWR_OK_LONG__INTC_CLR_PD_REG)



#endif /* CY_ISR_PWR_OK_LONG_H */


/* [] END OF FILE */

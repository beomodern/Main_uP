/*******************************************************************************
* File Name: FiltSwInt.h
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
#if !defined(CY_ISR_FiltSwInt_H)
#define CY_ISR_FiltSwInt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void FiltSwInt_Start(void);
void FiltSwInt_StartEx(cyisraddress address);
void FiltSwInt_Stop(void);

CY_ISR_PROTO(FiltSwInt_Interrupt);

void FiltSwInt_SetVector(cyisraddress address);
cyisraddress FiltSwInt_GetVector(void);

void FiltSwInt_SetPriority(uint8 priority);
uint8 FiltSwInt_GetPriority(void);

void FiltSwInt_Enable(void);
uint8 FiltSwInt_GetState(void);
void FiltSwInt_Disable(void);

void FiltSwInt_SetPending(void);
void FiltSwInt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the FiltSwInt ISR. */
#define FiltSwInt_INTC_VECTOR            ((reg32 *) FiltSwInt__INTC_VECT)

/* Address of the FiltSwInt ISR priority. */
#define FiltSwInt_INTC_PRIOR             ((reg32 *) FiltSwInt__INTC_PRIOR_REG)

/* Priority of the FiltSwInt interrupt. */
#define FiltSwInt_INTC_PRIOR_NUMBER      FiltSwInt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable FiltSwInt interrupt. */
#define FiltSwInt_INTC_SET_EN            ((reg32 *) FiltSwInt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the FiltSwInt interrupt. */
#define FiltSwInt_INTC_CLR_EN            ((reg32 *) FiltSwInt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the FiltSwInt interrupt state to pending. */
#define FiltSwInt_INTC_SET_PD            ((reg32 *) FiltSwInt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the FiltSwInt interrupt. */
#define FiltSwInt_INTC_CLR_PD            ((reg32 *) FiltSwInt__INTC_CLR_PD_REG)



#endif /* CY_ISR_FiltSwInt_H */


/* [] END OF FILE */

/*******************************************************************************
* File Name: DATALINK_INTRRUPT.h
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
#if !defined(CY_ISR_DATALINK_INTRRUPT_H)
#define CY_ISR_DATALINK_INTRRUPT_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void DATALINK_INTRRUPT_Start(void);
void DATALINK_INTRRUPT_StartEx(cyisraddress address);
void DATALINK_INTRRUPT_Stop(void);

CY_ISR_PROTO(DATALINK_INTRRUPT_Interrupt);

void DATALINK_INTRRUPT_SetVector(cyisraddress address);
cyisraddress DATALINK_INTRRUPT_GetVector(void);

void DATALINK_INTRRUPT_SetPriority(uint8 priority);
uint8 DATALINK_INTRRUPT_GetPriority(void);

void DATALINK_INTRRUPT_Enable(void);
uint8 DATALINK_INTRRUPT_GetState(void);
void DATALINK_INTRRUPT_Disable(void);

void DATALINK_INTRRUPT_SetPending(void);
void DATALINK_INTRRUPT_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the DATALINK_INTRRUPT ISR. */
#define DATALINK_INTRRUPT_INTC_VECTOR            ((reg32 *) DATALINK_INTRRUPT__INTC_VECT)

/* Address of the DATALINK_INTRRUPT ISR priority. */
#define DATALINK_INTRRUPT_INTC_PRIOR             ((reg32 *) DATALINK_INTRRUPT__INTC_PRIOR_REG)

/* Priority of the DATALINK_INTRRUPT interrupt. */
#define DATALINK_INTRRUPT_INTC_PRIOR_NUMBER      DATALINK_INTRRUPT__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable DATALINK_INTRRUPT interrupt. */
#define DATALINK_INTRRUPT_INTC_SET_EN            ((reg32 *) DATALINK_INTRRUPT__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the DATALINK_INTRRUPT interrupt. */
#define DATALINK_INTRRUPT_INTC_CLR_EN            ((reg32 *) DATALINK_INTRRUPT__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the DATALINK_INTRRUPT interrupt state to pending. */
#define DATALINK_INTRRUPT_INTC_SET_PD            ((reg32 *) DATALINK_INTRRUPT__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the DATALINK_INTRRUPT interrupt. */
#define DATALINK_INTRRUPT_INTC_CLR_PD            ((reg32 *) DATALINK_INTRRUPT__INTC_CLR_PD_REG)



#endif /* CY_ISR_DATALINK_INTRRUPT_H */


/* [] END OF FILE */

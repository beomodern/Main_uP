/*******************************************************************************
* File Name: SwClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_SwClock_H)
#define CY_CLOCK_SwClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void SwClock_StartEx(uint32 alignClkDiv);
#define SwClock_Start() \
    SwClock_StartEx(SwClock__PA_DIV_ID)

#else

void SwClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void SwClock_Stop(void);

void SwClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 SwClock_GetDividerRegister(void);
uint8  SwClock_GetFractionalDividerRegister(void);

#define SwClock_Enable()                         SwClock_Start()
#define SwClock_Disable()                        SwClock_Stop()
#define SwClock_SetDividerRegister(clkDivider, reset)  \
    SwClock_SetFractionalDividerRegister((clkDivider), 0u)
#define SwClock_SetDivider(clkDivider)           SwClock_SetDividerRegister((clkDivider), 1u)
#define SwClock_SetDividerValue(clkDivider)      SwClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define SwClock_DIV_ID     SwClock__DIV_ID

#define SwClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define SwClock_CTRL_REG   (*(reg32 *)SwClock__CTRL_REGISTER)
#define SwClock_DIV_REG    (*(reg32 *)SwClock__DIV_REGISTER)

#define SwClock_CMD_DIV_SHIFT          (0u)
#define SwClock_CMD_PA_DIV_SHIFT       (8u)
#define SwClock_CMD_DISABLE_SHIFT      (30u)
#define SwClock_CMD_ENABLE_SHIFT       (31u)

#define SwClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << SwClock_CMD_DISABLE_SHIFT))
#define SwClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << SwClock_CMD_ENABLE_SHIFT))

#define SwClock_DIV_FRAC_MASK  (0x000000F8u)
#define SwClock_DIV_FRAC_SHIFT (3u)
#define SwClock_DIV_INT_MASK   (0xFFFFFF00u)
#define SwClock_DIV_INT_SHIFT  (8u)

#else 

#define SwClock_DIV_REG        (*(reg32 *)SwClock__REGISTER)
#define SwClock_ENABLE_REG     SwClock_DIV_REG
#define SwClock_DIV_FRAC_MASK  SwClock__FRAC_MASK
#define SwClock_DIV_FRAC_SHIFT (16u)
#define SwClock_DIV_INT_MASK   SwClock__DIVIDER_MASK
#define SwClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_SwClock_H) */

/* [] END OF FILE */

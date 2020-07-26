/*******************************************************************************
* File Name: SwClock_1.h
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

#if !defined(CY_CLOCK_SwClock_1_H)
#define CY_CLOCK_SwClock_1_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void SwClock_1_StartEx(uint32 alignClkDiv);
#define SwClock_1_Start() \
    SwClock_1_StartEx(SwClock_1__PA_DIV_ID)

#else

void SwClock_1_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void SwClock_1_Stop(void);

void SwClock_1_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 SwClock_1_GetDividerRegister(void);
uint8  SwClock_1_GetFractionalDividerRegister(void);

#define SwClock_1_Enable()                         SwClock_1_Start()
#define SwClock_1_Disable()                        SwClock_1_Stop()
#define SwClock_1_SetDividerRegister(clkDivider, reset)  \
    SwClock_1_SetFractionalDividerRegister((clkDivider), 0u)
#define SwClock_1_SetDivider(clkDivider)           SwClock_1_SetDividerRegister((clkDivider), 1u)
#define SwClock_1_SetDividerValue(clkDivider)      SwClock_1_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define SwClock_1_DIV_ID     SwClock_1__DIV_ID

#define SwClock_1_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define SwClock_1_CTRL_REG   (*(reg32 *)SwClock_1__CTRL_REGISTER)
#define SwClock_1_DIV_REG    (*(reg32 *)SwClock_1__DIV_REGISTER)

#define SwClock_1_CMD_DIV_SHIFT          (0u)
#define SwClock_1_CMD_PA_DIV_SHIFT       (8u)
#define SwClock_1_CMD_DISABLE_SHIFT      (30u)
#define SwClock_1_CMD_ENABLE_SHIFT       (31u)

#define SwClock_1_CMD_DISABLE_MASK       ((uint32)((uint32)1u << SwClock_1_CMD_DISABLE_SHIFT))
#define SwClock_1_CMD_ENABLE_MASK        ((uint32)((uint32)1u << SwClock_1_CMD_ENABLE_SHIFT))

#define SwClock_1_DIV_FRAC_MASK  (0x000000F8u)
#define SwClock_1_DIV_FRAC_SHIFT (3u)
#define SwClock_1_DIV_INT_MASK   (0xFFFFFF00u)
#define SwClock_1_DIV_INT_SHIFT  (8u)

#else 

#define SwClock_1_DIV_REG        (*(reg32 *)SwClock_1__REGISTER)
#define SwClock_1_ENABLE_REG     SwClock_1_DIV_REG
#define SwClock_1_DIV_FRAC_MASK  SwClock_1__FRAC_MASK
#define SwClock_1_DIV_FRAC_SHIFT (16u)
#define SwClock_1_DIV_INT_MASK   SwClock_1__DIVIDER_MASK
#define SwClock_1_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_SwClock_1_H) */

/* [] END OF FILE */

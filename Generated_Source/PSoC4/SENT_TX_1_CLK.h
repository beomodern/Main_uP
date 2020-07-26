/*******************************************************************************
* File Name: SENT_TX_1_CLK.h
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

#if !defined(CY_CLOCK_SENT_TX_1_CLK_H)
#define CY_CLOCK_SENT_TX_1_CLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void SENT_TX_1_CLK_StartEx(uint32 alignClkDiv);
#define SENT_TX_1_CLK_Start() \
    SENT_TX_1_CLK_StartEx(SENT_TX_1_CLK__PA_DIV_ID)

#else

void SENT_TX_1_CLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void SENT_TX_1_CLK_Stop(void);

void SENT_TX_1_CLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 SENT_TX_1_CLK_GetDividerRegister(void);
uint8  SENT_TX_1_CLK_GetFractionalDividerRegister(void);

#define SENT_TX_1_CLK_Enable()                         SENT_TX_1_CLK_Start()
#define SENT_TX_1_CLK_Disable()                        SENT_TX_1_CLK_Stop()
#define SENT_TX_1_CLK_SetDividerRegister(clkDivider, reset)  \
    SENT_TX_1_CLK_SetFractionalDividerRegister((clkDivider), 0u)
#define SENT_TX_1_CLK_SetDivider(clkDivider)           SENT_TX_1_CLK_SetDividerRegister((clkDivider), 1u)
#define SENT_TX_1_CLK_SetDividerValue(clkDivider)      SENT_TX_1_CLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define SENT_TX_1_CLK_DIV_ID     SENT_TX_1_CLK__DIV_ID

#define SENT_TX_1_CLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define SENT_TX_1_CLK_CTRL_REG   (*(reg32 *)SENT_TX_1_CLK__CTRL_REGISTER)
#define SENT_TX_1_CLK_DIV_REG    (*(reg32 *)SENT_TX_1_CLK__DIV_REGISTER)

#define SENT_TX_1_CLK_CMD_DIV_SHIFT          (0u)
#define SENT_TX_1_CLK_CMD_PA_DIV_SHIFT       (8u)
#define SENT_TX_1_CLK_CMD_DISABLE_SHIFT      (30u)
#define SENT_TX_1_CLK_CMD_ENABLE_SHIFT       (31u)

#define SENT_TX_1_CLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << SENT_TX_1_CLK_CMD_DISABLE_SHIFT))
#define SENT_TX_1_CLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << SENT_TX_1_CLK_CMD_ENABLE_SHIFT))

#define SENT_TX_1_CLK_DIV_FRAC_MASK  (0x000000F8u)
#define SENT_TX_1_CLK_DIV_FRAC_SHIFT (3u)
#define SENT_TX_1_CLK_DIV_INT_MASK   (0xFFFFFF00u)
#define SENT_TX_1_CLK_DIV_INT_SHIFT  (8u)

#else 

#define SENT_TX_1_CLK_DIV_REG        (*(reg32 *)SENT_TX_1_CLK__REGISTER)
#define SENT_TX_1_CLK_ENABLE_REG     SENT_TX_1_CLK_DIV_REG
#define SENT_TX_1_CLK_DIV_FRAC_MASK  SENT_TX_1_CLK__FRAC_MASK
#define SENT_TX_1_CLK_DIV_FRAC_SHIFT (16u)
#define SENT_TX_1_CLK_DIV_INT_MASK   SENT_TX_1_CLK__DIVIDER_MASK
#define SENT_TX_1_CLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_SENT_TX_1_CLK_H) */

/* [] END OF FILE */

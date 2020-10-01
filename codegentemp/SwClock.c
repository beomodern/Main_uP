/*******************************************************************************
* File Name: SwClock.c
* Version 2.20
*
*  Description:
*   Provides system API for the clocking, interrupts and watchdog timer.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <cydevice_trm.h>
#include "SwClock.h"

#if defined CYREG_PERI_DIV_CMD

/*******************************************************************************
* Function Name: SwClock_StartEx
********************************************************************************
*
* Summary:
*  Starts the clock, aligned to the specified running clock.
*
* Parameters:
*  alignClkDiv:  The divider to which phase alignment is performed when the
*    clock is started.
*
* Returns:
*  None
*
*******************************************************************************/
void SwClock_StartEx(uint32 alignClkDiv)
{
    /* Make sure any previous start command has finished. */
    while((SwClock_CMD_REG & SwClock_CMD_ENABLE_MASK) != 0u)
    {
    }
    
    /* Specify the target divider and it's alignment divider, and enable. */
    SwClock_CMD_REG =
        ((uint32)SwClock__DIV_ID << SwClock_CMD_DIV_SHIFT)|
        (alignClkDiv << SwClock_CMD_PA_DIV_SHIFT) |
        (uint32)SwClock_CMD_ENABLE_MASK;
}

#else

/*******************************************************************************
* Function Name: SwClock_Start
********************************************************************************
*
* Summary:
*  Starts the clock.
*
* Parameters:
*  None
*
* Returns:
*  None
*
*******************************************************************************/

void SwClock_Start(void)
{
    /* Set the bit to enable the clock. */
    SwClock_ENABLE_REG |= SwClock__ENABLE_MASK;
}

#endif /* CYREG_PERI_DIV_CMD */


/*******************************************************************************
* Function Name: SwClock_Stop
********************************************************************************
*
* Summary:
*  Stops the clock and returns immediately. This API does not require the
*  source clock to be running but may return before the hardware is actually
*  disabled.
*
* Parameters:
*  None
*
* Returns:
*  None
*
*******************************************************************************/
void SwClock_Stop(void)
{
#if defined CYREG_PERI_DIV_CMD

    /* Make sure any previous start command has finished. */
    while((SwClock_CMD_REG & SwClock_CMD_ENABLE_MASK) != 0u)
    {
    }
    
    /* Specify the target divider and it's alignment divider, and disable. */
    SwClock_CMD_REG =
        ((uint32)SwClock__DIV_ID << SwClock_CMD_DIV_SHIFT)|
        ((uint32)SwClock_CMD_DISABLE_MASK);

#else

    /* Clear the bit to disable the clock. */
    SwClock_ENABLE_REG &= (uint32)(~SwClock__ENABLE_MASK);
    
#endif /* CYREG_PERI_DIV_CMD */
}


/*******************************************************************************
* Function Name: SwClock_SetFractionalDividerRegister
********************************************************************************
*
* Summary:
*  Modifies the clock divider and the fractional divider.
*
* Parameters:
*  clkDivider:  Divider register value (0-65535). This value is NOT the
*    divider; the clock hardware divides by clkDivider plus one. For example,
*    to divide the clock by 2, this parameter should be set to 1.
*  fracDivider:  Fractional Divider register value (0-31).
* Returns:
*  None
*
*******************************************************************************/
void SwClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional)
{
    uint32 maskVal;
    uint32 regVal;
    
#if defined (SwClock__FRAC_MASK) || defined (CYREG_PERI_DIV_CMD)
    
	/* get all but divider bits */
    maskVal = SwClock_DIV_REG & 
                    (uint32)(~(uint32)(SwClock_DIV_INT_MASK | SwClock_DIV_FRAC_MASK)); 
	/* combine mask and new divider vals into 32-bit value */
    regVal = maskVal |
        ((uint32)((uint32)clkDivider <<  SwClock_DIV_INT_SHIFT) & SwClock_DIV_INT_MASK) |
        ((uint32)((uint32)clkFractional << SwClock_DIV_FRAC_SHIFT) & SwClock_DIV_FRAC_MASK);
    
#else
    /* get all but integer divider bits */
    maskVal = SwClock_DIV_REG & (uint32)(~(uint32)SwClock__DIVIDER_MASK);
    /* combine mask and new divider val into 32-bit value */
    regVal = clkDivider | maskVal;
    
#endif /* SwClock__FRAC_MASK || CYREG_PERI_DIV_CMD */

    SwClock_DIV_REG = regVal;
}


/*******************************************************************************
* Function Name: SwClock_GetDividerRegister
********************************************************************************
*
* Summary:
*  Gets the clock divider register value.
*
* Parameters:
*  None
*
* Returns:
*  Divide value of the clock minus 1. For example, if the clock is set to
*  divide by 2, the return value will be 1.
*
*******************************************************************************/
uint16 SwClock_GetDividerRegister(void)
{
    return (uint16)((SwClock_DIV_REG & SwClock_DIV_INT_MASK)
        >> SwClock_DIV_INT_SHIFT);
}


/*******************************************************************************
* Function Name: SwClock_GetFractionalDividerRegister
********************************************************************************
*
* Summary:
*  Gets the clock fractional divider register value.
*
* Parameters:
*  None
*
* Returns:
*  Fractional Divide value of the clock
*  0 if the fractional divider is not in use.
*
*******************************************************************************/
uint8 SwClock_GetFractionalDividerRegister(void)
{
#if defined (SwClock__FRAC_MASK)
    /* return fractional divider bits */
    return (uint8)((SwClock_DIV_REG & SwClock_DIV_FRAC_MASK)
        >> SwClock_DIV_FRAC_SHIFT);
#else
    return 0u;
#endif /* SwClock__FRAC_MASK */
}


/* [] END OF FILE */

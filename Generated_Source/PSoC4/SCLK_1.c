/*******************************************************************************
* File Name: SCLK_1.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "SCLK_1.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        SCLK_1_PC =   (SCLK_1_PC & \
                                (uint32)(~(uint32)(SCLK_1_DRIVE_MODE_IND_MASK << (SCLK_1_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (SCLK_1_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: SCLK_1_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void SCLK_1_Write(uint8 value) 
{
    uint8 drVal = (uint8)(SCLK_1_DR & (uint8)(~SCLK_1_MASK));
    drVal = (drVal | ((uint8)(value << SCLK_1_SHIFT) & SCLK_1_MASK));
    SCLK_1_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: SCLK_1_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  SCLK_1_DM_STRONG     Strong Drive 
*  SCLK_1_DM_OD_HI      Open Drain, Drives High 
*  SCLK_1_DM_OD_LO      Open Drain, Drives Low 
*  SCLK_1_DM_RES_UP     Resistive Pull Up 
*  SCLK_1_DM_RES_DWN    Resistive Pull Down 
*  SCLK_1_DM_RES_UPDWN  Resistive Pull Up/Down 
*  SCLK_1_DM_DIG_HIZ    High Impedance Digital 
*  SCLK_1_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void SCLK_1_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(SCLK_1__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: SCLK_1_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro SCLK_1_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SCLK_1_Read(void) 
{
    return (uint8)((SCLK_1_PS & SCLK_1_MASK) >> SCLK_1_SHIFT);
}


/*******************************************************************************
* Function Name: SCLK_1_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 SCLK_1_ReadDataReg(void) 
{
    return (uint8)((SCLK_1_DR & SCLK_1_MASK) >> SCLK_1_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SCLK_1_INTSTAT) 

    /*******************************************************************************
    * Function Name: SCLK_1_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 SCLK_1_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(SCLK_1_INTSTAT & SCLK_1_MASK);
		SCLK_1_INTSTAT = maskedStatus;
        return maskedStatus >> SCLK_1_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */

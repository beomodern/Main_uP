/*******************************************************************************
* File Name: MODE.c  
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
#include "MODE.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        MODE_PC =   (MODE_PC & \
                                (uint32)(~(uint32)(MODE_DRIVE_MODE_IND_MASK << (MODE_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (MODE_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: MODE_Write
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
void MODE_Write(uint8 value) 
{
    uint8 drVal = (uint8)(MODE_DR & (uint8)(~MODE_MASK));
    drVal = (drVal | ((uint8)(value << MODE_SHIFT) & MODE_MASK));
    MODE_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: MODE_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  MODE_DM_STRONG     Strong Drive 
*  MODE_DM_OD_HI      Open Drain, Drives High 
*  MODE_DM_OD_LO      Open Drain, Drives Low 
*  MODE_DM_RES_UP     Resistive Pull Up 
*  MODE_DM_RES_DWN    Resistive Pull Down 
*  MODE_DM_RES_UPDWN  Resistive Pull Up/Down 
*  MODE_DM_DIG_HIZ    High Impedance Digital 
*  MODE_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void MODE_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(MODE__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: MODE_Read
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
*  Macro MODE_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 MODE_Read(void) 
{
    return (uint8)((MODE_PS & MODE_MASK) >> MODE_SHIFT);
}


/*******************************************************************************
* Function Name: MODE_ReadDataReg
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
uint8 MODE_ReadDataReg(void) 
{
    return (uint8)((MODE_DR & MODE_MASK) >> MODE_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(MODE_INTSTAT) 

    /*******************************************************************************
    * Function Name: MODE_ClearInterrupt
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
    uint8 MODE_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(MODE_INTSTAT & MODE_MASK);
		MODE_INTSTAT = maskedStatus;
        return maskedStatus >> MODE_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */

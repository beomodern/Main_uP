/*******************************************************************************
* File Name: PWR_OK.c  
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
#include "PWR_OK.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        PWR_OK_PC =   (PWR_OK_PC & \
                                (uint32)(~(uint32)(PWR_OK_DRIVE_MODE_IND_MASK << (PWR_OK_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (PWR_OK_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: PWR_OK_Write
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
void PWR_OK_Write(uint8 value) 
{
    uint8 drVal = (uint8)(PWR_OK_DR & (uint8)(~PWR_OK_MASK));
    drVal = (drVal | ((uint8)(value << PWR_OK_SHIFT) & PWR_OK_MASK));
    PWR_OK_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: PWR_OK_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  PWR_OK_DM_STRONG     Strong Drive 
*  PWR_OK_DM_OD_HI      Open Drain, Drives High 
*  PWR_OK_DM_OD_LO      Open Drain, Drives Low 
*  PWR_OK_DM_RES_UP     Resistive Pull Up 
*  PWR_OK_DM_RES_DWN    Resistive Pull Down 
*  PWR_OK_DM_RES_UPDWN  Resistive Pull Up/Down 
*  PWR_OK_DM_DIG_HIZ    High Impedance Digital 
*  PWR_OK_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void PWR_OK_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(PWR_OK__0__SHIFT, mode);
	SetP4PinDriveMode(PWR_OK__1__SHIFT, mode);
}


/*******************************************************************************
* Function Name: PWR_OK_Read
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
*  Macro PWR_OK_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PWR_OK_Read(void) 
{
    return (uint8)((PWR_OK_PS & PWR_OK_MASK) >> PWR_OK_SHIFT);
}


/*******************************************************************************
* Function Name: PWR_OK_ReadDataReg
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
uint8 PWR_OK_ReadDataReg(void) 
{
    return (uint8)((PWR_OK_DR & PWR_OK_MASK) >> PWR_OK_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PWR_OK_INTSTAT) 

    /*******************************************************************************
    * Function Name: PWR_OK_ClearInterrupt
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
    uint8 PWR_OK_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(PWR_OK_INTSTAT & PWR_OK_MASK);
		PWR_OK_INTSTAT = maskedStatus;
        return maskedStatus >> PWR_OK_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */

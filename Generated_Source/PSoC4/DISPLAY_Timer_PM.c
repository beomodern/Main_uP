/*******************************************************************************
* File Name: DISPLAY_Timer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "DISPLAY_Timer.h"

static DISPLAY_Timer_backupStruct DISPLAY_Timer_backup;


/*******************************************************************************
* Function Name: DISPLAY_Timer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  DISPLAY_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void DISPLAY_Timer_SaveConfig(void) 
{
    #if (!DISPLAY_Timer_UsingFixedFunction)
        DISPLAY_Timer_backup.TimerUdb = DISPLAY_Timer_ReadCounter();
        DISPLAY_Timer_backup.InterruptMaskValue = DISPLAY_Timer_STATUS_MASK;
        #if (DISPLAY_Timer_UsingHWCaptureCounter)
            DISPLAY_Timer_backup.TimerCaptureCounter = DISPLAY_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!DISPLAY_Timer_UDB_CONTROL_REG_REMOVED)
            DISPLAY_Timer_backup.TimerControlRegister = DISPLAY_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: DISPLAY_Timer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  DISPLAY_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void DISPLAY_Timer_RestoreConfig(void) 
{   
    #if (!DISPLAY_Timer_UsingFixedFunction)

        DISPLAY_Timer_WriteCounter(DISPLAY_Timer_backup.TimerUdb);
        DISPLAY_Timer_STATUS_MASK =DISPLAY_Timer_backup.InterruptMaskValue;
        #if (DISPLAY_Timer_UsingHWCaptureCounter)
            DISPLAY_Timer_SetCaptureCount(DISPLAY_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!DISPLAY_Timer_UDB_CONTROL_REG_REMOVED)
            DISPLAY_Timer_WriteControlRegister(DISPLAY_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: DISPLAY_Timer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  DISPLAY_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void DISPLAY_Timer_Sleep(void) 
{
    #if(!DISPLAY_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(DISPLAY_Timer_CTRL_ENABLE == (DISPLAY_Timer_CONTROL & DISPLAY_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            DISPLAY_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            DISPLAY_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    DISPLAY_Timer_Stop();
    DISPLAY_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: DISPLAY_Timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  DISPLAY_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void DISPLAY_Timer_Wakeup(void) 
{
    DISPLAY_Timer_RestoreConfig();
    #if(!DISPLAY_Timer_UDB_CONTROL_REG_REMOVED)
        if(DISPLAY_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                DISPLAY_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

/*******************************************************************************
* File Name: DATALINK_Timer_PM.c
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

#include "DATALINK_Timer.h"

static DATALINK_Timer_backupStruct DATALINK_Timer_backup;


/*******************************************************************************
* Function Name: DATALINK_Timer_SaveConfig
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
*  DATALINK_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void DATALINK_Timer_SaveConfig(void) 
{
    #if (!DATALINK_Timer_UsingFixedFunction)
        DATALINK_Timer_backup.TimerUdb = DATALINK_Timer_ReadCounter();
        DATALINK_Timer_backup.InterruptMaskValue = DATALINK_Timer_STATUS_MASK;
        #if (DATALINK_Timer_UsingHWCaptureCounter)
            DATALINK_Timer_backup.TimerCaptureCounter = DATALINK_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!DATALINK_Timer_UDB_CONTROL_REG_REMOVED)
            DATALINK_Timer_backup.TimerControlRegister = DATALINK_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: DATALINK_Timer_RestoreConfig
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
*  DATALINK_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void DATALINK_Timer_RestoreConfig(void) 
{   
    #if (!DATALINK_Timer_UsingFixedFunction)

        DATALINK_Timer_WriteCounter(DATALINK_Timer_backup.TimerUdb);
        DATALINK_Timer_STATUS_MASK =DATALINK_Timer_backup.InterruptMaskValue;
        #if (DATALINK_Timer_UsingHWCaptureCounter)
            DATALINK_Timer_SetCaptureCount(DATALINK_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!DATALINK_Timer_UDB_CONTROL_REG_REMOVED)
            DATALINK_Timer_WriteControlRegister(DATALINK_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: DATALINK_Timer_Sleep
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
*  DATALINK_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void DATALINK_Timer_Sleep(void) 
{
    #if(!DATALINK_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(DATALINK_Timer_CTRL_ENABLE == (DATALINK_Timer_CONTROL & DATALINK_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            DATALINK_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            DATALINK_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    DATALINK_Timer_Stop();
    DATALINK_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: DATALINK_Timer_Wakeup
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
*  DATALINK_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void DATALINK_Timer_Wakeup(void) 
{
    DATALINK_Timer_RestoreConfig();
    #if(!DATALINK_Timer_UDB_CONTROL_REG_REMOVED)
        if(DATALINK_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                DATALINK_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

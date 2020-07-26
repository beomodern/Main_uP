/*******************************************************************************
* File Name: SENT_TX_1_PWM_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SENT_TX_1_PWM.h"

static SENT_TX_1_PWM_BACKUP_STRUCT SENT_TX_1_PWM_backup;


/*******************************************************************************
* Function Name: SENT_TX_1_PWM_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SENT_TX_1_PWM_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: SENT_TX_1_PWM_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SENT_TX_1_PWM_Sleep(void)
{
    if(0u != (SENT_TX_1_PWM_BLOCK_CONTROL_REG & SENT_TX_1_PWM_MASK))
    {
        SENT_TX_1_PWM_backup.enableState = 1u;
    }
    else
    {
        SENT_TX_1_PWM_backup.enableState = 0u;
    }

    SENT_TX_1_PWM_Stop();
    SENT_TX_1_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: SENT_TX_1_PWM_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SENT_TX_1_PWM_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: SENT_TX_1_PWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SENT_TX_1_PWM_Wakeup(void)
{
    SENT_TX_1_PWM_RestoreConfig();

    if(0u != SENT_TX_1_PWM_backup.enableState)
    {
        SENT_TX_1_PWM_Enable();
    }
}


/* [] END OF FILE */

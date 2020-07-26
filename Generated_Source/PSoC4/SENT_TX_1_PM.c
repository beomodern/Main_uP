/*******************************************************************************
* \file Name: SENT_TX_1_PM.c
* \version 1.0
*
* This file contains the setup, control, and status commands to support
* the component in Low-Power modes.
*
********************************************************************************
* \copyright
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SENT_TX_1.h"


/*******************************************************************************
* Function Name: SENT_TX_1_Sleep
****************************************************************************//**
*
* Stops the component operation and saves the user configuration.
*
* Before call this function, ensure that SENT is ready to sleep by checking the 
* SENT_TX_1_status flag. For this purpose, use the 
* SENT_TX_1_GetStatus() function.
*
* \return
* CYRET_SUCCESS the SENT went into sleep. <br>
* CYRET_CANCELED the SENT did not go into sleep, because SENT still sending 
* previous data, SENT_TX_1_status = SENT_TX_1_BUSY. 
*
*******************************************************************************/
uint32 SENT_TX_1_Sleep(void)
{
    uint32 retVal = CYRET_CANCELED;

    if(SENT_TX_1_READY == SENT_TX_1_status)
    {
        SENT_TX_1_PWM_Sleep();
        retVal = CYRET_SUCCESS;
    }

    return (retVal);
}


/* [] END OF FILE */

/*******************************************************************************
* File Name: BT_SBC.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "BT_SBC.h"

static BT_SBC_BACKUP_STRUCT  BT_SBC_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: BT_SBC_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet BT_SBC_SUT.c usage_BT_SBC_Sleep_Wakeup
*******************************************************************************/
void BT_SBC_Sleep(void)
{
    #if defined(BT_SBC__PC)
        BT_SBC_backup.pcState = BT_SBC_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            BT_SBC_backup.usbState = BT_SBC_CR1_REG;
            BT_SBC_USB_POWER_REG |= BT_SBC_USBIO_ENTER_SLEEP;
            BT_SBC_CR1_REG &= BT_SBC_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BT_SBC__SIO)
        BT_SBC_backup.sioState = BT_SBC_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        BT_SBC_SIO_REG &= (uint32)(~BT_SBC_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: BT_SBC_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to BT_SBC_Sleep() for an example usage.
*******************************************************************************/
void BT_SBC_Wakeup(void)
{
    #if defined(BT_SBC__PC)
        BT_SBC_PC = BT_SBC_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            BT_SBC_USB_POWER_REG &= BT_SBC_USBIO_EXIT_SLEEP_PH1;
            BT_SBC_CR1_REG = BT_SBC_backup.usbState;
            BT_SBC_USB_POWER_REG &= BT_SBC_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BT_SBC__SIO)
        BT_SBC_SIO_REG = BT_SBC_backup.sioState;
    #endif
}


/* [] END OF FILE */

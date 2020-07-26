/*******************************************************************************
* File Name: BT_Tx_Rx.c  
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
#include "BT_Tx_Rx.h"

static BT_Tx_Rx_BACKUP_STRUCT  BT_Tx_Rx_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: BT_Tx_Rx_Sleep
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
*  \snippet BT_Tx_Rx_SUT.c usage_BT_Tx_Rx_Sleep_Wakeup
*******************************************************************************/
void BT_Tx_Rx_Sleep(void)
{
    #if defined(BT_Tx_Rx__PC)
        BT_Tx_Rx_backup.pcState = BT_Tx_Rx_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            BT_Tx_Rx_backup.usbState = BT_Tx_Rx_CR1_REG;
            BT_Tx_Rx_USB_POWER_REG |= BT_Tx_Rx_USBIO_ENTER_SLEEP;
            BT_Tx_Rx_CR1_REG &= BT_Tx_Rx_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BT_Tx_Rx__SIO)
        BT_Tx_Rx_backup.sioState = BT_Tx_Rx_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        BT_Tx_Rx_SIO_REG &= (uint32)(~BT_Tx_Rx_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: BT_Tx_Rx_Wakeup
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
*  Refer to BT_Tx_Rx_Sleep() for an example usage.
*******************************************************************************/
void BT_Tx_Rx_Wakeup(void)
{
    #if defined(BT_Tx_Rx__PC)
        BT_Tx_Rx_PC = BT_Tx_Rx_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            BT_Tx_Rx_USB_POWER_REG &= BT_Tx_Rx_USBIO_EXIT_SLEEP_PH1;
            BT_Tx_Rx_CR1_REG = BT_Tx_Rx_backup.usbState;
            BT_Tx_Rx_USB_POWER_REG &= BT_Tx_Rx_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BT_Tx_Rx__SIO)
        BT_Tx_Rx_SIO_REG = BT_Tx_Rx_backup.sioState;
    #endif
}


/* [] END OF FILE */

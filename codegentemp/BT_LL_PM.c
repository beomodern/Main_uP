/*******************************************************************************
* File Name: BT_LL.c  
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
#include "BT_LL.h"

static BT_LL_BACKUP_STRUCT  BT_LL_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: BT_LL_Sleep
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
*  \snippet BT_LL_SUT.c usage_BT_LL_Sleep_Wakeup
*******************************************************************************/
void BT_LL_Sleep(void)
{
    #if defined(BT_LL__PC)
        BT_LL_backup.pcState = BT_LL_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            BT_LL_backup.usbState = BT_LL_CR1_REG;
            BT_LL_USB_POWER_REG |= BT_LL_USBIO_ENTER_SLEEP;
            BT_LL_CR1_REG &= BT_LL_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BT_LL__SIO)
        BT_LL_backup.sioState = BT_LL_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        BT_LL_SIO_REG &= (uint32)(~BT_LL_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: BT_LL_Wakeup
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
*  Refer to BT_LL_Sleep() for an example usage.
*******************************************************************************/
void BT_LL_Wakeup(void)
{
    #if defined(BT_LL__PC)
        BT_LL_PC = BT_LL_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            BT_LL_USB_POWER_REG &= BT_LL_USBIO_EXIT_SLEEP_PH1;
            BT_LL_CR1_REG = BT_LL_backup.usbState;
            BT_LL_USB_POWER_REG &= BT_LL_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BT_LL__SIO)
        BT_LL_SIO_REG = BT_LL_backup.sioState;
    #endif
}


/* [] END OF FILE */

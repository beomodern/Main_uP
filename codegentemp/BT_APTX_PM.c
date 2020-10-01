/*******************************************************************************
* File Name: BT_APTX.c  
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
#include "BT_APTX.h"

static BT_APTX_BACKUP_STRUCT  BT_APTX_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: BT_APTX_Sleep
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
*  \snippet BT_APTX_SUT.c usage_BT_APTX_Sleep_Wakeup
*******************************************************************************/
void BT_APTX_Sleep(void)
{
    #if defined(BT_APTX__PC)
        BT_APTX_backup.pcState = BT_APTX_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            BT_APTX_backup.usbState = BT_APTX_CR1_REG;
            BT_APTX_USB_POWER_REG |= BT_APTX_USBIO_ENTER_SLEEP;
            BT_APTX_CR1_REG &= BT_APTX_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BT_APTX__SIO)
        BT_APTX_backup.sioState = BT_APTX_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        BT_APTX_SIO_REG &= (uint32)(~BT_APTX_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: BT_APTX_Wakeup
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
*  Refer to BT_APTX_Sleep() for an example usage.
*******************************************************************************/
void BT_APTX_Wakeup(void)
{
    #if defined(BT_APTX__PC)
        BT_APTX_PC = BT_APTX_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            BT_APTX_USB_POWER_REG &= BT_APTX_USBIO_EXIT_SLEEP_PH1;
            BT_APTX_CR1_REG = BT_APTX_backup.usbState;
            BT_APTX_USB_POWER_REG &= BT_APTX_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BT_APTX__SIO)
        BT_APTX_SIO_REG = BT_APTX_backup.sioState;
    #endif
}


/* [] END OF FILE */

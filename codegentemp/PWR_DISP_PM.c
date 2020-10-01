/*******************************************************************************
* File Name: PWR_DISP.c  
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
#include "PWR_DISP.h"

static PWR_DISP_BACKUP_STRUCT  PWR_DISP_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PWR_DISP_Sleep
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
*  \snippet PWR_DISP_SUT.c usage_PWR_DISP_Sleep_Wakeup
*******************************************************************************/
void PWR_DISP_Sleep(void)
{
    #if defined(PWR_DISP__PC)
        PWR_DISP_backup.pcState = PWR_DISP_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PWR_DISP_backup.usbState = PWR_DISP_CR1_REG;
            PWR_DISP_USB_POWER_REG |= PWR_DISP_USBIO_ENTER_SLEEP;
            PWR_DISP_CR1_REG &= PWR_DISP_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PWR_DISP__SIO)
        PWR_DISP_backup.sioState = PWR_DISP_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PWR_DISP_SIO_REG &= (uint32)(~PWR_DISP_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PWR_DISP_Wakeup
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
*  Refer to PWR_DISP_Sleep() for an example usage.
*******************************************************************************/
void PWR_DISP_Wakeup(void)
{
    #if defined(PWR_DISP__PC)
        PWR_DISP_PC = PWR_DISP_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PWR_DISP_USB_POWER_REG &= PWR_DISP_USBIO_EXIT_SLEEP_PH1;
            PWR_DISP_CR1_REG = PWR_DISP_backup.usbState;
            PWR_DISP_USB_POWER_REG &= PWR_DISP_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PWR_DISP__SIO)
        PWR_DISP_SIO_REG = PWR_DISP_backup.sioState;
    #endif
}


/* [] END OF FILE */

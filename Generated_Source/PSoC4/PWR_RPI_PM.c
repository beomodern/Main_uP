/*******************************************************************************
* File Name: PWR_RPI.c  
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
#include "PWR_RPI.h"

static PWR_RPI_BACKUP_STRUCT  PWR_RPI_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PWR_RPI_Sleep
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
*  \snippet PWR_RPI_SUT.c usage_PWR_RPI_Sleep_Wakeup
*******************************************************************************/
void PWR_RPI_Sleep(void)
{
    #if defined(PWR_RPI__PC)
        PWR_RPI_backup.pcState = PWR_RPI_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PWR_RPI_backup.usbState = PWR_RPI_CR1_REG;
            PWR_RPI_USB_POWER_REG |= PWR_RPI_USBIO_ENTER_SLEEP;
            PWR_RPI_CR1_REG &= PWR_RPI_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PWR_RPI__SIO)
        PWR_RPI_backup.sioState = PWR_RPI_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PWR_RPI_SIO_REG &= (uint32)(~PWR_RPI_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PWR_RPI_Wakeup
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
*  Refer to PWR_RPI_Sleep() for an example usage.
*******************************************************************************/
void PWR_RPI_Wakeup(void)
{
    #if defined(PWR_RPI__PC)
        PWR_RPI_PC = PWR_RPI_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PWR_RPI_USB_POWER_REG &= PWR_RPI_USBIO_EXIT_SLEEP_PH1;
            PWR_RPI_CR1_REG = PWR_RPI_backup.usbState;
            PWR_RPI_USB_POWER_REG &= PWR_RPI_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PWR_RPI__SIO)
        PWR_RPI_SIO_REG = PWR_RPI_backup.sioState;
    #endif
}


/* [] END OF FILE */

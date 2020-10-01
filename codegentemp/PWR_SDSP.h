/*******************************************************************************
* File Name: PWR_SDSP.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PWR_SDSP_H) /* Pins PWR_SDSP_H */
#define CY_PINS_PWR_SDSP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PWR_SDSP_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} PWR_SDSP_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PWR_SDSP_Read(void);
void    PWR_SDSP_Write(uint8 value);
uint8   PWR_SDSP_ReadDataReg(void);
#if defined(PWR_SDSP__PC) || (CY_PSOC4_4200L) 
    void    PWR_SDSP_SetDriveMode(uint8 mode);
#endif
void    PWR_SDSP_SetInterruptMode(uint16 position, uint16 mode);
uint8   PWR_SDSP_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PWR_SDSP_Sleep(void); 
void PWR_SDSP_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PWR_SDSP__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PWR_SDSP_DRIVE_MODE_BITS        (3)
    #define PWR_SDSP_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PWR_SDSP_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PWR_SDSP_SetDriveMode() function.
         *  @{
         */
        #define PWR_SDSP_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PWR_SDSP_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PWR_SDSP_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PWR_SDSP_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PWR_SDSP_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PWR_SDSP_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PWR_SDSP_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PWR_SDSP_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PWR_SDSP_MASK               PWR_SDSP__MASK
#define PWR_SDSP_SHIFT              PWR_SDSP__SHIFT
#define PWR_SDSP_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PWR_SDSP_SetInterruptMode() function.
     *  @{
     */
        #define PWR_SDSP_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PWR_SDSP_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PWR_SDSP_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PWR_SDSP_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PWR_SDSP__SIO)
    #define PWR_SDSP_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PWR_SDSP__PC) && (CY_PSOC4_4200L)
    #define PWR_SDSP_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PWR_SDSP_USBIO_DISABLE              ((uint32)(~PWR_SDSP_USBIO_ENABLE))
    #define PWR_SDSP_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PWR_SDSP_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PWR_SDSP_USBIO_ENTER_SLEEP          ((uint32)((1u << PWR_SDSP_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PWR_SDSP_USBIO_SUSPEND_DEL_SHIFT)))
    #define PWR_SDSP_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PWR_SDSP_USBIO_SUSPEND_SHIFT)))
    #define PWR_SDSP_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PWR_SDSP_USBIO_SUSPEND_DEL_SHIFT)))
    #define PWR_SDSP_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PWR_SDSP__PC)
    /* Port Configuration */
    #define PWR_SDSP_PC                 (* (reg32 *) PWR_SDSP__PC)
#endif
/* Pin State */
#define PWR_SDSP_PS                     (* (reg32 *) PWR_SDSP__PS)
/* Data Register */
#define PWR_SDSP_DR                     (* (reg32 *) PWR_SDSP__DR)
/* Input Buffer Disable Override */
#define PWR_SDSP_INP_DIS                (* (reg32 *) PWR_SDSP__PC2)

/* Interrupt configuration Registers */
#define PWR_SDSP_INTCFG                 (* (reg32 *) PWR_SDSP__INTCFG)
#define PWR_SDSP_INTSTAT                (* (reg32 *) PWR_SDSP__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PWR_SDSP_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PWR_SDSP__SIO)
    #define PWR_SDSP_SIO_REG            (* (reg32 *) PWR_SDSP__SIO)
#endif /* (PWR_SDSP__SIO_CFG) */

/* USBIO registers */
#if !defined(PWR_SDSP__PC) && (CY_PSOC4_4200L)
    #define PWR_SDSP_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PWR_SDSP_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PWR_SDSP_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PWR_SDSP_DRIVE_MODE_SHIFT       (0x00u)
#define PWR_SDSP_DRIVE_MODE_MASK        (0x07u << PWR_SDSP_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PWR_SDSP_H */


/* [] END OF FILE */

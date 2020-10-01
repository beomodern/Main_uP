/*******************************************************************************
* File Name: BT_LL.h  
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

#if !defined(CY_PINS_BT_LL_H) /* Pins BT_LL_H */
#define CY_PINS_BT_LL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BT_LL_aliases.h"


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
} BT_LL_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BT_LL_Read(void);
void    BT_LL_Write(uint8 value);
uint8   BT_LL_ReadDataReg(void);
#if defined(BT_LL__PC) || (CY_PSOC4_4200L) 
    void    BT_LL_SetDriveMode(uint8 mode);
#endif
void    BT_LL_SetInterruptMode(uint16 position, uint16 mode);
uint8   BT_LL_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BT_LL_Sleep(void); 
void BT_LL_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BT_LL__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BT_LL_DRIVE_MODE_BITS        (3)
    #define BT_LL_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BT_LL_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BT_LL_SetDriveMode() function.
         *  @{
         */
        #define BT_LL_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BT_LL_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BT_LL_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BT_LL_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BT_LL_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BT_LL_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BT_LL_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BT_LL_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BT_LL_MASK               BT_LL__MASK
#define BT_LL_SHIFT              BT_LL__SHIFT
#define BT_LL_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BT_LL_SetInterruptMode() function.
     *  @{
     */
        #define BT_LL_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BT_LL_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BT_LL_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BT_LL_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BT_LL__SIO)
    #define BT_LL_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BT_LL__PC) && (CY_PSOC4_4200L)
    #define BT_LL_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BT_LL_USBIO_DISABLE              ((uint32)(~BT_LL_USBIO_ENABLE))
    #define BT_LL_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BT_LL_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BT_LL_USBIO_ENTER_SLEEP          ((uint32)((1u << BT_LL_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BT_LL_USBIO_SUSPEND_DEL_SHIFT)))
    #define BT_LL_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BT_LL_USBIO_SUSPEND_SHIFT)))
    #define BT_LL_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BT_LL_USBIO_SUSPEND_DEL_SHIFT)))
    #define BT_LL_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BT_LL__PC)
    /* Port Configuration */
    #define BT_LL_PC                 (* (reg32 *) BT_LL__PC)
#endif
/* Pin State */
#define BT_LL_PS                     (* (reg32 *) BT_LL__PS)
/* Data Register */
#define BT_LL_DR                     (* (reg32 *) BT_LL__DR)
/* Input Buffer Disable Override */
#define BT_LL_INP_DIS                (* (reg32 *) BT_LL__PC2)

/* Interrupt configuration Registers */
#define BT_LL_INTCFG                 (* (reg32 *) BT_LL__INTCFG)
#define BT_LL_INTSTAT                (* (reg32 *) BT_LL__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BT_LL_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BT_LL__SIO)
    #define BT_LL_SIO_REG            (* (reg32 *) BT_LL__SIO)
#endif /* (BT_LL__SIO_CFG) */

/* USBIO registers */
#if !defined(BT_LL__PC) && (CY_PSOC4_4200L)
    #define BT_LL_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BT_LL_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BT_LL_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BT_LL_DRIVE_MODE_SHIFT       (0x00u)
#define BT_LL_DRIVE_MODE_MASK        (0x07u << BT_LL_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BT_LL_H */


/* [] END OF FILE */

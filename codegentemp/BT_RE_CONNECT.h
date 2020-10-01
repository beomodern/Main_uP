/*******************************************************************************
* File Name: BT_RE_CONNECT.h  
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

#if !defined(CY_PINS_BT_RE_CONNECT_H) /* Pins BT_RE_CONNECT_H */
#define CY_PINS_BT_RE_CONNECT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BT_RE_CONNECT_aliases.h"


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
} BT_RE_CONNECT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BT_RE_CONNECT_Read(void);
void    BT_RE_CONNECT_Write(uint8 value);
uint8   BT_RE_CONNECT_ReadDataReg(void);
#if defined(BT_RE_CONNECT__PC) || (CY_PSOC4_4200L) 
    void    BT_RE_CONNECT_SetDriveMode(uint8 mode);
#endif
void    BT_RE_CONNECT_SetInterruptMode(uint16 position, uint16 mode);
uint8   BT_RE_CONNECT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BT_RE_CONNECT_Sleep(void); 
void BT_RE_CONNECT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BT_RE_CONNECT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BT_RE_CONNECT_DRIVE_MODE_BITS        (3)
    #define BT_RE_CONNECT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BT_RE_CONNECT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BT_RE_CONNECT_SetDriveMode() function.
         *  @{
         */
        #define BT_RE_CONNECT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BT_RE_CONNECT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BT_RE_CONNECT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BT_RE_CONNECT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BT_RE_CONNECT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BT_RE_CONNECT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BT_RE_CONNECT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BT_RE_CONNECT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BT_RE_CONNECT_MASK               BT_RE_CONNECT__MASK
#define BT_RE_CONNECT_SHIFT              BT_RE_CONNECT__SHIFT
#define BT_RE_CONNECT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BT_RE_CONNECT_SetInterruptMode() function.
     *  @{
     */
        #define BT_RE_CONNECT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BT_RE_CONNECT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BT_RE_CONNECT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BT_RE_CONNECT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BT_RE_CONNECT__SIO)
    #define BT_RE_CONNECT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BT_RE_CONNECT__PC) && (CY_PSOC4_4200L)
    #define BT_RE_CONNECT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BT_RE_CONNECT_USBIO_DISABLE              ((uint32)(~BT_RE_CONNECT_USBIO_ENABLE))
    #define BT_RE_CONNECT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BT_RE_CONNECT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BT_RE_CONNECT_USBIO_ENTER_SLEEP          ((uint32)((1u << BT_RE_CONNECT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BT_RE_CONNECT_USBIO_SUSPEND_DEL_SHIFT)))
    #define BT_RE_CONNECT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BT_RE_CONNECT_USBIO_SUSPEND_SHIFT)))
    #define BT_RE_CONNECT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BT_RE_CONNECT_USBIO_SUSPEND_DEL_SHIFT)))
    #define BT_RE_CONNECT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BT_RE_CONNECT__PC)
    /* Port Configuration */
    #define BT_RE_CONNECT_PC                 (* (reg32 *) BT_RE_CONNECT__PC)
#endif
/* Pin State */
#define BT_RE_CONNECT_PS                     (* (reg32 *) BT_RE_CONNECT__PS)
/* Data Register */
#define BT_RE_CONNECT_DR                     (* (reg32 *) BT_RE_CONNECT__DR)
/* Input Buffer Disable Override */
#define BT_RE_CONNECT_INP_DIS                (* (reg32 *) BT_RE_CONNECT__PC2)

/* Interrupt configuration Registers */
#define BT_RE_CONNECT_INTCFG                 (* (reg32 *) BT_RE_CONNECT__INTCFG)
#define BT_RE_CONNECT_INTSTAT                (* (reg32 *) BT_RE_CONNECT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BT_RE_CONNECT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BT_RE_CONNECT__SIO)
    #define BT_RE_CONNECT_SIO_REG            (* (reg32 *) BT_RE_CONNECT__SIO)
#endif /* (BT_RE_CONNECT__SIO_CFG) */

/* USBIO registers */
#if !defined(BT_RE_CONNECT__PC) && (CY_PSOC4_4200L)
    #define BT_RE_CONNECT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BT_RE_CONNECT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BT_RE_CONNECT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BT_RE_CONNECT_DRIVE_MODE_SHIFT       (0x00u)
#define BT_RE_CONNECT_DRIVE_MODE_MASK        (0x07u << BT_RE_CONNECT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BT_RE_CONNECT_H */


/* [] END OF FILE */

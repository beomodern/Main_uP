/*******************************************************************************
* File Name: DATALINK.h  
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

#if !defined(CY_PINS_DATALINK_H) /* Pins DATALINK_H */
#define CY_PINS_DATALINK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DATALINK_aliases.h"


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
} DATALINK_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DATALINK_Read(void);
void    DATALINK_Write(uint8 value);
uint8   DATALINK_ReadDataReg(void);
#if defined(DATALINK__PC) || (CY_PSOC4_4200L) 
    void    DATALINK_SetDriveMode(uint8 mode);
#endif
void    DATALINK_SetInterruptMode(uint16 position, uint16 mode);
uint8   DATALINK_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DATALINK_Sleep(void); 
void DATALINK_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DATALINK__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DATALINK_DRIVE_MODE_BITS        (3)
    #define DATALINK_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DATALINK_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DATALINK_SetDriveMode() function.
         *  @{
         */
        #define DATALINK_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DATALINK_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DATALINK_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DATALINK_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DATALINK_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DATALINK_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DATALINK_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DATALINK_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DATALINK_MASK               DATALINK__MASK
#define DATALINK_SHIFT              DATALINK__SHIFT
#define DATALINK_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DATALINK_SetInterruptMode() function.
     *  @{
     */
        #define DATALINK_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DATALINK_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DATALINK_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DATALINK_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DATALINK__SIO)
    #define DATALINK_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DATALINK__PC) && (CY_PSOC4_4200L)
    #define DATALINK_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DATALINK_USBIO_DISABLE              ((uint32)(~DATALINK_USBIO_ENABLE))
    #define DATALINK_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DATALINK_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DATALINK_USBIO_ENTER_SLEEP          ((uint32)((1u << DATALINK_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DATALINK_USBIO_SUSPEND_DEL_SHIFT)))
    #define DATALINK_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DATALINK_USBIO_SUSPEND_SHIFT)))
    #define DATALINK_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DATALINK_USBIO_SUSPEND_DEL_SHIFT)))
    #define DATALINK_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DATALINK__PC)
    /* Port Configuration */
    #define DATALINK_PC                 (* (reg32 *) DATALINK__PC)
#endif
/* Pin State */
#define DATALINK_PS                     (* (reg32 *) DATALINK__PS)
/* Data Register */
#define DATALINK_DR                     (* (reg32 *) DATALINK__DR)
/* Input Buffer Disable Override */
#define DATALINK_INP_DIS                (* (reg32 *) DATALINK__PC2)

/* Interrupt configuration Registers */
#define DATALINK_INTCFG                 (* (reg32 *) DATALINK__INTCFG)
#define DATALINK_INTSTAT                (* (reg32 *) DATALINK__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DATALINK_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DATALINK__SIO)
    #define DATALINK_SIO_REG            (* (reg32 *) DATALINK__SIO)
#endif /* (DATALINK__SIO_CFG) */

/* USBIO registers */
#if !defined(DATALINK__PC) && (CY_PSOC4_4200L)
    #define DATALINK_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DATALINK_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DATALINK_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DATALINK_DRIVE_MODE_SHIFT       (0x00u)
#define DATALINK_DRIVE_MODE_MASK        (0x07u << DATALINK_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DATALINK_H */


/* [] END OF FILE */

/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_SPIM_H)
#define CY_SCB_PVT_SPIM_H

#include "SPIM.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define SPIM_SetI2CExtClkInterruptMode(interruptMask) SPIM_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define SPIM_ClearI2CExtClkInterruptSource(interruptMask) SPIM_CLEAR_INTR_I2C_EC(interruptMask)
#define SPIM_GetI2CExtClkInterruptSource()                (SPIM_INTR_I2C_EC_REG)
#define SPIM_GetI2CExtClkInterruptMode()                  (SPIM_INTR_I2C_EC_MASK_REG)
#define SPIM_GetI2CExtClkInterruptSourceMasked()          (SPIM_INTR_I2C_EC_MASKED_REG)

#if (!SPIM_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define SPIM_SetSpiExtClkInterruptMode(interruptMask) \
                                                                SPIM_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define SPIM_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                SPIM_CLEAR_INTR_SPI_EC(interruptMask)
    #define SPIM_GetExtSpiClkInterruptSource()                 (SPIM_INTR_SPI_EC_REG)
    #define SPIM_GetExtSpiClkInterruptMode()                   (SPIM_INTR_SPI_EC_MASK_REG)
    #define SPIM_GetExtSpiClkInterruptSourceMasked()           (SPIM_INTR_SPI_EC_MASKED_REG)
#endif /* (!SPIM_CY_SCBIP_V1) */

#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void SPIM_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (SPIM_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_SPIM_CUSTOM_INTR_HANDLER)
    extern cyisraddress SPIM_customIntrHandler;
#endif /* !defined (CY_REMOVE_SPIM_CUSTOM_INTR_HANDLER) */
#endif /* (SPIM_SCB_IRQ_INTERNAL) */

extern SPIM_BACKUP_STRUCT SPIM_backup;

#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 SPIM_scbMode;
    extern uint8 SPIM_scbEnableWake;
    extern uint8 SPIM_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 SPIM_mode;
    extern uint8 SPIM_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * SPIM_rxBuffer;
    extern uint8   SPIM_rxDataBits;
    extern uint32  SPIM_rxBufferSize;

    extern volatile uint8 * SPIM_txBuffer;
    extern uint8   SPIM_txDataBits;
    extern uint32  SPIM_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 SPIM_numberOfAddr;
    extern uint8 SPIM_subAddrSize;
#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (SPIM_SCB_MODE_I2C_CONST_CFG || \
        SPIM_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 SPIM_IntrTxMask;
#endif /* (! (SPIM_SCB_MODE_I2C_CONST_CFG || \
              SPIM_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define SPIM_SCB_MODE_I2C_RUNTM_CFG     (SPIM_SCB_MODE_I2C      == SPIM_scbMode)
    #define SPIM_SCB_MODE_SPI_RUNTM_CFG     (SPIM_SCB_MODE_SPI      == SPIM_scbMode)
    #define SPIM_SCB_MODE_UART_RUNTM_CFG    (SPIM_SCB_MODE_UART     == SPIM_scbMode)
    #define SPIM_SCB_MODE_EZI2C_RUNTM_CFG   (SPIM_SCB_MODE_EZI2C    == SPIM_scbMode)
    #define SPIM_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (SPIM_SCB_MODE_UNCONFIG == SPIM_scbMode)

    /* Defines wakeup enable */
    #define SPIM_SCB_WAKE_ENABLE_CHECK       (0u != SPIM_scbEnableWake)
#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!SPIM_CY_SCBIP_V1)
    #define SPIM_SCB_PINS_NUMBER    (7u)
#else
    #define SPIM_SCB_PINS_NUMBER    (2u)
#endif /* (!SPIM_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_SPIM_H) */


/* [] END OF FILE */

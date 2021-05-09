/***************************************************************************//**
* \file SPIM_BOOT.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_SPIM_H)
#define CY_SCB_BOOT_SPIM_H

#include "SPIM_PVT.h"

#if (SPIM_SCB_MODE_I2C_INC)
    #include "SPIM_I2C.h"
#endif /* (SPIM_SCB_MODE_I2C_INC) */

#if (SPIM_SCB_MODE_EZI2C_INC)
    #include "SPIM_EZI2C.h"
#endif /* (SPIM_SCB_MODE_EZI2C_INC) */

#if (SPIM_SCB_MODE_SPI_INC || SPIM_SCB_MODE_UART_INC)
    #include "SPIM_SPI_UART.h"
#endif /* (SPIM_SCB_MODE_SPI_INC || SPIM_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define SPIM_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPIM) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (SPIM_SCB_MODE_I2C_INC)
    #define SPIM_I2C_BTLDR_COMM_ENABLED     (SPIM_BTLDR_COMM_ENABLED && \
                                                            (SPIM_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             SPIM_I2C_SLAVE_CONST))
#else
     #define SPIM_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (SPIM_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (SPIM_SCB_MODE_EZI2C_INC)
    #define SPIM_EZI2C_BTLDR_COMM_ENABLED   (SPIM_BTLDR_COMM_ENABLED && \
                                                         SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define SPIM_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (SPIM_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (SPIM_SCB_MODE_SPI_INC)
    #define SPIM_SPI_BTLDR_COMM_ENABLED     (SPIM_BTLDR_COMM_ENABLED && \
                                                            (SPIM_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             SPIM_SPI_SLAVE_CONST))
#else
        #define SPIM_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (SPIM_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (SPIM_SCB_MODE_UART_INC)
       #define SPIM_UART_BTLDR_COMM_ENABLED    (SPIM_BTLDR_COMM_ENABLED && \
                                                            (SPIM_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (SPIM_UART_RX_DIRECTION && \
                                                              SPIM_UART_TX_DIRECTION)))
#else
     #define SPIM_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (SPIM_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define SPIM_BTLDR_COMM_MODE_ENABLED    (SPIM_I2C_BTLDR_COMM_ENABLED   || \
                                                     SPIM_SPI_BTLDR_COMM_ENABLED   || \
                                                     SPIM_EZI2C_BTLDR_COMM_ENABLED || \
                                                     SPIM_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SPIM_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void SPIM_I2CCyBtldrCommStart(void);
    void SPIM_I2CCyBtldrCommStop (void);
    void SPIM_I2CCyBtldrCommReset(void);
    cystatus SPIM_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SPIM_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (SPIM_SCB_MODE_I2C_CONST_CFG)
        #define SPIM_CyBtldrCommStart   SPIM_I2CCyBtldrCommStart
        #define SPIM_CyBtldrCommStop    SPIM_I2CCyBtldrCommStop
        #define SPIM_CyBtldrCommReset   SPIM_I2CCyBtldrCommReset
        #define SPIM_CyBtldrCommRead    SPIM_I2CCyBtldrCommRead
        #define SPIM_CyBtldrCommWrite   SPIM_I2CCyBtldrCommWrite
    #endif /* (SPIM_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SPIM_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SPIM_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void SPIM_EzI2CCyBtldrCommStart(void);
    void SPIM_EzI2CCyBtldrCommStop (void);
    void SPIM_EzI2CCyBtldrCommReset(void);
    cystatus SPIM_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SPIM_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (SPIM_SCB_MODE_EZI2C_CONST_CFG)
        #define SPIM_CyBtldrCommStart   SPIM_EzI2CCyBtldrCommStart
        #define SPIM_CyBtldrCommStop    SPIM_EzI2CCyBtldrCommStop
        #define SPIM_CyBtldrCommReset   SPIM_EzI2CCyBtldrCommReset
        #define SPIM_CyBtldrCommRead    SPIM_EzI2CCyBtldrCommRead
        #define SPIM_CyBtldrCommWrite   SPIM_EzI2CCyBtldrCommWrite
    #endif /* (SPIM_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SPIM_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SPIM_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void SPIM_SpiCyBtldrCommStart(void);
    void SPIM_SpiCyBtldrCommStop (void);
    void SPIM_SpiCyBtldrCommReset(void);
    cystatus SPIM_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SPIM_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (SPIM_SCB_MODE_SPI_CONST_CFG)
        #define SPIM_CyBtldrCommStart   SPIM_SpiCyBtldrCommStart
        #define SPIM_CyBtldrCommStop    SPIM_SpiCyBtldrCommStop
        #define SPIM_CyBtldrCommReset   SPIM_SpiCyBtldrCommReset
        #define SPIM_CyBtldrCommRead    SPIM_SpiCyBtldrCommRead
        #define SPIM_CyBtldrCommWrite   SPIM_SpiCyBtldrCommWrite
    #endif /* (SPIM_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SPIM_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SPIM_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void SPIM_UartCyBtldrCommStart(void);
    void SPIM_UartCyBtldrCommStop (void);
    void SPIM_UartCyBtldrCommReset(void);
    cystatus SPIM_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SPIM_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (SPIM_SCB_MODE_UART_CONST_CFG)
        #define SPIM_CyBtldrCommStart   SPIM_UartCyBtldrCommStart
        #define SPIM_CyBtldrCommStop    SPIM_UartCyBtldrCommStop
        #define SPIM_CyBtldrCommReset   SPIM_UartCyBtldrCommReset
        #define SPIM_CyBtldrCommRead    SPIM_UartCyBtldrCommRead
        #define SPIM_CyBtldrCommWrite   SPIM_UartCyBtldrCommWrite
    #endif /* (SPIM_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SPIM_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SPIM_BTLDR_COMM_ENABLED)
    #if (SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void SPIM_CyBtldrCommStart(void);
        void SPIM_CyBtldrCommStop (void);
        void SPIM_CyBtldrCommReset(void);
        cystatus SPIM_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus SPIM_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPIM)
        #define CyBtldrCommStart    SPIM_CyBtldrCommStart
        #define CyBtldrCommStop     SPIM_CyBtldrCommStop
        #define CyBtldrCommReset    SPIM_CyBtldrCommReset
        #define CyBtldrCommWrite    SPIM_CyBtldrCommWrite
        #define CyBtldrCommRead     SPIM_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPIM) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SPIM_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define SPIM_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define SPIM_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define SPIM_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define SPIM_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef SPIM_SPI_BYTE_TO_BYTE
    #define SPIM_SPI_BYTE_TO_BYTE   (22u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef SPIM_UART_BYTE_TO_BYTE
    #define SPIM_UART_BYTE_TO_BYTE  (2500u)
#endif /* SPIM_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_SPIM_H) */


/* [] END OF FILE */

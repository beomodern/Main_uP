/***************************************************************************//**
* \file SPIM_SPI_UART_PVT.h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_SPIM_H)
#define CY_SCB_SPI_UART_PVT_SPIM_H

#include "SPIM_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (SPIM_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  SPIM_rxBufferHead;
    extern volatile uint32  SPIM_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   SPIM_rxBufferOverflow;
    /** @} globals */
#endif /* (SPIM_INTERNAL_RX_SW_BUFFER_CONST) */

#if (SPIM_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  SPIM_txBufferHead;
    extern volatile uint32  SPIM_txBufferTail;
#endif /* (SPIM_INTERNAL_TX_SW_BUFFER_CONST) */

#if (SPIM_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 SPIM_rxBufferInternal[SPIM_INTERNAL_RX_BUFFER_SIZE];
#endif /* (SPIM_INTERNAL_RX_SW_BUFFER) */

#if (SPIM_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 SPIM_txBufferInternal[SPIM_TX_BUFFER_SIZE];
#endif /* (SPIM_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void SPIM_SpiPostEnable(void);
void SPIM_SpiStop(void);

#if (SPIM_SCB_MODE_SPI_CONST_CFG)
    void SPIM_SpiInit(void);
#endif /* (SPIM_SCB_MODE_SPI_CONST_CFG) */

#if (SPIM_SPI_WAKE_ENABLE_CONST)
    void SPIM_SpiSaveConfig(void);
    void SPIM_SpiRestoreConfig(void);
#endif /* (SPIM_SPI_WAKE_ENABLE_CONST) */

void SPIM_UartPostEnable(void);
void SPIM_UartStop(void);

#if (SPIM_SCB_MODE_UART_CONST_CFG)
    void SPIM_UartInit(void);
#endif /* (SPIM_SCB_MODE_UART_CONST_CFG) */

#if (SPIM_UART_WAKE_ENABLE_CONST)
    void SPIM_UartSaveConfig(void);
    void SPIM_UartRestoreConfig(void);
#endif /* (SPIM_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in SPIM_SetPins() */
#define SPIM_UART_RX_PIN_ENABLE    (SPIM_UART_RX)
#define SPIM_UART_TX_PIN_ENABLE    (SPIM_UART_TX)

/* UART RTS and CTS position to be used in  SPIM_SetPins() */
#define SPIM_UART_RTS_PIN_ENABLE    (0x10u)
#define SPIM_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define SPIM_SpiUartEnableIntRx(intSourceMask)  SPIM_SetRxInterruptMode(intSourceMask)
#define SPIM_SpiUartEnableIntTx(intSourceMask)  SPIM_SetTxInterruptMode(intSourceMask)
uint32  SPIM_SpiUartDisableIntRx(void);
uint32  SPIM_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_SPIM_H) */


/* [] END OF FILE */

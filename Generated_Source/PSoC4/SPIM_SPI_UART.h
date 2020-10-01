/***************************************************************************//**
* \file SPIM_SPI_UART.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_SPIM_H)
#define CY_SCB_SPI_UART_SPIM_H

#include "SPIM.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define SPIM_SPI_MODE                   (1u)
#define SPIM_SPI_SUB_MODE               (0u)
#define SPIM_SPI_CLOCK_MODE             (3u)
#define SPIM_SPI_OVS_FACTOR             (16u)
#define SPIM_SPI_MEDIAN_FILTER_ENABLE   (1u)
#define SPIM_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define SPIM_SPI_RX_DATA_BITS_NUM       (8u)
#define SPIM_SPI_TX_DATA_BITS_NUM       (8u)
#define SPIM_SPI_WAKE_ENABLE            (0u)
#define SPIM_SPI_BITS_ORDER             (1u)
#define SPIM_SPI_TRANSFER_SEPARATION    (1u)
#define SPIM_SPI_NUMBER_OF_SS_LINES     (2u)
#define SPIM_SPI_RX_BUFFER_SIZE         (30u)
#define SPIM_SPI_TX_BUFFER_SIZE         (8u)

#define SPIM_SPI_INTERRUPT_MODE         (1u)

#define SPIM_SPI_INTR_RX_MASK           (0x4u)
#define SPIM_SPI_INTR_TX_MASK           (0x0u)

#define SPIM_SPI_RX_TRIGGER_LEVEL       (7u)
#define SPIM_SPI_TX_TRIGGER_LEVEL       (0u)

#define SPIM_SPI_BYTE_MODE_ENABLE       (0u)
#define SPIM_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define SPIM_SPI_SS0_POLARITY           (0u)
#define SPIM_SPI_SS1_POLARITY           (0u)
#define SPIM_SPI_SS2_POLARITY           (0u)
#define SPIM_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define SPIM_UART_SUB_MODE              (0u)
#define SPIM_UART_DIRECTION             (3u)
#define SPIM_UART_DATA_BITS_NUM         (8u)
#define SPIM_UART_PARITY_TYPE           (2u)
#define SPIM_UART_STOP_BITS_NUM         (2u)
#define SPIM_UART_OVS_FACTOR            (12u)
#define SPIM_UART_IRDA_LOW_POWER        (0u)
#define SPIM_UART_MEDIAN_FILTER_ENABLE  (0u)
#define SPIM_UART_RETRY_ON_NACK         (0u)
#define SPIM_UART_IRDA_POLARITY         (0u)
#define SPIM_UART_DROP_ON_FRAME_ERR     (0u)
#define SPIM_UART_DROP_ON_PARITY_ERR    (0u)
#define SPIM_UART_WAKE_ENABLE           (0u)
#define SPIM_UART_RX_BUFFER_SIZE        (8u)
#define SPIM_UART_TX_BUFFER_SIZE        (8u)
#define SPIM_UART_MP_MODE_ENABLE        (0u)
#define SPIM_UART_MP_ACCEPT_ADDRESS     (0u)
#define SPIM_UART_MP_RX_ADDRESS         (0x2u)
#define SPIM_UART_MP_RX_ADDRESS_MASK    (0xFFu)

#define SPIM_UART_INTERRUPT_MODE        (0u)

#define SPIM_UART_INTR_RX_MASK          (0x0u)
#define SPIM_UART_INTR_TX_MASK          (0x0u)

#define SPIM_UART_RX_TRIGGER_LEVEL      (7u)
#define SPIM_UART_TX_TRIGGER_LEVEL      (0u)

#define SPIM_UART_BYTE_MODE_ENABLE      (0u)
#define SPIM_UART_CTS_ENABLE            (0u)
#define SPIM_UART_CTS_POLARITY          (0u)
#define SPIM_UART_RTS_ENABLE            (0u)
#define SPIM_UART_RTS_POLARITY          (0u)
#define SPIM_UART_RTS_FIFO_LEVEL        (4u)

#define SPIM_UART_RX_BREAK_WIDTH        (11u)

/* SPI mode enum */
#define SPIM_SPI_SLAVE  (0u)
#define SPIM_SPI_MASTER (1u)

/* UART direction enum */
#define SPIM_UART_RX    (1u)
#define SPIM_UART_TX    (2u)
#define SPIM_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define SPIM_SPI_SLAVE_CONST        (1u)
    #define SPIM_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define SPIM_RX_DIRECTION           (1u)
    #define SPIM_TX_DIRECTION           (1u)
    #define SPIM_UART_RX_DIRECTION      (1u)
    #define SPIM_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define SPIM_INTERNAL_RX_SW_BUFFER   (0u)
    #define SPIM_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define SPIM_INTERNAL_RX_BUFFER_SIZE    (SPIM_rxBufferSize + 1u)
    #define SPIM_RX_BUFFER_SIZE             (SPIM_rxBufferSize)
    #define SPIM_TX_BUFFER_SIZE             (SPIM_txBufferSize)

    /* Return true if buffer is provided */
    #define SPIM_CHECK_RX_SW_BUFFER (NULL != SPIM_rxBuffer)
    #define SPIM_CHECK_TX_SW_BUFFER (NULL != SPIM_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define SPIM_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define SPIM_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define SPIM_SPI_WAKE_ENABLE_CONST  (1u)
    #define SPIM_UART_WAKE_ENABLE_CONST (1u)
    #define SPIM_CHECK_SPI_WAKE_ENABLE  ((0u != SPIM_scbEnableWake) && SPIM_SCB_MODE_SPI_RUNTM_CFG)
    #define SPIM_CHECK_UART_WAKE_ENABLE ((0u != SPIM_scbEnableWake) && SPIM_SCB_MODE_UART_RUNTM_CFG)

    /* SPI/UART: TX or RX FIFO size */
    #if (SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1)
        #define SPIM_SPI_UART_FIFO_SIZE             (SPIM_FIFO_SIZE)
        #define SPIM_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define SPIM_SPI_UART_FIFO_SIZE (SPIM_GET_FIFO_SIZE(SPIM_CTRL_REG & \
                                                                                    SPIM_CTRL_BYTE_MODE))

        #define SPIM_CHECK_UART_RTS_CONTROL_FLOW \
                    ((SPIM_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != SPIM_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(SPIM_UART_FLOW_CTRL_REG)))
    #endif /* (SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (SPIM_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define SPIM_SPI_RX_DIRECTION (1u)
        #define SPIM_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #define SPIM_SPI_UART_FIFO_SIZE SPIM_GET_FIFO_SIZE(SPIM_SPI_BYTE_MODE_ENABLE)

        /* SPI internal RX and TX buffers */
        #define SPIM_INTERNAL_SPI_RX_SW_BUFFER  (SPIM_SPI_RX_BUFFER_SIZE > \
                                                                SPIM_SPI_UART_FIFO_SIZE)
        #define SPIM_INTERNAL_SPI_TX_SW_BUFFER  (SPIM_SPI_TX_BUFFER_SIZE > \
                                                                SPIM_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define SPIM_INTERNAL_RX_SW_BUFFER  (SPIM_INTERNAL_SPI_RX_SW_BUFFER)
        #define SPIM_INTERNAL_TX_SW_BUFFER  (SPIM_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define SPIM_INTERNAL_RX_BUFFER_SIZE    (SPIM_SPI_RX_BUFFER_SIZE + 1u)
        #define SPIM_RX_BUFFER_SIZE             (SPIM_SPI_RX_BUFFER_SIZE)
        #define SPIM_TX_BUFFER_SIZE             (SPIM_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define SPIM_SPI_WAKE_ENABLE_CONST  (0u != SPIM_SPI_WAKE_ENABLE)
        #define SPIM_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define SPIM_UART_RX_DIRECTION (0u != (SPIM_UART_DIRECTION & SPIM_UART_RX))
        #define SPIM_UART_TX_DIRECTION (0u != (SPIM_UART_DIRECTION & SPIM_UART_TX))

        /* Get FIFO size */
        #define SPIM_SPI_UART_FIFO_SIZE SPIM_GET_FIFO_SIZE(SPIM_UART_BYTE_MODE_ENABLE)

        /* UART internal RX and TX buffers */
        #define SPIM_INTERNAL_UART_RX_SW_BUFFER  (SPIM_UART_RX_BUFFER_SIZE > \
                                                                SPIM_SPI_UART_FIFO_SIZE)
        #define SPIM_INTERNAL_UART_TX_SW_BUFFER  (SPIM_UART_TX_BUFFER_SIZE > \
                                                                    SPIM_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define SPIM_INTERNAL_RX_SW_BUFFER  (SPIM_INTERNAL_UART_RX_SW_BUFFER)
        #define SPIM_INTERNAL_TX_SW_BUFFER  (SPIM_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define SPIM_INTERNAL_RX_BUFFER_SIZE    (SPIM_UART_RX_BUFFER_SIZE + 1u)
        #define SPIM_RX_BUFFER_SIZE             (SPIM_UART_RX_BUFFER_SIZE)
        #define SPIM_TX_BUFFER_SIZE             (SPIM_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define SPIM_SPI_WAKE_ENABLE_CONST  (0u)
        #define SPIM_UART_WAKE_ENABLE_CONST (0u != SPIM_UART_WAKE_ENABLE)

    #endif /* (SPIM_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define SPIM_SPI_SLAVE_CONST    (SPIM_SPI_MODE == SPIM_SPI_SLAVE)
    #define SPIM_SPI_MASTER_CONST   (SPIM_SPI_MODE == SPIM_SPI_MASTER)

    /* Direction */
    #define SPIM_RX_DIRECTION ((SPIM_SCB_MODE_SPI_CONST_CFG) ? \
                                            (SPIM_SPI_RX_DIRECTION) : (SPIM_UART_RX_DIRECTION))

    #define SPIM_TX_DIRECTION ((SPIM_SCB_MODE_SPI_CONST_CFG) ? \
                                            (SPIM_SPI_TX_DIRECTION) : (SPIM_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define SPIM_CHECK_RX_SW_BUFFER (SPIM_INTERNAL_RX_SW_BUFFER)
    #define SPIM_CHECK_TX_SW_BUFFER (SPIM_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define SPIM_INTERNAL_RX_SW_BUFFER_CONST    (SPIM_INTERNAL_RX_SW_BUFFER)
    #define SPIM_INTERNAL_TX_SW_BUFFER_CONST    (SPIM_INTERNAL_TX_SW_BUFFER)

    /* Wake up enable */
    #define SPIM_CHECK_SPI_WAKE_ENABLE  (SPIM_SPI_WAKE_ENABLE_CONST)
    #define SPIM_CHECK_UART_WAKE_ENABLE (SPIM_UART_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define SPIM_CHECK_UART_RTS_CONTROL_FLOW    (SPIM_SCB_MODE_UART_CONST_CFG && \
                                                             SPIM_UART_RTS_ENABLE)

#endif /* End (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/

/* SPIM_SPI_INIT_STRUCT */
typedef struct
{
    /** Mode of operation for SPI. The following defines are available choices:
     *  - SPIM_SPI_SLAVE
     *  - SPIM_SPI_MASTE
    */
    uint32 mode;

    /** Submode of operation for SPI. The following defines are available
     *  choices:
     *  - SPIM_SPI_MODE_MOTOROLA
     *  - SPIM_SPI_MODE_TI_COINCIDES
     *  - SPIM_SPI_MODE_TI_PRECEDES
     *  - SPIM_SPI_MODE_NATIONAL
    */
    uint32 submode;

    /** Determines the sclk relationship for Motorola submode. Ignored
     *  for other submodes. The following defines are available choices:
     *  - SPIM_SPI_SCLK_CPHA0_CPOL0
     *  - SPIM_SPI_SCLK_CPHA0_CPOL1
     *  - SPIM_SPI_SCLK_CPHA1_CPOL0
     *  - SPIM_SPI_SCLK_CPHA1_CPOL1
    */
    uint32 sclkMode;

    /** Oversampling factor for the SPI clock. Ignored for Slave mode operation.
    */
    uint32 oversample;

    /** Applies median filter on the input lines: 0 – not applied, 1 – applied.
    */
    uint32 enableMedianFilter;

    /** Applies late sampling of MISO line: 0 – not applied, 1 – applied.
     *  Ignored for slave mode.
    */
    uint32 enableLateSampling;

    /** Enables wakeup from low power mode: 0 – disable, 1 – enable.
     *  Ignored for master mode.
    */
    uint32 enableWake;

    /** Number of data bits for RX direction.
     *  Different dataBitsRx and dataBitsTx are only allowed for National
     *  submode.
    */
    uint32 rxDataBits;

    /** Number of data bits for TX direction.
     *  Different dataBitsRx and dataBitsTx are only allowed for National
     *  submode.
    */
    uint32 txDataBits;

    /** Determines the bit ordering. The following defines are available
     *  choices:
     *  - SPIM_BITS_ORDER_LSB_FIRST
     *  - SPIM_BITS_ORDER_MSB_FIRST
    */
    uint32 bitOrder;

    /** Determines whether transfers are back to back or have SS disabled
     *  between words. Ignored for slave mode. The following defines are
     *  available choices:
     *  - SPIM_SPI_TRANSFER_CONTINUOUS
     *  - SPIM_SPI_TRANSFER_SEPARATED
    */
    uint32 transferSeperation;

    /** Size of the RX buffer in bytes/words (depends on rxDataBits parameter).
     *  A value equal to the RX FIFO depth implies the usage of buffering in
     *  hardware. A value greater than the RX FIFO depth results in a software
     *  buffer.
     *  The SPIM_INTR _RX_NOT_EMPTY interrupt has to be enabled to
     *  transfer data into the software buffer.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words for PSoC 4100 /
     *    PSoC 4200 devices.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words or 16
     *    bytes (Byte mode is enabled) for PSoC 4100 BLE / PSoC 4200 BLE /
     *    PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *    PSoC Analog Coprocessor devices.
    */
    uint32 rxBufferSize;

    /** Buffer space provided for a RX software buffer:
     *  - A NULL pointer must be provided to use hardware buffering.
     *  - A pointer to an allocated buffer must be provided to use software
     *    buffering. The buffer size must equal (rxBufferSize + 1) in bytes if
     *    dataBitsRx is less or equal to 8, otherwise (2 * (rxBufferSize + 1))
     *    in bytes. The software RX buffer always keeps one element empty.
     *    For correct operation the allocated RX buffer has to be one element
     *    greater than maximum packet size expected to be received.
    */
    uint8* rxBuffer;

    /** Size of the TX buffer in bytes/words(depends on txDataBits parameter).
     *  A value equal to the TX FIFO depth implies the usage of buffering in
     *  hardware. A value greater than the TX FIFO depth results in a software
     *  buffer.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words for PSoC 4100 /
     *    PSoC 4200 devices.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words or 16
     *    bytes (Byte mode is enabled) for PSoC 4100 BLE / PSoC 4200 BLE /
     *    PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *    PSoC Analog Coprocessor devices.
    */
    uint32 txBufferSize;

    /** Buffer space provided for a TX software buffer:
     *  - A NULL pointer must be provided to use hardware buffering.
     *  - A pointer to an allocated buffer must be provided to use software
     *    buffering. The buffer size must equal txBufferSize if dataBitsTx is
     *    less or equal to 8, otherwise (2* txBufferSize).
    */
    uint8* txBuffer;

    /** Enables component interrupt: 0 – disable, 1 – enable.
     *  The interrupt has to be enabled if software buffer is used.
    */
    uint32 enableInterrupt;

    /** Mask of enabled interrupt sources for the RX direction. This mask is
     *  written regardless of the setting of the enable Interrupt field.
     *  Multiple sources are enabled by providing a value that is the OR of
     *  all of the following sources to enable:
     *  - SPIM_INTR_RX_FIFO_LEVEL
     *  - SPIM_INTR_RX_NOT_EMPTY
     *  - SPIM_INTR_RX_FULL
     *  - SPIM_INTR_RX_OVERFLOW
     *  - SPIM_INTR_RX_UNDERFLOW
     *  - SPIM_INTR_SLAVE_SPI_BUS_ERROR
    */
    uint32 rxInterruptMask;

    /** FIFO level for an RX FIFO level interrupt. This value is written
     *  regardless of whether the RX FIFO level interrupt source is enabled.
    */
    uint32 rxTriggerLevel;

    /** Mask of enabled interrupt sources for the TX direction. This mask is
     *  written regardless of the setting of the enable Interrupt field.
     *  Multiple sources are enabled by providing a value that is the OR of
     *  all of the following sources to enable:
     *  - SPIM_INTR_TX_FIFO_LEVEL
     *  - SPIM_INTR_TX_NOT_FULL
     *  - SPIM_INTR_TX_EMPTY
     *  - SPIM_INTR_TX_OVERFLOW
     *  - SPIM_INTR_TX_UNDERFLOW
     *  - SPIM_INTR_MASTER_SPI_DONE
    */
    uint32 txInterruptMask;

    /** FIFO level for a TX FIFO level interrupt. This value is written
     * regardless of whether the TX FIFO level interrupt source is enabled.
    */
    uint32 txTriggerLevel;

    /** When enabled the TX and RX FIFO depth is doubled and equal to
     *  16 bytes: 0 – disable, 1 – enable. This implies that number of
     *  TX and RX data bits must be less than or equal to 8.
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *  PSoC Analog Coprocessor.
    */
    uint8 enableByteMode;

    /** Enables continuous SCLK generation by the SPI master: 0 – disable,
     *  1 – enable.
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *  PSoC Analog Coprocessor.
    */
    uint8 enableFreeRunSclk;

    /** Active polarity of slave select lines 0-3. This is bit mask where bit
     *  SPIM_SPI_SLAVE_SELECT0 corresponds to slave select 0
     *  polarity, bit SPIM_SPI_SLAVE_SELECT1 – slave select 1
     *  polarity and so on. Polarity constants are:
     *  - SPIM_SPI_SS_ACTIVE_LOW
     *  - SPIM_SPI_SS_ACTIVE_HIGH
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *  PSoC Analog Coprocessor.
    */
    uint8 polaritySs;
} SPIM_SPI_INIT_STRUCT;


/* SPIM_UART_INIT_STRUCT */
typedef struct
{
    /** Mode of operation for the UART. The following defines are available
     *  choices:
     *  - SPIM_UART_MODE_STD
     *  - SPIM_UART_MODE_SMARTCARD
     *  - SPIM_UART_MODE_IRDA
    */
    uint32 mode;

    /** Direction of operation for the UART. The following defines are available
     *  choices:
     *  - SPIM_UART_TX_RX
     *  - SPIM_UART_RX
     *  - SPIM_UART_TX
    */
    uint32 direction;

    /** Number of data bits.
    */
    uint32 dataBits;

    /** Determines the parity. The following defines are available choices:
     *  - SPIM_UART_PARITY_EVEN
     *  - SPIM_UART_PARITY_ODD
     *  - SPIM_UART_PARITY_NONE
    */
    uint32 parity;

    /** Determines the number of stop bits. The following defines are available
     *  choices:
     *  - SPIM_UART_STOP_BITS_1
     *  - SPIM_UART_STOP_BITS_1_5
     *  - SPIM_UART_STOP_BITS_2
    */
    uint32 stopBits;

    /** Oversampling factor for the UART.
     *
     *  Note The oversampling factor values are changed when enableIrdaLowPower
     *  is enabled:
     *  - SPIM_UART_IRDA_LP_OVS16
     *  - SPIM_UART_IRDA_LP_OVS32
     *  - SPIM_UART_IRDA_LP_OVS48
     *  - SPIM_UART_IRDA_LP_OVS96
     *  - SPIM_UART_IRDA_LP_OVS192
     *  - SPIM_UART_IRDA_LP_OVS768
     *  - SPIM_UART_IRDA_LP_OVS1536
    */
    uint32 oversample;

    /** Enables IrDA low power RX mode operation: 0 – disable, 1 – enable.
     *  The TX functionality does not work when enabled.
    */
    uint32 enableIrdaLowPower;

    /** Applies median filter on the input lines:  0 – not applied, 1 – applied.
    */
    uint32 enableMedianFilter;

    /** Enables retry when NACK response was received: 0 – disable, 1 – enable.
     *  Only current content of TX FIFO is re-sent.
     *  Ignored for modes other than SmartCard.
    */
    uint32 enableRetryNack;

    /** Inverts polarity of RX line: 0 – non-inverting, 1 – inverting.
     *  Ignored for modes other than IrDA.
    */
    uint32 enableInvertedRx;

    /** Drop data from RX FIFO if parity error is detected: 0 – disable,
     *  1 – enable.
    */
    uint32 dropOnParityErr;

    /** Drop data from RX FIFO if a frame error is detected: 0 – disable,
     *  1 – enable.
    */
    uint32 dropOnFrameErr;

    /** Enables wakeup from low power mode: 0 – disable, 1 – enable.
     *  Ignored for modes other than standard UART. The RX functionality
     *  has to be enabled.
    */
    uint32 enableWake;

    /** Size of the RX buffer in bytes/words (depends on rxDataBits parameter).
     *  A value equal to the RX FIFO depth implies the usage of buffering in
     *  hardware. A value greater than the RX FIFO depth results in a software
     *  buffer.
     *  The SPIM_INTR _RX_NOT_EMPTY interrupt has to be enabled to
     *  transfer data into the software buffer.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words for PSoC 4100 /
     *    PSoC 4200 devices.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words or 16
     *    bytes (Byte mode is enabled) for PSoC 4100 BLE / PSoC 4200 BLE /
     *    PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *    PSoC Analog Coprocessor devices.
    */
    uint32 rxBufferSize;

    /** Buffer space provided for a RX software buffer:
     *  - A NULL pointer must be provided to use hardware buffering.
     *  - A pointer to an allocated buffer must be provided to use software
     *    buffering. The buffer size must equal (rxBufferSize + 1) in bytes if
     *    dataBitsRx is less or equal to 8, otherwise (2 * (rxBufferSize + 1))
     *    in bytes. The software RX buffer always keeps one element empty.
     *    For correct operation the allocated RX buffer has to be one element
     *    greater than maximum packet size expected to be received.
    */
    uint8* rxBuffer;

    /** Size of the TX buffer in bytes/words(depends on txDataBits parameter).
     *  A value equal to the TX FIFO depth implies the usage of buffering in
     *  hardware. A value greater than the TX FIFO depth results in a software
     *  buffer.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words for PSoC 4100 /
     *    PSoC 4200 devices.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words or 16
     *    bytes (Byte mode is enabled) for PSoC 4100 BLE / PSoC 4200 BLE /
     *    PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *    PSoC Analog Coprocessor devices.
    */
    uint32 txBufferSize;

    /** Buffer space provided for a TX software buffer:
     *  - A NULL pointer must be provided to use hardware buffering.
     *  - A pointer to an allocated buffer must be provided to use software
     *    buffering. The buffer size must equal txBufferSize if dataBitsTx is
     *    less or equal to 8, otherwise (2* txBufferSize).
    */
    uint8* txBuffer;

    /** Enables multiprocessor mode: 0 – disable, 1 – enable.
    */
    uint32 enableMultiproc;

    /** Enables matched address to be accepted: 0 – disable, 1 – enable.
    */
    uint32 multiprocAcceptAddr;

    /** 8 bit address to match in Multiprocessor mode. Ignored for other modes.
    */
    uint32 multiprocAddr;

    /** 8 bit mask of address bits that are compared for a Multiprocessor
     *  address match. Ignored for other modes.
     *  - Bit value 0 – excludes bit from address comparison.
     *  - Bit value 1 – the bit needs to match with the corresponding bit
     *   of the device address.
    */
    uint32 multiprocAddrMask;

    /** Enables component interrupt: 0 – disable, 1 – enable.
     *  The interrupt has to be enabled if software buffer is used.
    */
    uint32 enableInterrupt;

    /** Mask of interrupt sources to enable in the RX direction. This mask is
     *  written regardless of the setting of the enableInterrupt field.
     *  Multiple sources are enabled by providing a value that is the OR of
     *  all of the following sources to enable:
     *  - SPIM_INTR_RX_FIFO_LEVEL
     *  - SPIM_INTR_RX_NOT_EMPTY
     *  - SPIM_INTR_RX_FULL
     *  - SPIM_INTR_RX_OVERFLOW
     *  - SPIM_INTR_RX_UNDERFLOW
     *  - SPIM_INTR_RX_FRAME_ERROR
     *  - SPIM_INTR_RX_PARITY_ERROR
    */
    uint32 rxInterruptMask;

    /** FIFO level for an RX FIFO level interrupt. This value is written
     *  regardless of whether the RX FIFO level interrupt source is enabled.
    */
    uint32 rxTriggerLevel;

    /** Mask of interrupt sources to enable in the TX direction. This mask is
     *  written regardless of the setting of the enableInterrupt field.
     *  Multiple sources are enabled by providing a value that is the OR of
     *  all of the following sources to enable:
     *  - SPIM_INTR_TX_FIFO_LEVEL
     *  - SPIM_INTR_TX_NOT_FULL
     *  - SPIM_INTR_TX_EMPTY
     *  - SPIM_INTR_TX_OVERFLOW
     *  - SPIM_INTR_TX_UNDERFLOW
     *  - SPIM_INTR_TX_UART_DONE
     *  - SPIM_INTR_TX_UART_NACK
     *  - SPIM_INTR_TX_UART_ARB_LOST
    */
    uint32 txInterruptMask;

    /** FIFO level for a TX FIFO level interrupt. This value is written
     *  regardless of whether the TX FIFO level interrupt source is enabled.
    */
    uint32 txTriggerLevel;

    /** When enabled the TX and RX FIFO depth is doubled and equal to
     *  16 bytes: 0 – disable, 1 – enable. This implies that number of
     *  Data bits must be less than or equal to 8.
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *  PSoC Analog Coprocessor.
    */
    uint8 enableByteMode;

    /** Enables usage of CTS input signal by the UART transmitter : 0 – disable,
     *  1 – enable.
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *  PSoC Analog Coprocessor.
    */
    uint8 enableCts;

    /** Sets active polarity of CTS input signal:
     *  - SPIM_UART_CTS_ACTIVE_LOW
     *  - SPIM_UART_CTS_ACTIVE_HIGH
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *  PSoC Analog Coprocessor.
    */
    uint8 ctsPolarity;

    /** RX FIFO level for RTS signal activation. While the RX FIFO has fewer
     *  entries than the RTS FIFO level value the RTS signal remains active,
     *  otherwise the RTS signal becomes inactive. By setting this field to 0,
     *  RTS signal activation is disabled.
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *  PSoC Analog Coprocessor.
    */
    uint8 rtsRxFifoLevel;

    /** Sets active polarity of RTS output signal:
     *  - SPIM_UART_RTS_ ACTIVE_LOW
     *  - SPIM_UART_RTS_ACTIVE_HIGH
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *  PSoC Analog Coprocessor.
    */
    uint8 rtsPolarity;

    /** Configures the width of a break signal in that triggers the break
     *  detection interrupt source. A Break is a low level on the RX line.
     *  Valid range is 1-16 UART bits times.
    */
    uint8 breakWidth;
} SPIM_UART_INIT_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes
***************************************/

/**
* \addtogroup group_spi
* @{
*/
/* SPI specific functions */
#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    void SPIM_SpiInit(const SPIM_SPI_INIT_STRUCT *config);
#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */


#if(SPIM_SCB_MODE_SPI_INC)
    /*******************************************************************************
    * Function Name: SPIM_SpiIsBusBusy
    ****************************************************************************//**
    *
    *  Returns the current status on the bus. The bus status is determined using
    *  the slave select signal.
    *  - Motorola and National Semiconductor sub-modes: The bus is busy after
    *    the slave select line is activated and lasts until the slave select line
    *    is deactivated.
    *  - Texas Instrument sub-modes: The bus is busy at the moment of the initial
    *    pulse on the slave select line and lasts until the transfer is complete.
    *    If SPI Master is configured to use "Separated transfers"
    *    (see Continuous versus Separated Transfer Separation), the bus is busy
    *    during each element transfer and is free between each element transfer.
    *    The Master does not activate SS line immediately after data has been
    *    written into the TX FIFO.
    *
    *  \return slaveSelect: Current status on the bus.
    *   If the returned value is nonzero, the bus is busy.
    *   If zero is returned, the bus is free. The bus status is determined using
    *   the slave select signal.
    *
    *******************************************************************************/
    #define SPIM_SpiIsBusBusy() ((uint32) (0u != (SPIM_SPI_STATUS_REG & \
                                                              SPIM_SPI_STATUS_BUS_BUSY)))

    #if (SPIM_SPI_MASTER_CONST)
        void SPIM_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(SPIM_SPI_MASTER_CONST) */

    #if !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1)
        void SPIM_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1) */
#endif /* (SPIM_SCB_MODE_SPI_INC) */
/** @} spi */

/**
* \addtogroup group_uart
* @{
*/
/* UART specific functions */
#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    void SPIM_UartInit(const SPIM_UART_INIT_STRUCT *config);
#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(SPIM_SCB_MODE_UART_INC)
    void SPIM_UartSetRxAddress(uint32 address);
    void SPIM_UartSetRxAddressMask(uint32 addressMask);


    /* UART RX direction APIs */
    #if(SPIM_UART_RX_DIRECTION)
        uint32 SPIM_UartGetChar(void);
        uint32 SPIM_UartGetByte(void);

        #if !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void SPIM_UartSetRtsPolarity(uint32 polarity);
            void SPIM_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1) */
    #endif /* (SPIM_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(SPIM_UART_TX_DIRECTION)
        /*******************************************************************************
        * Function Name: SPIM_UartPutChar
        ****************************************************************************//**
        *
        *  Places a byte of data in the transmit buffer to be sent at the next available
        *  bus time. This function is blocking and waits until there is a space
        *  available to put requested data in the transmit buffer.
        *  For UART Multi Processor mode this function can send 9-bits data as well.
        *  Use SPIM_UART_MP_MARK to add a mark to create an address byte.
        *
        *  \param txDataByte: the data to be transmitted.
        *
        *******************************************************************************/
        #define SPIM_UartPutChar(ch)    SPIM_SpiUartWriteTxData((uint32)(ch))

        void SPIM_UartPutString(const char8 string[]);
        void SPIM_UartPutCRLF(uint32 txDataByte);
        void SPIM_UartSendBreakBlocking(uint32 breakWidth);

        #if !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void SPIM_UartEnableCts(void);
            void SPIM_UartDisableCts(void);
            void SPIM_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1) */
    #endif /* (SPIM_UART_TX_DIRECTION) */
#endif /* (SPIM_SCB_MODE_UART_INC) */
/** @} uart */

/**
* \addtogroup group_spi_uart
* @{
*/
#if(SPIM_RX_DIRECTION)
    uint32 SPIM_SpiUartReadRxData(void);
    uint32 SPIM_SpiUartGetRxBufferSize(void);
    void   SPIM_SpiUartClearRxBuffer(void);
#endif /* (SPIM_RX_DIRECTION) */

/* Common APIs TX direction */
#if(SPIM_TX_DIRECTION)
    void   SPIM_SpiUartWriteTxData(uint32 txData);
    void   SPIM_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 SPIM_SpiUartGetTxBufferSize(void);
    void   SPIM_SpiUartClearTxBuffer(void);
#endif /* (SPIM_TX_DIRECTION) */
/** @} spi_uart */

CY_ISR_PROTO(SPIM_SPI_UART_ISR);

#if(SPIM_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(SPIM_UART_WAKEUP_ISR);
#endif /* (SPIM_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   SPIM_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 SPIM_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   SPIM_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 SPIM_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(SPIM_INTERNAL_RX_SW_BUFFER_CONST)
        #define SPIM_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    SPIM_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define SPIM_GetWordFromRxBuffer(idx) SPIM_rxBufferInternal[(idx)]

    #endif /* (SPIM_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(SPIM_INTERNAL_TX_SW_BUFFER_CONST)
        #define SPIM_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        SPIM_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define SPIM_GetWordFromTxBuffer(idx) SPIM_txBufferInternal[(idx)]

    #endif /* (SPIM_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (SPIM_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define SPIM_SPI_MODE_MOTOROLA      (0x00u)
#define SPIM_SPI_MODE_TI_COINCIDES  (0x01u)
#define SPIM_SPI_MODE_TI_PRECEDES   (0x11u)
#define SPIM_SPI_MODE_NATIONAL      (0x02u)
#define SPIM_SPI_MODE_MASK          (0x03u)
#define SPIM_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define SPIM_SPI_MODE_NS_MICROWIRE  (SPIM_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define SPIM_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define SPIM_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define SPIM_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define SPIM_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define SPIM_BITS_ORDER_LSB_FIRST   (0u)
#define SPIM_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define SPIM_SPI_TRANSFER_SEPARATED     (0u)
#define SPIM_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define SPIM_SPI_SLAVE_SELECT0    (SPIM_SCB__SS0_POSISTION)
#define SPIM_SPI_SLAVE_SELECT1    (SPIM_SCB__SS1_POSISTION)
#define SPIM_SPI_SLAVE_SELECT2    (SPIM_SCB__SS2_POSISTION)
#define SPIM_SPI_SLAVE_SELECT3    (SPIM_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define SPIM_SPI_SS_ACTIVE_LOW  (0u)
#define SPIM_SPI_SS_ACTIVE_HIGH (1u)

#define SPIM_INTR_SPIM_TX_RESTORE   (SPIM_INTR_TX_OVERFLOW)

#define SPIM_INTR_SPIS_TX_RESTORE     (SPIM_INTR_TX_OVERFLOW | \
                                                 SPIM_INTR_TX_UNDERFLOW)

/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define SPIM_UART_MODE_STD          (0u)
#define SPIM_UART_MODE_SMARTCARD    (1u)
#define SPIM_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define SPIM_UART_RX    (1u)
#define SPIM_UART_TX    (2u)
#define SPIM_UART_TX_RX (3u)

/* UART parity enum */
#define SPIM_UART_PARITY_EVEN   (0u)
#define SPIM_UART_PARITY_ODD    (1u)
#define SPIM_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define SPIM_UART_STOP_BITS_1   (2u)
#define SPIM_UART_STOP_BITS_1_5 (3u)
#define SPIM_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define SPIM_UART_IRDA_LP_OVS16     (16u)
#define SPIM_UART_IRDA_LP_OVS32     (32u)
#define SPIM_UART_IRDA_LP_OVS48     (48u)
#define SPIM_UART_IRDA_LP_OVS96     (96u)
#define SPIM_UART_IRDA_LP_OVS192    (192u)
#define SPIM_UART_IRDA_LP_OVS768    (768u)
#define SPIM_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define SPIM_UART_MP_MARK       (0x100u)
#define SPIM_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define SPIM_UART_CTS_ACTIVE_LOW    (0u)
#define SPIM_UART_CTS_ACTIVE_HIGH   (1u)
#define SPIM_UART_RTS_ACTIVE_LOW    (0u)
#define SPIM_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define SPIM_INTR_RX_ERR        (SPIM_INTR_RX_OVERFLOW    | \
                                             SPIM_INTR_RX_UNDERFLOW   | \
                                             SPIM_INTR_RX_FRAME_ERROR | \
                                             SPIM_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for SPIM_UartGetByte() */
#define SPIM_UART_RX_OVERFLOW       (SPIM_INTR_RX_OVERFLOW << 8u)
#define SPIM_UART_RX_UNDERFLOW      (SPIM_INTR_RX_UNDERFLOW << 8u)
#define SPIM_UART_RX_FRAME_ERROR    (SPIM_INTR_RX_FRAME_ERROR << 8u)
#define SPIM_UART_RX_PARITY_ERROR   (SPIM_INTR_RX_PARITY_ERROR << 8u)
#define SPIM_UART_RX_ERROR_MASK     (SPIM_UART_RX_OVERFLOW    | \
                                                 SPIM_UART_RX_UNDERFLOW   | \
                                                 SPIM_UART_RX_FRAME_ERROR | \
                                                 SPIM_UART_RX_PARITY_ERROR)

#define SPIM_INTR_UART_TX_RESTORE   (SPIM_INTR_TX_OVERFLOW  | \
                                                 SPIM_INTR_TX_UART_NACK | \
                                                 SPIM_INTR_TX_UART_DONE | \
                                                 SPIM_INTR_TX_UART_ARB_LOST)


/***************************************
*     Vars with External Linkage
***************************************/

#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const SPIM_SPI_INIT_STRUCT  SPIM_configSpi;
    extern const SPIM_UART_INIT_STRUCT SPIM_configUart;
#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (SPIM_UART_WAKE_ENABLE_CONST && SPIM_UART_RX_WAKEUP_IRQ)
    extern uint8 SPIM_skipStart;
#endif /* (SPIM_UART_WAKE_ENABLE_CONST && SPIM_UART_RX_WAKEUP_IRQ) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define SPIM_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & SPIM_INTR_SLAVE_SPI_BUS_ERROR)
#define SPIM_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & SPIM_INTR_MASTER_SPI_DONE)
#define SPIM_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~SPIM_INTR_SLAVE_SPI_BUS_ERROR)

#define SPIM_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~SPIM_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define SPIM_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((SPIM_UART_IRDA_LP_OVS16   == (oversample)) ? SPIM_CTRL_OVS_IRDA_LP_OVS16 : \
         ((SPIM_UART_IRDA_LP_OVS32   == (oversample)) ? SPIM_CTRL_OVS_IRDA_LP_OVS32 : \
          ((SPIM_UART_IRDA_LP_OVS48   == (oversample)) ? SPIM_CTRL_OVS_IRDA_LP_OVS48 : \
           ((SPIM_UART_IRDA_LP_OVS96   == (oversample)) ? SPIM_CTRL_OVS_IRDA_LP_OVS96 : \
            ((SPIM_UART_IRDA_LP_OVS192  == (oversample)) ? SPIM_CTRL_OVS_IRDA_LP_OVS192 : \
             ((SPIM_UART_IRDA_LP_OVS768  == (oversample)) ? SPIM_CTRL_OVS_IRDA_LP_OVS768 : \
              ((SPIM_UART_IRDA_LP_OVS1536 == (oversample)) ? SPIM_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          SPIM_CTRL_OVS_IRDA_LP_OVS16)))))))

#define SPIM_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (SPIM_UART_RX & (direction))) ? \
                                                                     (SPIM_RX_CTRL_ENABLED) : (0u))

#define SPIM_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (SPIM_UART_TX & (direction))) ? \
                                                                     (SPIM_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define SPIM_CTRL_SPI      (SPIM_CTRL_MODE_SPI)
#define SPIM_SPI_RX_CTRL   (SPIM_RX_CTRL_ENABLED)
#define SPIM_SPI_TX_CTRL   (SPIM_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define SPIM_SPI_SS_POLARITY \
             (((uint32) SPIM_SPI_SS0_POLARITY << SPIM_SPI_SLAVE_SELECT0) | \
              ((uint32) SPIM_SPI_SS1_POLARITY << SPIM_SPI_SLAVE_SELECT1) | \
              ((uint32) SPIM_SPI_SS2_POLARITY << SPIM_SPI_SLAVE_SELECT2) | \
              ((uint32) SPIM_SPI_SS3_POLARITY << SPIM_SPI_SLAVE_SELECT3))

#if(SPIM_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define SPIM_SPI_DEFAULT_CTRL \
                    (SPIM_GET_CTRL_OVS(SPIM_SPI_OVS_FACTOR) | \
                     SPIM_GET_CTRL_BYTE_MODE (SPIM_SPI_BYTE_MODE_ENABLE) | \
                     SPIM_GET_CTRL_EC_AM_MODE(SPIM_SPI_WAKE_ENABLE)      | \
                     SPIM_CTRL_SPI)

    #define SPIM_SPI_DEFAULT_SPI_CTRL \
                    (SPIM_GET_SPI_CTRL_CONTINUOUS    (SPIM_SPI_TRANSFER_SEPARATION)       | \
                     SPIM_GET_SPI_CTRL_SELECT_PRECEDE(SPIM_SPI_SUB_MODE &                   \
                                                                  SPIM_SPI_MODE_TI_PRECEDES_MASK)     | \
                     SPIM_GET_SPI_CTRL_SCLK_MODE     (SPIM_SPI_CLOCK_MODE)                | \
                     SPIM_GET_SPI_CTRL_LATE_MISO_SAMPLE(SPIM_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     SPIM_GET_SPI_CTRL_SCLK_CONTINUOUS(SPIM_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     SPIM_GET_SPI_CTRL_SSEL_POLARITY (SPIM_SPI_SS_POLARITY)               | \
                     SPIM_GET_SPI_CTRL_SUB_MODE      (SPIM_SPI_SUB_MODE)                  | \
                     SPIM_GET_SPI_CTRL_MASTER_MODE   (SPIM_SPI_MODE))

    /* RX direction */
    #define SPIM_SPI_DEFAULT_RX_CTRL \
                    (SPIM_GET_RX_CTRL_DATA_WIDTH(SPIM_SPI_RX_DATA_BITS_NUM)     | \
                     SPIM_GET_RX_CTRL_BIT_ORDER (SPIM_SPI_BITS_ORDER)           | \
                     SPIM_GET_RX_CTRL_MEDIAN    (SPIM_SPI_MEDIAN_FILTER_ENABLE) | \
                     SPIM_SPI_RX_CTRL)

    #define SPIM_SPI_DEFAULT_RX_FIFO_CTRL \
                    SPIM_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(SPIM_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define SPIM_SPI_DEFAULT_TX_CTRL \
                    (SPIM_GET_TX_CTRL_DATA_WIDTH(SPIM_SPI_TX_DATA_BITS_NUM) | \
                     SPIM_GET_TX_CTRL_BIT_ORDER (SPIM_SPI_BITS_ORDER)       | \
                     SPIM_SPI_TX_CTRL)

    #define SPIM_SPI_DEFAULT_TX_FIFO_CTRL \
                    SPIM_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(SPIM_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define SPIM_SPI_DEFAULT_INTR_SPI_EC_MASK   (SPIM_NO_INTR_SOURCES)

    #define SPIM_SPI_DEFAULT_INTR_I2C_EC_MASK   (SPIM_NO_INTR_SOURCES)
    #define SPIM_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (SPIM_SPI_INTR_RX_MASK & SPIM_INTR_SLAVE_SPI_BUS_ERROR)

    #define SPIM_SPI_DEFAULT_INTR_MASTER_MASK \
                    (SPIM_SPI_INTR_TX_MASK & SPIM_INTR_MASTER_SPI_DONE)

    #define SPIM_SPI_DEFAULT_INTR_RX_MASK \
                    (SPIM_SPI_INTR_RX_MASK & (uint32) ~SPIM_INTR_SLAVE_SPI_BUS_ERROR)

    #define SPIM_SPI_DEFAULT_INTR_TX_MASK \
                    (SPIM_SPI_INTR_TX_MASK & (uint32) ~SPIM_INTR_MASTER_SPI_DONE)

#endif /* (SPIM_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define SPIM_CTRL_UART      (SPIM_CTRL_MODE_UART)
#define SPIM_UART_RX_CTRL   (SPIM_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define SPIM_UART_TX_CTRL   (SPIM_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(SPIM_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(SPIM_UART_MODE_IRDA == SPIM_UART_SUB_MODE)

        #define SPIM_DEFAULT_CTRL_OVS   ((0u != SPIM_UART_IRDA_LOW_POWER) ?              \
                                (SPIM_UART_GET_CTRL_OVS_IRDA_LP(SPIM_UART_OVS_FACTOR)) : \
                                (SPIM_CTRL_OVS_IRDA_OVS16))

    #else

        #define SPIM_DEFAULT_CTRL_OVS   SPIM_GET_CTRL_OVS(SPIM_UART_OVS_FACTOR)

    #endif /* (SPIM_UART_MODE_IRDA == SPIM_UART_SUB_MODE) */

    #define SPIM_UART_DEFAULT_CTRL \
                                (SPIM_GET_CTRL_BYTE_MODE  (SPIM_UART_BYTE_MODE_ENABLE)  | \
                                 SPIM_GET_CTRL_ADDR_ACCEPT(SPIM_UART_MP_ACCEPT_ADDRESS) | \
                                 SPIM_DEFAULT_CTRL_OVS                                              | \
                                 SPIM_CTRL_UART)

    #define SPIM_UART_DEFAULT_UART_CTRL \
                                    (SPIM_GET_UART_CTRL_MODE(SPIM_UART_SUB_MODE))

    /* RX direction */
    #define SPIM_UART_DEFAULT_RX_CTRL_PARITY \
                                ((SPIM_UART_PARITY_NONE != SPIM_UART_PARITY_TYPE) ?      \
                                  (SPIM_GET_UART_RX_CTRL_PARITY(SPIM_UART_PARITY_TYPE) | \
                                   SPIM_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define SPIM_UART_DEFAULT_UART_RX_CTRL \
                    (SPIM_GET_UART_RX_CTRL_MODE(SPIM_UART_STOP_BITS_NUM)                    | \
                     SPIM_GET_UART_RX_CTRL_POLARITY(SPIM_UART_IRDA_POLARITY)                | \
                     SPIM_GET_UART_RX_CTRL_MP_MODE(SPIM_UART_MP_MODE_ENABLE)                | \
                     SPIM_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(SPIM_UART_DROP_ON_PARITY_ERR) | \
                     SPIM_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(SPIM_UART_DROP_ON_FRAME_ERR)   | \
                     SPIM_GET_UART_RX_CTRL_BREAK_WIDTH(SPIM_UART_RX_BREAK_WIDTH)            | \
                     SPIM_UART_DEFAULT_RX_CTRL_PARITY)


    #define SPIM_UART_DEFAULT_RX_CTRL \
                                (SPIM_GET_RX_CTRL_DATA_WIDTH(SPIM_UART_DATA_BITS_NUM)        | \
                                 SPIM_GET_RX_CTRL_MEDIAN    (SPIM_UART_MEDIAN_FILTER_ENABLE) | \
                                 SPIM_GET_UART_RX_CTRL_ENABLED(SPIM_UART_DIRECTION))

    #define SPIM_UART_DEFAULT_RX_FIFO_CTRL \
                                SPIM_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(SPIM_UART_RX_TRIGGER_LEVEL)

    #define SPIM_UART_DEFAULT_RX_MATCH_REG  ((0u != SPIM_UART_MP_MODE_ENABLE) ?          \
                                (SPIM_GET_RX_MATCH_ADDR(SPIM_UART_MP_RX_ADDRESS) | \
                                 SPIM_GET_RX_MATCH_MASK(SPIM_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define SPIM_UART_DEFAULT_TX_CTRL_PARITY (SPIM_UART_DEFAULT_RX_CTRL_PARITY)

    #define SPIM_UART_DEFAULT_UART_TX_CTRL \
                                (SPIM_GET_UART_TX_CTRL_MODE(SPIM_UART_STOP_BITS_NUM)       | \
                                 SPIM_GET_UART_TX_CTRL_RETRY_NACK(SPIM_UART_RETRY_ON_NACK) | \
                                 SPIM_UART_DEFAULT_TX_CTRL_PARITY)

    #define SPIM_UART_DEFAULT_TX_CTRL \
                                (SPIM_GET_TX_CTRL_DATA_WIDTH(SPIM_UART_DATA_BITS_NUM) | \
                                 SPIM_GET_UART_TX_CTRL_ENABLED(SPIM_UART_DIRECTION))

    #define SPIM_UART_DEFAULT_TX_FIFO_CTRL \
                                SPIM_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(SPIM_UART_TX_TRIGGER_LEVEL)

    #define SPIM_UART_DEFAULT_FLOW_CTRL \
                        (SPIM_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(SPIM_UART_RTS_FIFO_LEVEL) | \
                         SPIM_GET_UART_FLOW_CTRL_RTS_POLARITY (SPIM_UART_RTS_POLARITY)   | \
                         SPIM_GET_UART_FLOW_CTRL_CTS_POLARITY (SPIM_UART_CTS_POLARITY)   | \
                         SPIM_GET_UART_FLOW_CTRL_CTS_ENABLE   (SPIM_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define SPIM_UART_DEFAULT_INTR_I2C_EC_MASK  (SPIM_NO_INTR_SOURCES)
    #define SPIM_UART_DEFAULT_INTR_SPI_EC_MASK  (SPIM_NO_INTR_SOURCES)
    #define SPIM_UART_DEFAULT_INTR_SLAVE_MASK   (SPIM_NO_INTR_SOURCES)
    #define SPIM_UART_DEFAULT_INTR_MASTER_MASK  (SPIM_NO_INTR_SOURCES)
    #define SPIM_UART_DEFAULT_INTR_RX_MASK      (SPIM_UART_INTR_RX_MASK)
    #define SPIM_UART_DEFAULT_INTR_TX_MASK      (SPIM_UART_INTR_TX_MASK)

#endif /* (SPIM_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define SPIM_SPIM_ACTIVE_SS0    (SPIM_SPI_SLAVE_SELECT0)
#define SPIM_SPIM_ACTIVE_SS1    (SPIM_SPI_SLAVE_SELECT1)
#define SPIM_SPIM_ACTIVE_SS2    (SPIM_SPI_SLAVE_SELECT2)
#define SPIM_SPIM_ACTIVE_SS3    (SPIM_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_SPIM_H */


/* [] END OF FILE */
